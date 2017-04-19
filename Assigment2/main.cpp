/*
Chen Yu
cy436
2017 3 10
ece4960
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include "test.h"
#include "lib.h"
using namespace std;

int main()
{
    /*Input and Declaration*/
    vector<double> X(17758);
    vector<double> b(17758);

    /*read in data from mtx file*/
    struct ComprassTypeMatrix MatrixA;
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

    /*read into sparse matrix MatrixA*/
    int A,B,pointer;
    int feedback;
    double C;
    pointer=0;
    for(int i=0;i<K;i++)
    {
        fin >> A >> B >> C;
        feedback=AddElementIntoSparseM(MatrixA,A,B,C,i,pointer);
    }
    printf("MatrixA: rank=%d; nonzero=%d \n", MatrixA.Rank,MatrixA.NonZeroNumber);

    /*Build D matrix*/
    struct ComprassTypeMatrix MatrixD;
    MatrixD=CreateDMatrix(MatrixA);
    printf("MatrixD:  rank=%d; nonzero=%d \n", MatrixD.Rank,MatrixD.NonZeroNumber);

    /*Build LU matrix*/
    struct ComprassTypeMatrix MatrixLU;
    MatrixLU=CreateLUMatrix(MatrixA);
    printf("MatrixL+U: rank=%d; nonzero=%d \n", MatrixLU.Rank,MatrixLU.NonZeroNumber);

    /*get D inv*/
    InverseSparseDiagonal(MatrixD);

    /*set x0 all zeros*/
    feedback=Zeros(X);
    testAddition();
    test1();
    test2();
    string bvar[6]={"b at 1st","b at 2nd","b at 5th","b at 6th","b at 8th","b=1 in all"};
    int b1position[6]={1,2,5,6,8,0};
    for(int i=0;i<6;i++)
    {
        b=createb1(b1position[i],17758);
        double eps;
        for(int i=0;i<51;i++)
        {
            X= Addition(Product(MatrixD,Product(MatrixLU,X)),Product(MatrixD,b));
            eps=abs(VecNorm(Addition(Neg(b),Product(MatrixA,X)))/VecNorm(b));
            printf("epsilon=%lf at %d step\n",eps,i);
        }
        cout<< bvar[i]<< " result " << (eps>1?"diverge":"converge")<<endl;
    }
}
