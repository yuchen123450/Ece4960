#include <cstdio>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stdio.h>

#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

using namespace std;

struct ComprassTypeMatrix
{
    vector<double> arrayValue=vector<double>(12);
    vector<int> arrayIndi=vector<int>(12);
    vector<int> arrayPtr=vector<int>(6);
    int NonZeroNumber=12;
    int Rank=5;
};
vector<double> Neg(vector<double> Input);
double VecNorm(vector<double> Input);
void DisplayVector(vector<double> Input);
int Zeros(vector<double> &X);
void DisplaySparseMatrix(ComprassTypeMatrix SparseM);
int AddElementIntoSparseM(ComprassTypeMatrix &Input, int A, int B, double C, int pointer,int &rowpointer);
ComprassTypeMatrix CreateDMatrix(ComprassTypeMatrix Input);
ComprassTypeMatrix CreateLUMatrix(ComprassTypeMatrix Input);
void InverseSparseDiagonal(ComprassTypeMatrix &Input);
vector<double> Product(ComprassTypeMatrix Input, vector<double> X);
vector<double> Addition(vector<double> X1, vector<double> X2);
void PermuteSparse(ComprassTypeMatrix &Input,vector <double> &b, int RowIndex1, int RowIndex2);
void PermuteColomn(ComprassTypeMatrix &Input,vector<double> &X, int ColIndex1, int ColIndex2);
void DiagonalMaximize(ComprassTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b);

#endif // LIB_H_INCLUDED
