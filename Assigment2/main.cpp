/** Main
* Chen Yu
* cy436
* 2017 3 10
* ece4960
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

#define ProblemRank 17758
#define Nonzero         126150

#include "MatrixOperate.h"
#include "test.h"
//#include "lib.h"
using namespace std;

int main()
{
    /*read in data from mtx file*/
    ifstream fin("memplus.mtx");
    if ( ! fin.is_open() )
    {
        cout << "Could not open file!" << '\n';
    }
    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(256, '\n');

    // Read defining parameters:
    //I make N as row and M as colomn, K as nonzero
    int M,N,K;
    fin >> M >> N >> K;
    printf("col: %d, row: %d, nonzero: %d\n",M,N,K);

    /*Input and Declaration*/
    vector<double> X(ProblemRank);
    vector<double> b(ProblemRank);

    /*read into sparse matrix MatrixA*/
    int A,B,pointer;
    int feedback;
    double C;
    pointer=0;
    CompressTypeMatrix MatrixA;                                                                                   // define a new matrix
    MatrixA.arrayPtr.push_back(0);                                                                                 // default the first element of ArrayPtr is 0
    for(int i=0;i<K;i++)
    {
        fin >> A >> B >> C;
        feedback += AddElementIntoSparseM(MatrixA,A,B,C,i,pointer);                          // push values into sparse matrix A
    }
    printf("MatrixA: rank=%d; nonzero=%d \n", MatrixA.Rank,MatrixA.NonZeroNumber);

    /* run test before run computation*/
    runModularTest();
    MainFunctionalTest MainTest;
    MainTest.runTest();
//    testAddition();
//    test1();
//    test2();
    for(int i=0;i<ProblemRank;i++)
    {
        X[i]=i;
    }

    int b1position[6]={1,2,5,6,8,0};
    vector<double> Zero(ProblemRank);
    for(int i=0;i<6;i++)
    {
        b=createb1(b1position[i],ProblemRank);
        printf("in main: b size:%d\n", b.size());
        SparseMatrixOperate Solve(MatrixA,X,b);
        vector<double> result;
        result=Solve.JacobiSolve();
        feedback = Solve.Zeroes(Zero);
        if (Solve.VEq(Zero, result))
            printf("diverge\n");
        else
            printf("converge\n");
    }
}
