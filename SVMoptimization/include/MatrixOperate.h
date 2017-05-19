#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#define MaxSize 4

#ifndef MATRIXOPERATE_H
#define MATRIXOPERATE_H

using namespace std;
template <typename T>
class MatrixOperate
{
    public:
        MatrixOperate(T A, std::vector<double> X)
        {
            A=A;
            X=X;
            Rank = X.size();
        };
        ~MatrixOperate()
        {
        };
        std::vector<double> DirectSolve(T A,std::vector<double> X)//(double A[MaxSize][MaxSize],vector<double> &X);
        {
            /*implement result instead of X which is private in the class*/
            std::vector<double> result(X.size());
            for(int i=0;i<X.size();i++)
                result[i]=X[i];

            /*direct solve*/
            for(int loop=0;loop<Rank;loop++)
            {
                int shiftrow=loop;
                for(int i=loop;i<Rank-1;i++)    //row increasing
                {
                    if(A[i][loop]!=0)
                    {
                        shiftrow=i;             // looking for a non-zero pivot
                        break;
                    }
                }
                RowPermute(A,result,loop+1,shiftrow+1); //Row permute to make sure the diagonal is non-zero
                for(int i=0;i<Rank;i++)
                {
                    if ((A[i][loop]!=0) && (i!=loop))
                        RowScaling(A,result,loop+1,i+1,-A[i][loop]/A[loop][loop]); //Row scaling to clear all other indices to be zero
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
        };

        /*Product between matrix and vector*/
        std::vector<double> Product(T A,std::vector<double> X1)
        {
            std::vector<double> b(Rank);
            for(int i=0;i<Rank;i++)             //row increasing
            {
                for(int j=0;j<Rank;j++)         //col increasing
                {
                    b[i]+= A[i][j]*X1[j];       //a(ij)*b(j)
                }
            }
            return b;
        };

        /*Product between vector and matrix*/
        std::vector<double> Product(std::vector<double> X1, T A)
        {
            std::vector<double> b(Rank);
            for(int j=0;j<Rank;j++)             //col increasing
            {
                for(int i=0;i<Rank;i++)         //row increasing
                {
                    b[j]+= A[i][j]*X1[i];            //b(i)*a(ij)
                }
            }
            return b;
        };
    protected:
        void RowPermute(T &A, std::vector<double> &X1, int RowIndex1, int RowIndex2)
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
        };
        void RowScaling(T &A, std::vector<double> &X1, int RowIndex1, int RowIndex2, double a)
        {
            if (a!=0)
            {
                X1[RowIndex2-1] += a*X1[RowIndex1-1];
                for(int i=0;i<Rank;i++)
                {
                    A[RowIndex2-1][i] += A[RowIndex1-1][i]*a;
                }
            }
        };

    private:
        T A;
        std::vector<double> X;
        int Rank;
};

void DisplayFullMatrix(double A[MaxSize][MaxSize]);
void DisplayFullMatrix(std::vector< std::vector<double> > A) ;
void DisplayVector(std::vector<double> Input);
void ExpandVector(std::vector<double> &Input, int Size);
#endif // MATRIXOPERATE_H
