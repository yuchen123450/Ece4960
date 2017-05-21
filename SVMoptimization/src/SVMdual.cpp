#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#include "ExtractionParameter.h"
#include "MatrixOperate.h"
#include "SVMdual.h"

using namespace std;

SVMdual::SVMdual(vector< vector<double> > X,vector<double> Y,double Epsilon)
{
    Xtrain = X;
    Epsilon = Epsilon;                                      // Input Epsilon
    y         = Y;                                               // save label
    DSize   = X.size();                                     // store problem Rank
    if (DSize==0)
    {
        printf("Input vector not enough");            // except 0 size problem
        FeatureSize = 0;
    }
    else
    {
        FeatureSize = X[0].size();                       // store feature size
    }
    /*set E = 1(n dim)*/
    vector<double> e(DSize);
    E=e;                                                          // E is identity vector in size of DSize
    for(int i=0;i<DSize;i++)
    {
        E[i]=1;
    }
}

SVMdual::~SVMdual()
{
    //dtor
}

double SVMdual::K(vector<double> a, vector<double> b)
{
    try
    {
        if(a.size()!=b.size())                               //except when a vector size different from b vector size
        {
            printf("a size = %d, b size=%d\n", a.size(),b.size());
            throw "K, two array have different size";
        }
        double sum=0;                                      // initialize sum=0
        for(int i=0;i<a.size();i++)
        {
            sum += a[i]*b[i];                               // simga a[i]b[i]
        }
        return sum*sum;                                  // square sum of a(i)b(i)
    }
    catch(const char* msg)                            // exception handling
    {
      cerr << msg << endl;
    }
}

double SVMdual::DotProduct(vector<double> a, vector<double> b)      // calculate dot product
{
    double result=0;                                                           // initialize return value
    for(int i=0;i<a.size();i++)
    {
        result += a[i]*b[i];                                                     // sum of a[i]*b[i]
    }
    return result;
}
void SVMdual::GetExtract()
{
    /*construct a Local solver to find local optimal solution */
    ExtractionParameter<SVMdual> DoSvm(this);               // construct EXTRACTION PARAMETER problem
    alpha=DoSvm.GoExtract(this);                                      // using vector store solved solution
    printf("%lf\n",objective(alpha));

    /*test for local minimum, pass if the alpha give local minimum value*/
    bool pass;
    pass = DoSvm.TestExtract(this);                                   // make sure the found result is LOS
    if (pass == true)
        printf("LOS is true\n");
    else
        printf("LOS is false\n");

     /* Apply TrustTech module */
    double ExitNumber = DoSvm.TrustTechModule();
    vector< vector<double> > alpha2;
    alpha2.push_back(alpha);
    for(int i=0;i<ExitNumber;i++)
    {
        DoSvm.Reset(i+1);                                                    // set temporary parameters to (i+1)th exit point
        alpha2.push_back(DoSvm.GoExtract(this));                // do extraction again
        if (objective(alpha2[i+1]) < objective(alpha))               // whenever next LOS better than previous minimum
        {
            alpha=alpha2[i+1];                                                // set that LOS as global minimum
        }
    }


//    /* apply constraints that sum of alpha = 0*/
//    double amplitude;
//    amplitude = DotProduct(E,alpha)/sqrt( (double) DSize);  // the smallest distance we have to move
//
//    for(int i=0;i<DSize;i++)
//    {
//        alpha[i] = alpha[i]-amplitude/sqrt( (double) DSize);      // move along (-1,-1,...,-1) direction to approach that a1+a2+..an=0 plane
//    }
//    DisplayVector(alpha);
//    printf("%lf\n",objective(alpha));
//
//    /*check if the sum of alpha = 0*/
//    if (Checktrain())
//        printf("alpha satisfy sigma of alpha[i] = 0:      pass\n");
//    else
//        printf("alpha satisfy sigma of alpha[i] = 0:      failed\n");

    /* using the calculated result to compute Gradient */
    Gradient = DoSvm.PartialDeriv(this, alpha);

    /* calculate rho */
    rho=CalculateRho();
    printf("rho=%lf\n",rho);

    /* tell the error */
    printf("The training error in R2 accuracy:          %lf\n",CalTrainingR2Accuracy());
    printf("The training rmse error:                    %lf\n",CalTrainingRmseAccuracy());

}

double SVMdual::CalculateRho()                                      // calculate rho
{
    /* define and initialize*/
	double r;
	double nr_free = 0;                                                     // initialize valid number = 0
	double ub = 999999, lb = -999999, sum_free = 0;         // set upper bound, lower bound, sum
	for(int i=0;i<DSize;i++)
	{
		double yG = y[i]*Gradient[i];                                  // calculate current yG
		if(alpha[i]>=ub)                                                      // kick out over limit alpha
		{
			if(y[i]==-1)
				ub = min(ub,yG);
			else
				lb = max(lb,yG);
		}
		else if(alpha[i]<=lb)
		{
			if(y[i]==+1)
				ub = min(ub,yG);
			else
				lb = max(lb,yG);
		}
		else                                                                      // if not all alpha over limit
		{
			++nr_free;                                                        // increment valid number
			sum_free += yG;                                               // sum of valid yG
		}
	}

	if(nr_free>0)
		r = sum_free/nr_free;
	else
		r = (ub+lb)/2;

	return r;
}

/*// check if the sum of alpha = 0*/
bool SVMdual::Checktrain()
{
    double sum=0;                                                       // initialize sum
    for(int i=0;i<DSize;i++)
    {
        sum += alpha[i];                                                 // sum of alpha
    }
    if (abs(sum) < pow(10,-17))                                    // check if the sum = 0 (soft landing)
        return true;
    else
        return false;
}

double SVMdual::Predict(vector<double> Xtest)
{
     try
    {
        if(Xtest.size()!=FeatureSize)                               //except when a vector size different from existed problem size
            throw "two array have different size";
        double result=0;                                                // initialize return value = 0
        for(int i=0;i<DSize;i++)
        {
            result += alpha[i]*K(Xtest,Xtrain[i]);              // y = alpha[i]*Kernal(x, x[i])
        }
        return result+rho;
    }
    catch(const char* msg)                                        // exception handling
    {
      cerr << msg << endl;
    }
}

vector<double> SVMdual::Predict(vector< vector<double> > Xtest)
{
    vector<double> result;
    for(int i=0;i<Xtest.size();i++)
    {
        result.push_back(Predict(Xtest[i]));
    }
    return result;
}

double SVMdual::CalR2Accuracy(vector< vector<double> > Xtest)                 // calculate R2 accuracy
{
    vector<double> prediction;
    prediction = Predict(Xtest);
    double SST = 0;
    double SSE = 0;
    double ybar=ave(y);
    for(int i=0;i<DSize;i++)
    {
        SST += pow((y[i]-ybar),2);                                 // SST = sum of (y[i]-ybar)**2
        SSE += pow((y[i]-prediction[i]),2);                      // SSE = sum of Error**2
    }
    return 1-(SSE/SST);
}

double SVMdual::CalRmseAccuracy(vector< vector<double> > Xtest)
{
    vector<double> prediction;
    prediction = Predict(Xtest);
    double rmse = 0;
    for(int i=0;i<DSize;i++)
    {
        rmse += pow((prediction[i]-y[i]),2);
    }
    return sqrt(rmse/(double)DSize);
}

double SVMdual::CalTrainingR2Accuracy()
{
    return CalR2Accuracy(Xtrain);
}

double SVMdual::CalTrainingRmseAccuracy()
{
    return CalRmseAccuracy(Xtrain);
}

double SVMdual::objective(vector<double> a)              // build objective function
{
    double sum=0;
    for(int i=0;i<DSize;i++)
    {
        for(int j=0;j<DSize;j++)
        {
            sum += a[i]*a[j]*K(Xtrain[i],Xtrain[j])/2;            // sum of ai*aj*K(xi,xj)/2
        }
        sum += Epsilon*abs(a[i])- y[i]*a[i];                        // sum of Epsilon*abs(a[i]) - y[i]*a[i]
    }
    return sum;
}
