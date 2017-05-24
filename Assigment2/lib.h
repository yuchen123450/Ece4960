#include <cstdio>
#include <stdio.h>
#include <vector>
#include <algorithm>

#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

using namespace std;

struct CompressTypeMatrix
{
    vector<double> arrayValue;
    vector<int> arrayIndi;
    vector<int> arrayPtr;
    int NonZeroNumber;
    int Rank;
};
vector<double> Neg(vector<double> Input);
double VecNorm(vector<double> Input);
void DisplayVector(vector<double> Input);
int Zeros(vector<double> &X);
void DisplaySparseMatrix(CompressTypeMatrix SparseM);
int AddElementIntoSparseM(CompressTypeMatrix &Input, int A, int B, double C, int pointer,int &rowpointer);
CompressTypeMatrix CreateDMatrix(CompressTypeMatrix Input);
CompressTypeMatrix CreateLUMatrix(CompressTypeMatrix Input);
void InverseSparseDiagonal(CompressTypeMatrix &Input);
vector<double> Product(CompressTypeMatrix Input, vector<double> X);
vector<double> Addition(vector<double> X1, vector<double> X2);
void PermuteSparse(CompressTypeMatrix &Input,vector <double> &b, int RowIndex1, int RowIndex2);
void PermuteColomn(CompressTypeMatrix &Input,vector<double> &X, int ColIndex1, int ColIndex2);
void DiagonalMaximize(CompressTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b);

#endif // LIB_H_INCLUDED
