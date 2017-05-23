/**  Matrix Operator
 *
 * Some global function accessory
 *
 * Chen Yu
 * May.23/2017
 */

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

double ave(vector<double> Input)
{
    int s=Input.size();
    double sum=0;
    for(int i=0;i<s;i++)
    {
        sum += Input[i];
    }
    return sum/(double) s;
}
