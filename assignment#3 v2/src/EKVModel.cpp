#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "EKVModel.h"
#include "ExtractParameter.h"


using namespace std;
/** Parent class
 *
 * construct a model with Input: Ids, Vgs, Vds,
 * \return: best fit Is, Kappa,Vth
 *
 */
EKVModel::EKVModel()
{
}

EKVModel::~EKVModel()
{
    //dtor
}



/** Subclass Task4
 *
 * only function is Objective function
 */
Task4::Task4(vector<double> Smodel,vector<double> Input1,vector<double> Input2, double x1,double x2,double x3)
{
    Id   = Smodel;                         // Id, Vgs, Vds are given input values
    Vgs= Input1;
    Vds= Input2;
    Is   = x1;                                  // In fact,  Is, Kappa, Vth are initial guess here
    Kappa = x2;
    Vth = x3;
}

Task4::~Task4()
{
    //dtor
}

double Task4::objective(vector<double> Parameter)
{
    double result=0;
    try
    {
        if((Vgs.size()!=Vds.size()) || (Vds.size()!=Id.size()))
            throw "two array have different size";
        for(int i=0;i<Vgs.size();i++)
        {
            result += pow((Parameter[0]*( pow(log(1+exp(Parameter[1]*(Vgs[i]-Parameter[2])/0.052)),2) - pow(log(1+exp((Parameter[1]*(Vgs[i]-Parameter[2])-Vds[i])/0.052)),2) )-Id[i]),2);
        }
        return result;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
        return 0;
    }
}

void Task4::runExtract()
{
    vector<double> Solution;
    vector<double> SSolution;
    vector<double> St(3);                                                                      // starting point, as initial guess
    St[0] = Is;
    St[1] = Kappa;
    St[2] = Vth;
    QuasiNewtonMethod<Task4> EkvNewton(St);
    Solution=EkvNewton.runExtract(this);
    printf("Quasi-Newton result: Is= %lf,  Kappa= %lf,   Vth= %lf  \n", Solution[0],Solution[1],Solution[2]);


    vector< vector<double> > SecantSt;                                              // Secant Starting
    QuasiNewtonMethod<Task4> Preprocess(St);
    SecantSt = Preprocess.TwoIterationExtract(this);                            // get next guess following Quasi-Newton
    SecantMethod<Task4> EkvSecant(SecantSt);
    SSolution = EkvSecant.runExtract(this);
    printf("Secant method result: Is= %lf,  Kappa= %lf,   Vth= %lf  \n", Solution[0],Solution[1],Solution[2]);
}

vector<double> Task4::FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3)
{
    return FullParameter2Search( x1, x2, x3,this);
}

/** Subclass Task5
 *
 * only function is Objective function
 */
Task5::Task5(vector<double> Smodel,vector<double> Input1,vector<double> Input2, double x1,double x2,double x3)
{
    Id=Smodel;                             // Id, Vgs, Vds are given input values
    Vgs=Input1;
    Vds=Input2;
    Is   = x1;                                  // In fact,  Is, Kappa, Vth are initial guess here
    Kappa = x2;
    Vth = x3;
}

Task5::~Task5()
{
    //dtor
}

double Task5::objective(vector<double> Parameter)
{
    double result=0;
    try
    {
        if((Vgs.size()!=Vds.size()) || (Vds.size()!=Id.size()))
            throw "two array have different size";
        for(int i=0;i<Vgs.size();i++)
        {
            result += pow((Parameter[0]*( pow(log(1+exp(Parameter[1]*(Vgs[i]-Parameter[2])/0.052)),2) - pow(log(1+exp((Parameter[1]*(Vgs[i]-Parameter[2])-Vds[i])/0.052)),2) )/Id[i]-Id[i]),2);
        }
        return result;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
        return 0;
    }
}

void Task5::runExtract()
{
    vector<double> Solution;
    vector<double> SSolution;
    vector<double> St(3);                                                                      // starting point, as initial guess
    St[0] = Is;
    St[1] = Kappa;
    St[2] = Vth;
    QuasiNewtonMethod<Task5> EkvNewton(St);
    Solution=EkvNewton.runExtract(this);
    printf("Quasi-Newton result: Is= %lf,  Kappa= %lf,   Vth= %lf  \n", Solution[0],Solution[1],Solution[2]);


    vector< vector<double> > SecantSt;                                              // Secant Starting
    QuasiNewtonMethod<Task5> Preprocess(St);
    SecantSt = Preprocess.TwoIterationExtract(this);                            // get next guess following Quasi-Newton
    SecantMethod<Task5> EkvSecant(SecantSt);
    SSolution = EkvSecant.runExtract(this);
    printf("Secant method result: Is= %lf,  Kappa= %lf,   Vth= %lf  \n", Solution[0],Solution[1],Solution[2]);
}
vector<double> Task5::FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3)
{
    return FullParameter2Search(x1,x2,x3,this);
}

