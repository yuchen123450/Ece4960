/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * task 1
 * matrix solver
 * implemented to solve for Ax=b problem
 * input: A and x or b
 * output: product b or solution x
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

#define MaxtrixSolverSize 5

#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

using namespace std;

class DirectFullMatrixSolver   //my matrix solver supports up to rank 5 matrix
{
private:
    double A[MaxtrixSolverSize][MaxtrixSolverSize];
    vector<double> X;
    int Rank;

public:
    DirectFullMatrixSolver(double A[MaxtrixSolverSize][MaxtrixSolverSize],vector<double> Xx);
    virtual ~DirectFullMatrixSolver();
    vector<double> DirectSolve(double A[5][5],vector<double> X);//(double A[5][5],vector<double> &X);
    void DisplayFullMatrix(double A[MaxtrixSolverSize][MaxtrixSolverSize]);
    void DisplayVector(vector<double> Input);
    void RowPermute(double A[MaxtrixSolverSize][MaxtrixSolverSize], vector<double> &X1, int RowIndex1, int RowIndex2);
    void RowScaling(double A[MaxtrixSolverSize][MaxtrixSolverSize], vector<double> &X1, int RowIndex1, int RowIndex2, double a);
    vector<double> Product(double A[MaxtrixSolverSize][MaxtrixSolverSize],vector<double> X1);
};

#endif // LIB_H_INCLUDED
