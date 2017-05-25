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
#include <algorithm>
#include "MatrixSolver.h"

using namespace std;

#ifndef EXTRACTIONPARAMETER_H_INCLUDED
#define EXTRACTIONPARAMETER_H_INCLUDED

class ExtractParameter
{
private:
    vector<double> S;
    vector<double> a;
    vector<double> x;
    double x1,x2,x3;
    double V(vector<double>S,vector<double>a,vector<double>x);
    double EKVDeviation(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double EKVequation(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double f1(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double f2(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double f3(vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double CallFunction(int FunctionNumber,vector<double> Vgs,vector<double> Vds,double Is,double Kappa,double Vth,vector<double> Id,int Task);
    double SecandCallFunction(int FunctionNumber,vector<double> Is, vector<double> Kappa,vector<double> Vth,int loop);
public:
    ExtractParameter(vector<double> Smodel,vector<double> param,vector<double> IndependentVariable);
    ExtractParameter(vector<double> Smodel,vector<double> Vgs,vector<double> Vds,double Is0,double Kappa0,double Vth0);
    ~ExtractParameter(){
    };
    vector<double> Task2LogExpressionValidation();
    vector<double> Task4ExtractParameterEKVModel(int Mode,int Task);
    vector<double> FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3);
};

#endif // EXTRACTIONPARAMETER_H_INCLUDED
