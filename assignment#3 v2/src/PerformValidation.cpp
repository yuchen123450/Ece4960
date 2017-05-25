/** Perform the validation of that existed problem
 *
 * Nothing input
 * show whether the extraction parameter class work as expected
 * \return: c,m be about 10 and -0.5
 *
 */

#include <cmath>
#include <stdlib.h>
#include <vector>
#include "PerformValidation.h"
#include "ExtractParameter.h"

using namespace std;

PerformValidation::PerformValidation()
{
    /* manually Generate 10 samples*/
    vector<double> Smodel(10);
    Smodel[0] = 12;                                           // manually generate 10 points
    Smodel[1] = 7.777;
    Smodel[2] = 6.9282;
    Smodel[3] = 4.35;
    Smodel[4] = 5.0535;
    Smodel[5] = 3.2659;
    Smodel[6] = 3.4016;
    Smodel[7] = 4.1719;
    Smodel[8] = 3.6666;
    Smodel[9] = 2.7828;
    vector<double> a(2);                                    // set a sample solution
    a[0]=10;
    a[1]=-0.5;
    vector<double> x1(10);                               // manually generate 10 points
    for(int i=0;i<10;i++)
    {
        x1[i] =(double) (i+1);
        x1[i] =log(x1[i]);
        Smodel[i]  = log(Smodel[i]);
    }
    x=x1;
    y=Smodel;
    sample = a;
}

PerformValidation::~PerformValidation()
{
    //dtor
}

double PerformValidation::objective(vector<double> param)
{
    double result=0;
    for(int i=0;i<10;i++)
    {
        result += pow((param[0]*x[i]+param[1]-y[i]),2);                        // objective = sum of (ax(i)+b-y(i))^2
    }
    return result;
}

void PerformValidation::runExtraction()
{
    vector<double> Solution;
    vector<double> SSolution;
    vector<double> St(2);                                                                      // starting point, as initial guess
    St[0] = 9.0;
    St[1] = 0.8;
    vector< vector<double> > SecantSt;                                              // Secant Starting
    QuasiNewtonMethod<PerformValidation> Validation(St);
    Solution=Validation.runExtract(this);
    printf("Quasi-Newton result: %lf,     %lf\n", exp(Solution[0]),exp(Solution[1]));

    QuasiNewtonMethod<PerformValidation> Preprocess(St);
    SecantSt = Preprocess.TwoIterationExtract(this);                            // get next guess following Quasi-Newton
    SecantMethod<PerformValidation> SValidation(SecantSt);
    SSolution = SValidation.runExtract(this);
    printf("Secant result: %lf,    %lf\n", exp(SSolution[0]),exp(SSolution[1]));
}

