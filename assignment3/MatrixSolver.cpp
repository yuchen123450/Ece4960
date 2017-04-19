/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * task 1
 * matrix solver
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "MatrixSolver.h"
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

void DirectFullMatrixSolver::RowPermute(double A[5][5], vector<double> &X1, int RowIndex1, int RowIndex2)
{
    if (RowIndex1 != RowIndex2)
    {
        double intermedia;
        intermedia=X1[RowIndex1-1];
        X1[RowIndex1-1]=X1[RowIndex2-1];
        X1[RowIndex2-1]=intermedia;
        for(int i=0;i<Rank;i++)
        {
            intermedia=A[RowIndex1-1][i];
            A[RowIndex1-1][i]=A[RowIndex2-1][i];
            A[RowIndex2-1][i]=intermedia;
        }
    }
}

void  DirectFullMatrixSolver::RowScaling(double A[5][5], vector<double> &X1, int RowIndex1, int RowIndex2, double a)
{
    if (a!=0)
    {
        X1[RowIndex2-1] += a*X1[RowIndex1-1];
        for(int i=0;i<Rank;i++)
        {
            A[RowIndex2-1][i] += A[RowIndex1-1][i]*a;
        }
    }
}

vector<double>  DirectFullMatrixSolver::Product(double A[5][5],vector<double> X1)
{
    vector<double> b(Rank);
    for(int i=0;i<Rank;i++)
    {
        for(int j=0;j<Rank;j++)
        {
            b[i]+= A[i][j]*X1[j];
        }
    }
    return b;
}

void  DirectFullMatrixSolver::DisplayFullMatrix(double A[5][5])
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("  %.1lf  ",A[i][j]);
        }
        printf("\n");
    }
}

void  DirectFullMatrixSolver::DisplayVector(vector<double> Input)
{
    for(int i=0;i<Input.size();i++)
    {
        printf("%lf; ",Input[i]);
    }
    printf("\n");
}

DirectFullMatrixSolver::DirectFullMatrixSolver(double A[5][5],vector<double> X)
{
    A=A;
    X=X;
//    if (X.size()<5)
//        while (X.size()<5)
//            X.push_back(0);
}
//double A[5][5],vector<double> X
vector<double> DirectFullMatrixSolver::DirectSolve(double A[5][5],vector<double> X)
{
    /*implement result instead of X which is private in the class*/
    vector<double> result(X.size());
    for(int i=0;i<X.size();i++)
        result[i]=X[i];

    /*direct solve*/
    for(int loop=0;loop<Rank;loop++)
    {
        int shiftrow=loop;
        for(int i=loop;i<Rank-1;i++)
        {
            if(A[i][loop]!=0)
            {
                shiftrow=i;
                break;
            }
        }
        RowPermute(A,result,loop+1,shiftrow+1);
        for(int i=0;i<Rank;i++)
        {
            if ((A[i][loop]!=0) && (i!=loop))
                RowScaling(A,result,loop+1,i+1,-A[i][loop]/A[loop][loop]);
        }
    }

    /*divided each row coefficient*/
    for(int i=0;i<Rank;i++)
    {
        if (A[i][i]!=0)
        {
            result[i]/=A[i][i];         //real result
            A[i][i]  /=A[i][i];         //A matrix convert to identity
        }
        else result[i]=0;
    }
    return result;
}

