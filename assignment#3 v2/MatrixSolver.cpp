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

DirectFullMatrixSolver::DirectFullMatrixSolver(double A[MaxtrixSolverSize][MaxtrixSolverSize],vector<double> Xx)
{
    A=A;
    X=Xx;
    Rank=Xx.size();
}
DirectFullMatrixSolver::~DirectFullMatrixSolver()
{

}


void DirectFullMatrixSolver::RowPermute(double A[MaxtrixSolverSize][MaxtrixSolverSize], vector<double> &X1, int RowIndex1, int RowIndex2)
{
    if (RowIndex1 != RowIndex2)
    {
        double intermedia;
        intermedia=X1[RowIndex1-1];                                             // exchange 2 row value
        X1[RowIndex1-1]=X1[RowIndex2-1];                                // c=b,b=a,a=c
        X1[RowIndex2-1]=intermedia;
        for(int i=0;i<Rank;i++)
        {
            intermedia=A[RowIndex1-1][i];
            A[RowIndex1-1][i]=A[RowIndex2-1][i];
            A[RowIndex2-1][i]=intermedia;
        }
    }
}

void  DirectFullMatrixSolver::RowScaling(double A[MaxtrixSolverSize][MaxtrixSolverSize], vector<double> &X1, int RowIndex1, int RowIndex2, double a)
{
    if (a!=0)
    {
        X1[RowIndex2-1] += a*X1[RowIndex1-1];                           // x2 = x2 + a*x1
        for(int i=0;i<Rank;i++)
        {
            A[RowIndex2-1][i] += A[RowIndex1-1][i]*a;                   // row2 = row2 + a*row1
        }
    }
}

vector<double>  DirectFullMatrixSolver::Product(double A[MaxtrixSolverSize][MaxtrixSolverSize],vector<double> X1)
{
    vector<double> b(Rank,0);
    for(int i=0;i<Rank;i++)
    {
        for(int j=0;j<Rank;j++)
        {
            b[i]+= A[i][j]*X1[j];                                                   // bi = sum of Aij*xj
        }
    }
    return b;
}

void  DirectFullMatrixSolver::DisplayFullMatrix(double A[MaxtrixSolverSize][MaxtrixSolverSize])
{
    for(int i=0;i<MaxtrixSolverSize;i++)
    {
        for(int j=0;j<MaxtrixSolverSize;j++)
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

vector<double> DirectFullMatrixSolver::DirectSolve(double A[MaxtrixSolverSize][MaxtrixSolverSize],vector<double> X)
{
    /*implement result instead of X which is private in the class*/
    vector<double> result(X.size());
    for(int i=0;i<X.size();i++)                                 // initialize result = X;
        result[i]=X[i];

    /*direct solve*/
    for(int loop=0;loop<Rank;loop++)                   // row increasing
    {
        int shiftrow=loop;                                         // searching from beginning of the row
        for(int i=loop;i<Rank-1;i++)                        // column increasing
        {
            if(A[i][loop]!=0)                                       // first nonzero element in the column
            {
                shiftrow=i;                                             // shift to the top
                break;
            }
        }
        if (shiftrow!=loop)                                         // shift to the top if needed
            RowPermute(A,result,loop+1,shiftrow+1);
        for(int i=0;i<Rank;i++)
        {
            if ((A[i][loop]!=0) && (i!=loop))
                RowScaling(A,result,loop+1,i+1,-A[i][loop]/A[loop][loop]);          // clear element not on diagonal to be 0
        }
    }

    /*divided each row coefficient*/
    for(int i=0;i<X.size();i++)
    {
        if (A[i][i]!=0)                   // when element is nonzero
        {
            result[i]/=A[i][i];         //real result
            A[i][i]  /=A[i][i];         //A matrix convert to identity
        }
        else result[i]=0;
    }
    return result;
}

