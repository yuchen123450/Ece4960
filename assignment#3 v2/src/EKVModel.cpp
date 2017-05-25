#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "EKVModel.h"

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
