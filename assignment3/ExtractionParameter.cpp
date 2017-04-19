/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * task2,4,5,6
 * extraction parameter
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "ExtractionParameter.h"
#include <algorithm>
#include "MatrixSolver.h"

using namespace std;

ExtractParameter::ExtractParameter(vector<double> Smodel,vector<double> param,vector<double> IndependentVariable)
{
    S=Smodel;
    a=param;
    x=IndependentVariable;
}

ExtractParameter::ExtractParameter(vector<double> Smodel,vector<double> Vgs,vector<double> Vds,double Is0,double Kappa0,double Vth0)
{
    S=Smodel;
    a=Vgs;
    x=Vds;
    x1=Is0;
    x2=Kappa0;
    x3=Vth0;
}

double V(vector<double>S,vector<double>a,vector<double>x)
{
    double sum=0;
    for(int i=0;i<x.size();i++)
    {
        sum += pow((a[0]*pow(x[i],a[1])-S[i]),2);
    }
    return sum;
}



vector<double> ExtractParameter::Task2LogExpressionValidation()//using log expression to perform the validation of the power law equation
{
    vector<double> result;
    try
    {
        if(S.size()!=x.size())                 //except when y vector size different from x vector size
            throw "two array have different size";
        /*transfer to log notation*/
        vector<double> y(x.size());
        vector<double> x1(x.size());
        for(int i=0;i<S.size();i++)
        {
            y[i]=log(S[i]);               //s=log(y)
            x1[i]=log(x[i]);              //x1=log(x)
        }

        /*solve for f1=0=f2*/
        double Jacobi[5][5]={{0,0,0,0,0},
                             {0,0,0,0,0},
                             {0,0,0,0,0},
                             {0,0,0,0,0},
                             {0,0,0,0,0}};
        vector<double> b(5);
        b[0]=0;b[1]=0;b[2]=0;b[3]=0;b[4]=0;         //preset all zeros in 2-D array and vector
        for(int i=0;i<x.size();i++)
        {
            Jacobi[0][0] += pow(x1[i],2);
            Jacobi[0][1] += x1[i];
            Jacobi[1][0] += x1[i];
            Jacobi[1][1] ++;
            b[0] += x1[i]*y[i];
            b[1] += y[i];                // this is just a rank 2 matrix
        }                                // build that Jacobi * (a,b) = 0
        DirectFullMatrixSolver DirectFullMatrixSolver(Jacobi,b);
        result=DirectFullMatrixSolver.DirectSolve(Jacobi,b);
        /*convert back to power law function*/
        result[1]=exp(result[1]);
        double medi;
        medi=result[0];
        result[0]=result[1];
        result[1]=medi;
        a=result;
    }
    catch(const char* msg)
    {
      cerr << msg << endl;
    }
    return result;
}

double ExtractParameter::EKVDeviation(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task)  //(Smodel-Smeasured)square
{
    double result=0;
    try
    {
        if((Vgs.size()!=Vds.size()) || (Vds.size()!=Id.size()))
            throw "two array have different size";
        for(int i=0;i<Vgs.size();i++)
        {
            if (Task == 4)
                result += pow((Is*( pow(log(1+exp(Kappa*(Vgs[i]-Vth)/0.052)),2) - pow(log(1+exp((Kappa*(Vgs[i]-Vth)-Vds[i])/0.052)),2) )-Id[i]),2);
            else if (Task == 5)
                result += pow((Is*( pow(log(1+exp(Kappa*(Vgs[i]-Vth)/0.052)),2) - pow(log(1+exp((Kappa*(Vgs[i]-Vth)-Vds[i])/0.052)),2) )/Id[i]-Id[i]),2);
            else
                printf("error: function not executed in task 4 or 5\n");
        }
        return result;
    }
    catch(const char* msg)
    {
      cerr << msg << endl;
    }
//    return 0;
}
double ExtractParameter::EKVequation(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task) // Smodel square
{
    double result=0;
    try
    {
        if((Vgs.size()!=Vds.size()) || (Vds.size()!=Id.size()))
            throw "two array have different size";
        for(int i=0;i<Vgs.size();i++)
        {
            if (Task == 4)
                result += Is*(pow( log(1+exp( Kappa*(Vgs[i]-Vth)/0.052 )),2 )-pow( log(1+exp( (Kappa*(Vgs[i]-Vth)-Vds[i])/0.052 )),2 ));
            else if (Task == 5)
                result += Is*(pow( log(1+exp( Kappa*(Vgs[i]-Vth)/0.052)),2 )-pow( log(1+exp( (Kappa*(Vgs[i]-Vth)-Vds[i]) /0.052 )),2 ))/Id[i];
            else
                printf("error: function not executed in task 4 or 5\n");
            return result;
        }
    }
    catch(const char* msg)
    {
      cerr << msg << endl;
    }
//    return 0;
}

double ExtractParameter::f1(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task)       //dEKVdeviation/dIs
{
    return (EKVDeviation(Vgs,Vds,1.00001*Is,Kappa,Vth,Id, Task)-EKVDeviation(Vgs,Vds,Is,Kappa,Vth,Id, Task))/(0.00001*Is);
}

double ExtractParameter::f2(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task)      //dEKVdeviation/dKappa
{
    return (EKVDeviation(Vgs,Vds,Is,1.00001*Kappa,Vth,Id, Task)-EKVDeviation(Vgs,Vds,Is,Kappa,Vth,Id, Task))/(0.00001*Kappa);
}

double ExtractParameter::f3(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task)      //dEKVdeviation/dVth
{
    return (EKVDeviation(Vgs,Vds,Is,Kappa,1.00001*Vth,Id, Task)-EKVDeviation(Vgs,Vds,Is,Kappa,Vth,Id, Task))/(0.00001*Vth);
}


double ExtractParameter::CallFunction(int FunctionNumber,vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task)
// used to select which f=0 equation to apply. EX: FunctionNumber==1, then select f1=0 to solve
{
    if (FunctionNumber == 1)
        return f1(Vgs,Vds,Is,Kappa,Vth,Id, Task);
    else if (FunctionNumber == 2)
        return f2(Vgs,Vds,Is,Kappa,Vth,Id, Task);
    else if (FunctionNumber == 3)
        return f3(Vgs,Vds,Is,Kappa,Vth,Id, Task);
    else
    {
        printf("error of input FunctionNumber\n");
        return 0;
    }
}

bool IsNaN(double t)
{
    return t != t;
}

bool IsInf(double t)
{
    return t/t != t/t;
}

vector<double> ExtractParameter::Task4ExtractParameterEKVModel(int Mode,int Task)//EKV model extraction parameter finding least-square fittest result
{
    vector<double> result;
    try
    {
        if((S.size()!=x.size()) || (a.size()!=x.size()))                //except when y vector size different from x vector size
            throw "two array have different size";

        /*f1 solve in Quasi Newton method*/
        /**
         * Initialize used variables
         */

        vector<double> Id   = S;
        vector<double> Vgs  = a;
        vector<double> Vds  = x;
        vector<double> AbsDeviation;
        AbsDeviation.push_back(0);
        vector<double> Delta;
        Delta.push_back(0);
        vector<double> dSIs;
        vector<double> dSKappa;
        vector<double> dSVth;
        vector<double> Is;
        vector<double> Kappa;
        vector<double> Vth;
        dSIs.push_back(0);
        dSKappa.push_back(0);
        dSVth.push_back(0);
        Is.push_back(x1);
        Kappa.push_back(x2);
        Vth.push_back(x3);
        double dIs  = 0;
        double dK   = 0;
        double dVth = 0;
        int loop    = 0;
        int endloop = -1;
        double J[5][5]= {{0,0,0,0,0},
                         {0,0,0,0,0},
                         {0,0,0,0,0},
                         {0,0,0,0,0},
                         {0,0,0,0,0}};
        while(loop<200)
        {
            /*start to solve f1 or f2 or f3 == 0*/

            /*Jacobi build*/
            if ((Mode==0) || (loop==0))                //Quasi-Newton Method
            {
                /**
                 *Newtons method
                 */
                for(int i=1;i<4;i++)
                {
                    J[i-1][0] = (CallFunction(i,Vgs,Vds,1.00001*Is[loop],Kappa[loop],Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task))
                                /(0.00001*Is[loop]);
                    J[i-1][1] = (CallFunction(i,Vgs,Vds,Is[loop],1.00001*Kappa[loop],Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task))
                                /(0.00001*Kappa[loop]);
                    J[i-1][2] = (CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],1.00001*Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task))
                                /(0.00001*Vth[loop]);
                }
            }
            else if ((Mode==1) && (loop>0))
            {
                /**
                 * Secant method
                 */
                for(int i=1;i<4;i++)
                {
                    J[i-1][0] = (CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop-1],Kappa[loop-1],Vth[loop-1],Id,Task))
                                /(Is[loop]-Is[loop-1]);
                    J[i-1][1] = (CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop-1],Kappa[loop-1],Vth[loop-1],Id,Task))
                                /(Kappa[loop]-Kappa[loop-1]);
                    J[i-1][2] = (CallFunction(i,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)-CallFunction(i,Vgs,Vds,Is[loop-1],Kappa[loop-1],Vth[loop-1],Id,Task))
                                /(Vth[loop]-Vth[loop-1]);
                }
            }
            /*solve for matrix*/
            vector<double> fder(5);          //preparation before execute extraction parameter
            fder[0]=-CallFunction(1,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task);
            fder[1]=-CallFunction(2,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task);
            fder[2]=-CallFunction(3,Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task);
            fder[3]=0;
            fder[4]=0;
//            printf("fder=%lf, %lf, %lf\n",fder[0],fder[1],fder[2]);
            vector<double> IKV;
            DirectFullMatrixSolver IsKappaVth(J,fder);
            IKV = IsKappaVth.DirectSolve(J,fder);
            dIs = IKV[0];
            dK  = IKV[1];
            dVth= IKV[2];
            printf("dIs=%lf, dK=%lf, dVth=%lf\n",dIs,dK,dVth);
            Is.push_back(Is[loop]+dIs);
            Kappa.push_back(Kappa[loop]+dK);
            Vth.push_back(Vth[loop]+dVth);

            /* calculate Deviation, Delta and Sensitivity */
            AbsDeviation.push_back(EKVDeviation(Vgs,Vds,Is[loop+1],Kappa[loop+1],Vth[loop+1],Id,Task));
            Delta.push_back((pow((Is[loop+1]-Is[loop]),2)/pow(Is[loop+1],2)) + (pow((Kappa[loop+1]-Kappa[loop]),2)/pow(Kappa[loop+1],2)) + (pow((Vth[loop+1]-Vth[loop]),2)/pow(Vth[loop+1],2)));
            dSIs.push_back(EKVequation(Vgs,Vds,Is[loop+1],Kappa[loop],Vth[loop],Id,Task)*Is[loop]
                           /(EKVequation(Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)*dIs));
            dSKappa.push_back(EKVequation(Vgs,Vds,Is[loop],Kappa[loop+1],Vth[loop],Id,Task)*Kappa[loop]
                              /(EKVequation(Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)*dK));
            dSVth.push_back(EKVequation(Vgs,Vds,Is[loop],Kappa[loop],Vth[loop+1],Id,Task)*Vth[loop]
                            /(EKVequation(Vgs,Vds,Is[loop],Kappa[loop],Vth[loop],Id,Task)*dVth));
            printf("%lf,%lf,%lf,%lf,%d\n",Is[loop+1],Kappa[loop+1],Vth[loop+1],Delta[loop+1],loop);
            if (loop == endloop)
            {
                break;
            }
            if ((loop>1) && ((abs(Delta[loop+1]) < pow(10,-14)) ||
                            (Delta[loop+1] == pow(Delta[loop],2))||
                            IsNaN(Is[loop+1]) || IsInf(Is[loop+1]) ||
                            IsNaN(Kappa[loop+1]) || IsInf(Kappa[loop+1])||
                            IsNaN(Vth[loop+1]) || IsInf(Vth[loop+1])))
                  {
                      endloop = loop + 1;//break;
                  }
            loop++;
            printf("\n");
        }



        /**
         * normal convergence judgment
         * change in value less than 10^(-7)
         */
        if (loop>=199)
            printf("finally not converge\n");
        else if (dIs/Is[loop]<pow(10,-7) || dK/Kappa[loop]<pow(10,-7) || dVth/Vth[loop]<pow(10,-7))
            printf("finally converges\n");
        else
            printf("fail at loop = %d\n",loop-1);


        /**
         * quadratic convergence judgmentS
         * f(x2)-f(x1)/f(x2) =?= f(X1)-f(x0)/f(x1)  ^ 2
         */
        if ((loop>=2) && (Delta[loop+1] == pow(Delta[loop],2)))
            printf("quadratic convergence exist\n");
        else if (loop<2)
            printf("loop number not enough to detect quadratic convergence\n");
        else if  (loop>=2)
            printf("quadratic convergence failed\n");

        result.push_back(Is[loop-1]);
        result.push_back(Kappa[loop-1]);
        result.push_back(Vth[loop-1]);
        result.push_back(AbsDeviation[loop-1]);
        result.push_back(Delta[loop-1]);
        result.push_back(dSIs[loop-1]);
        result.push_back(dSKappa[loop-1]);
        result.push_back(dSVth[loop-1]);
    }
    catch(const char* msg)
    {
      cerr << msg << endl;
    }
    return result;
}

vector<double> ExtractParameter::FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3)
{
    vector<double> result;
    for(int loop=0;loop<2;loop++)
    {
        result.push_back(x1[0]);
        result.push_back(x2[0]);
        result.push_back(x3[0]);
        double Vmin=EKVDeviation(a,x,x1[0],x2[0],x3[0],S,4);
        for(int i=0;i<x1.size();i++)
        {
            for(int j=0;j<x2.size();j++)
            {
                for(int k=0;k<x3.size();k++)
                {
                    if ((EKVDeviation(a,x,x1[i],x2[j],x3[k],S,4)<Vmin) && ((x1[i]!=result[0]) || (x2[j]!=result[1]) || (x3[k]!=result[2])))
                    {
                        Vmin=EKVDeviation(a,x,x1[i],x2[j],x3[k],S,4);
                        result[0+loop*3] = x1[i];
                        result[1+loop*3] = x2[j];
                        result[2+loop*3] = x3[k];
                    }
                }
            }
        }
    }
    return result;
}
