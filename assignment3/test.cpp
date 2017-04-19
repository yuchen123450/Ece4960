/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * test for direct method matrix solver
 *
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "test.h"
#include "MatrixSolver.h"
#include <string>
#include <sstream>

using namespace std;

TestDirectMatrixSolver::TestDirectMatrixSolver(double A[5][5], vector<double> X, vector<double> b)
{
    A=A;X=X;b=b;
}

void TestDirectMatrixSolver::ShowTestResult(double A[5][5], vector<double> X, vector<double> b,string TestTag) //check the matrix solver result is the same as ground truth
{
    vector<double> result;
    bool pass=true;
    DirectFullMatrixSolver CalTest(A,X);
    result = CalTest.DirectSolve(A,X);
//    CalTest.DisplayVector(result);
    for(int i=0;i<Rank;i++)
    {
        if (result[i] - b[i] > 0.01)
            pass = false;
    }
    cout << TestTag << ":" << (pass?"pass":"failed") << endl;
}

void TestDirectMatrixSolver::Update(double A[5][5],vector<double> X,vector<double> b)
{
    A=A;
    X=X;
    b=b;
}
vector<double> BuildVector(int Size, int VecRank, double Input[])
{
    vector<double> result;
    for(int i=0;i<Size;i++)
    {
        if (i<VecRank)
            result.push_back(Input[i]);
        else
            result.push_back(0);
    }
    return result;
}

void GoTestMatrixSolver()
{
    /**
     * fixed value test
     */
    double A[3][5][5] = {{{2,-1,1,0,0},
                          {0,-2,1,0,0},
                          {1,-2,0,0,0},
                          {0,0,0,0,0},
                          {0,0,0,0,0}},{{1,2,0,0,0},
                                        {4,5,6,0,0},
                                        {0,7,8,0,0},
                                        {0,0,0,10,0},
                                        {0,0,0,0,0}},{{0,3,2,0,0},
                                                      {1,0,2,6,0},
                                                      {5,5,7,3,0},
                                                      {0,0,3,1,0},
                                                      {0,0,0,0,0}}}; //create 3 matrix for tests
    vector<double> RHS; //in Ax=b, RHS=b
    double x[3][4]={{3,1,1,0},
                    {0,1,2,3},
                    {6,31,38,13}};
    RHS = BuildVector(5,4,x[0]);
    vector<double> GroundTruth; //in Ax=b, GroundTruth=x
    double b[3][4]={{1,0,1,0},
                    {-0.121212,0.060606,0.19697,0.3},
                    {1,0,3,4}};
    /* fixed value test 1*/
    GroundTruth = BuildVector(5,4,b[0]);
    TestDirectMatrixSolver Test1(A[0],RHS,GroundTruth);
    Test1.ShowTestResult(A[0],RHS,GroundTruth,"Fixed Value TEST 1");

    /* fixed value test 2*/
    RHS = BuildVector(5,4,x[1]);
    GroundTruth = BuildVector(5,4,b[1]);
    Test1.Update(A[1],RHS,GroundTruth);
    Test1.ShowTestResult(A[1],RHS,GroundTruth,"Fixed Value TEST 2");

    /* fixed value test 3*/
    RHS = BuildVector(5,4,x[2]);
    GroundTruth = BuildVector(5,4,b[2]);
    Test1.Update(A[2],RHS,GroundTruth);
    Test1.ShowTestResult(A[2],RHS,GroundTruth,"Fixed Value TEST 3");

    /**
     * random value test
     */
    for(int loop=0;loop<5;loop++)
    {
        double RandMatrix[5][5] = {{rand() % 10,    rand() % 10,     rand() % 10,   rand() % 10,   rand() % 10,  },
                                   {rand() % 100,   rand() % 100,    rand() % 100,  rand() % 100,  rand() % 100, },
                                   {rand() % 1000,  rand() % 1000,   rand() % 1000, rand() % 1000, rand() % 1000,},
                                   {rand() % 10,    rand() % 100,    rand() % 100,  rand() % 10,   rand() % 1000,},
                                   {rand() % 1000,  rand() % 10,     rand() % 100,  rand() % 10,   rand() % 100,}};
        double Multiplier[5]    = { rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10 };

        /*generate Ax=b, then try solve(A,b) compare the result with VECTOR x*/
        GroundTruth = BuildVector(5,5,Multiplier);
        DirectFullMatrixSolver Inter(RandMatrix,RHS);
        RHS = Inter.Product(RandMatrix,GroundTruth);
        Test1.Update(RandMatrix,RHS,GroundTruth);

        /*do with test tag*/
        string tag = "Random Value TEST ";
        if (loop==0)
            tag += "1";
        else if (loop==1)
            tag += "2";
        else if (loop==2)
            tag += "3";
        else if (loop==3)
            tag += "4";
        else tag += "5";
        Test1.ShowTestResult(RandMatrix,RHS,GroundTruth,tag);
    }

}
