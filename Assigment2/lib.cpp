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

vector<double> Neg(vector<double> Input)
{
    vector<double> result(Input.size());
    for(int i=0;i<Input.size();i++)
        result[i]=-Input[i];
    return result;
}

vector<int> Convert2Int(vector<double> Input)
{
    vector<int> Output(Input.size());
    for(int i=0;i<Input.size();i++)
    {
        Output[i]=(int)Input[i];
    }
    return Output;
}

double VecNorm(vector<double> Input)
{
    double result=0;
    for(int i=0;i<Input.size();i++)
        result += pow(Input[i],2);
    return result;
}

void SwitchTwoDouble(double &A, double &B)
{
    double media;
    media=A;
    A=B;
    B=media;
}

void SwitchTwoInt(int &A, int &B)
{
    int media;
    media=A;
    A=B;
    B=media;
}

void DisplayVector(vector<double> Input)
{
    for(int i=0;i<Input.size();i++)
    {
        printf("%lf; ",Input[i]);
    }
    printf("\n");
}


int Zeros(vector<double> &X)      //make matrix all "0"
{
    for(int i=0;i<X.size();i++)
    {
        X[i]=0;
    }
    return 1;
}

void DisplaySparseMatrix(ComprassTypeMatrix SparseM)
{
    printf("sparse matrix value is:   ");
    for(int i=0;i<SparseM.NonZeroNumber;i++)
    {
        printf("%.2lf;  ",SparseM.arrayValue[i]);
    }
    printf("\n");
    printf("sparse matrix row pointer is:   ");
    for(int i=0;i<6;i++)
    {
        printf("%d;  ",SparseM.arrayPtr[i]);
    }
    printf("\n");
    printf("sparse matrix indices is:   ");
    for(int i=0;i<SparseM.NonZeroNumber;i++)
    {
        printf("%d;  ",SparseM.arrayIndi[i]);
    }
    printf("\n");
}

int AddElementIntoSparseM(ComprassTypeMatrix &Input, int A, int B, double C, int pointer, int &rowpointer)
{
        if (pointer<12)
        {
            Input.arrayIndi[pointer]=A-1;
            Input.arrayValue[pointer]=C;
        }
        else
        {
            Input.arrayIndi.push_back(A-1);
            Input.arrayValue.push_back(C);
            Input.NonZeroNumber++;
        }
        if (B==rowpointer)
            Input.arrayPtr[B]++;
        else
        {
            if (B>5)
            {
                for(int j=rowpointer+1;j<=B;j++)
                {
                     Input.arrayPtr.push_back(Input.arrayPtr[rowpointer]);
                     Input.Rank++;
                }
                Input.arrayPtr[B]++;
            }
            else
                for(int j=rowpointer;j<B;j++)
                     Input.arrayPtr[j]=Input.arrayPtr[rowpointer];
                Input.arrayPtr[B]=Input.arrayPtr[rowpointer]+1;
        }
        rowpointer=B;
        return 1;
}

ComprassTypeMatrix CreateDMatrix(ComprassTypeMatrix Input)
{
    struct ComprassTypeMatrix MatrixD;
    int Dptrpointer=0,Dpointer=0;
    int feedback;
    for(int i=0;i<Input.Rank;i++)
    {
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)
        {
            if (Input.arrayIndi[j]==i)
            {
                feedback=AddElementIntoSparseM(MatrixD,Input.arrayIndi[j]+1,i+1,Input.arrayValue[j],Dpointer,Dptrpointer);
                Dpointer++;
                break;
            }
        }
    }
    return MatrixD;
}

ComprassTypeMatrix CreateLUMatrix(ComprassTypeMatrix Input)
{
    struct ComprassTypeMatrix LU;
    int LUptrpointer=0,LUpointer=0;
    int feedback;
    for(int i=0;i<Input.Rank;i++)
    {
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)
        {
            if (Input.arrayIndi[j]!=i )
            {
                feedback=AddElementIntoSparseM(LU,Input.arrayIndi[j]+1,i+1,Input.arrayValue[j],LUpointer,LUptrpointer);
                LUpointer++;
            }
        }
    }
    return LU;
}


void InverseSparseDiagonal(ComprassTypeMatrix &Input)
{
    for(int i=0;i<Input.Rank;i++)
    {
        Input.arrayValue[i]= 1/Input.arrayValue[i];
    }
}

vector<double> Product(ComprassTypeMatrix Input, vector<double> X)
{
    vector<double> b(X.size());
    int cont;
    cont=Zeros(b);
    if(X.size()!=Input.Rank)
    {
        printf("vector size is different from that matrix rank");
        return b;
    }
    for(int i=0;i<Input.Rank;i++)
    {
        for(int j=0;j<Input.arrayPtr[i+1]-Input.arrayPtr[i];j++)
        {
            b[i]+=Input.arrayValue[Input.arrayPtr[i]+j]*X[Input.arrayIndi[Input.arrayPtr[i]+j]];
        }
    }
    return b;
}

vector<double> Addition(vector<double> X1, vector<double> X2)
{
    vector<double> b(X1.size());
    if (X1.size()!=X2.size())
    {
        printf("error: addition between different size vectors\n");
    }
    else
    {
        for(int i=0;i<X1.size();i++)
            b[i]=X1[i]+X2[i];
        return b;
    }
}

void PermuteSparse(ComprassTypeMatrix &Input,vector<double> &b, int RowIndex1, int RowIndex2)
{
    double media;
    media=b[RowIndex1-1];
    b[RowIndex1-1]=b[RowIndex2-1];
    b[RowIndex2-1]=media;

    /*get each row # of nonzero value first*/
    int EachRowContainsNonZero[Input.Rank];
    for(int i=0;i<Input.Rank;i++)
    {
        EachRowContainsNonZero[i]=Input.arrayPtr[i+1]-Input.arrayPtr[i];
    }

    /*define intermedia array*/
    double Row2Value[EachRowContainsNonZero[RowIndex2-1]];
    int Row2Indi[EachRowContainsNonZero[RowIndex2-1]];
    double IntermediaValue[Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1]];
    int IntermediaIndi[Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1]];

    /*save initial row2 all value and indices*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex2-1];i++)
    {
        Row2Value[i]=Input.arrayValue[Input.arrayPtr[RowIndex2-1]+i];
        Row2Indi[i]=Input.arrayIndi[Input.arrayPtr[RowIndex2-1]+i];
    }
    /*save initial items between row1 and row2 all value and indices*/
    for(int i=0;i<Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1];i++)
    {
        IntermediaValue[i]=Input.arrayValue[Input.arrayPtr[RowIndex1]+i];
        IntermediaIndi[i]=Input.arrayIndi[Input.arrayPtr[RowIndex1]+i];
    }

    /*move row1 to row2*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex1-1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex2]-1-i]=Input.arrayIndi[Input.arrayPtr[RowIndex1]-1-i];
        Input.arrayValue[Input.arrayPtr[RowIndex2]-1-i]=Input.arrayValue[Input.arrayPtr[RowIndex1]-1-i];
    }

    /*move items between row1 and row2*/
    for(int i=0;i<Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex1-1]+EachRowContainsNonZero[RowIndex2-1]+i]=IntermediaIndi[i];
        Input.arrayValue[Input.arrayPtr[RowIndex1-1]+EachRowContainsNonZero[RowIndex2-1]+i]=IntermediaValue[i];
    }

    /*move row2 to row1*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex2-1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex1-1]+i]=Row2Indi[i];
        Input.arrayValue[Input.arrayPtr[RowIndex1-1]+i]=Row2Value[i];
    }

    /*change ptr*/
    Input.arrayPtr[0]=0;
    int accumu=0;
    for(int i=0;i<Input.Rank;i++)
    {
        if (i==RowIndex1-1)
            accumu +=EachRowContainsNonZero[RowIndex2-1];
        else if (i==RowIndex2-1)
            accumu +=EachRowContainsNonZero[RowIndex1-1];
        else
            accumu +=EachRowContainsNonZero[i];
        if(i<Input.Rank)
            Input.arrayPtr[i+1]=accumu;
    }
    printf("\n");
}

void PermuteColomn(ComprassTypeMatrix &Input,vector<double> &X, int ColIndex1, int ColIndex2)
{
    SwitchTwoDouble(X[ColIndex1-1],X[ColIndex2-1]);
    bool Col1NonZero;
    bool Col2Nonzero;
    for(int i=0;i<Input.Rank;i++)
    {
        Col1NonZero=false;
        Col2Nonzero=false;
        int ptr1,ptr2=0;
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)
        {
            if (Input.arrayIndi[j]==ColIndex1-1)
            {
                Col1NonZero=true;
                ptr1=j;
            }
            if (Input.arrayIndi[j]==ColIndex2-1)
            {
                Col2Nonzero=true;
                ptr2=j;
            }
        }
        if ((Col1NonZero==true) && (Col2Nonzero==true))
        {
            SwitchTwoDouble(Input.arrayValue[ptr1],Input.arrayValue[ptr2]);
        }
        else if ((Col1NonZero==true) && (Col2Nonzero==false))
        {
            Input.arrayIndi[ptr1]=ColIndex2-1;
            for(int j=ptr1+1;j<Input.arrayPtr[i+1];j++)
            {
                if (Input.arrayIndi[j]<ColIndex2-1)
                {
                    SwitchTwoDouble(Input.arrayValue[j],Input.arrayValue[j-1]);
                    SwitchTwoInt(Input.arrayIndi[j],Input.arrayIndi[j-1]);
                }
            }
        }
        else if ((Col1NonZero==false) && (Col2Nonzero==true))
        {
            Input.arrayIndi[ptr2]=ColIndex1-1;
            for(int j=ptr2-1;j>=Input.arrayPtr[i];j--)
            {
                if (Input.arrayIndi[j]>ColIndex1-1)
                {
                    SwitchTwoDouble(Input.arrayValue[j],Input.arrayValue[j+1]);
                    SwitchTwoInt(Input.arrayIndi[j],Input.arrayIndi[j+1]);
                }
            }
        }
    }
}

void DiagonalMaximize(ComprassTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b)
{
    int ptr;
    double Max;
    int row,col;
    bool shift;
    for(int i=0;i<Input.Rank;i++)
    {
        shift=false;
        row=0;
        col=0;
        ptr=Input.arrayPtr[i];
        Max=Input.arrayValue[ptr];
        /*Find maximum and corresponding ptr*/
        for(int j=Input.arrayPtr[i];j<Input.NonZeroNumber;j++)
        {
            if ((Input.arrayValue[j]>Max) && (Input.arrayIndi[j]>=i))
            {
                Max=Input.arrayValue[j];
                ptr=j;
                shift=true;
            }
        }
        if (shift)
        {
        /*figure out corresponding row and col*/
            for(int j=0;j<=Input.Rank;j++)
                if (ptr<Input.arrayPtr[j])
                {
                    row=j;
                    break;
                }
            col=Input.arrayIndi[ptr]+1;
        /*Do permute*/
            if ((row==i+1) && (col!=i+1))
                PermuteColomn(Input,Xcomp,i,col-1);
            if ((row!=i+1) && (col==i+1))
                PermuteSparse(Input,b,i,row-1);
            if ((row!=i+1) && (col!=i+1))
            {
                PermuteSparse(Input,b,i+1,row);
                PermuteColomn(Input,Xcomp,i+1,col);
            }
        }
    }
}
