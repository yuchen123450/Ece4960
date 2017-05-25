/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * test for direct method matrix solver
 * Actually thats a modular test, only for matrix solver
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "MatrixSolver.h"
#include <string>


#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

using namespace std;

class TestDirectMatrixSolver   //my matrix solver supports up to rank 5 matrix
{
private:
    double A[5][5];
    vector<double> X;
    int Rank = 5;
    vector<double> b;

public:
    TestDirectMatrixSolver(double A[5][5],vector<double> X,vector<double> b);
    void ShowTestResult(double A[5][5],vector<double> X,vector<double> b, string TestTag);
    void Update(double A[5][5],vector<double> X,vector<double> b);
    virtual ~TestDirectMatrixSolver(){
        //delete A;
    };
};

void GoTestMatrixSolver();

#endif // TEST_H_INCLUDED
