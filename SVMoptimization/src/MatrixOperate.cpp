#include "MatrixOperate.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void  DisplayFullMatrix(double A[MaxSize][MaxSize]) //display full matrix
{
    for(int i=0;i<MaxSize;i++)          //row increasing
    {
        for(int j=0;j<MaxSize;j++)      //col increasing
        {
            printf("  %.1lf  ",A[i][j]);
        }
        printf("\n");
    }
}

void  DisplayFullMatrix(vector< vector<double> > A) //display full matrix
{
    for(int i=0;i<A.size();i++)          //row increasing
    {
        for(int j=0;j<A.size();j++)      //col increasing
        {
            printf("  %.1lf  ",A[i][j]);
        }
        printf("\n");
    }
}

void  DisplayVector(vector<double> Input) //display a vector
{
    for(int i=0;i<Input.size();i++)
    {
        printf("%.12lf; ",Input[i]);
    }
    printf("\n");
}

void ExpandVector(vector<double> &Input,int Size) //expand vector to size of Maxsize
{
    while (Input.size()<Size)
    {
        Input.push_back(0);
    }
}
