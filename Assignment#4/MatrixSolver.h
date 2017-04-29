/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 1
 * matrix solver
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>

#define MaxSize 5


#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

using namespace std;

class DirectFullMatrixSolver   //my matrix solver supports up to rank 5 matrix
{
private:
    double A[5][5];
    vector<double> X;
    int Rank = 5;

public:
    DirectFullMatrixSolver(double A[5][5],vector<double> X);
    ~DirectFullMatrixSolver(){
    };
    vector<double> DirectSolve(double A[5][5],vector<double> X);//(double A[5][5],vector<double> &X);
    void RowPermute(double A[5][5], vector<double> &X1, int RowIndex1, int RowIndex2);
    void RowScaling(double A[5][5], vector<double> &X1, int RowIndex1, int RowIndex2, double a);
    vector<double> Product(double A[5][5],vector<double> X1);
};

void DisplayFullMatrix(double A[MaxSize][MaxSize]);
void DisplayVector(vector<double> Input);
void ExpandVector(vector<double> &Input);


template <class T>
void SaveVector(int Control,int s,vector<double> Input,T *ptr)
{
    ofstream fo;
    if (Control == 0)
    {
        fo.open(ptr->Title,std::ios::out);
    }
    else
    {
        fo.open(ptr->Title,std::ios::out | std::ios::app);
    }
    if (fmod(Control,s)==0)
    {
        if (Control/s == 0)
            fo << "Selection: Backward Euler"<<endl;
        else if (Control/s == 1)
            fo << "Selection: Forward Euler"<<endl;
        else if (Control/s == 2)
            fo << "Selection: Trapezoidal"<<endl;
        else if (Control/s == 3)
            fo << "Selection: RK34 fixed time step"<<endl;
        else if (Control/s == 4)
            fo << "Selection: Adaptive RK34"<<endl;
    }

    if (s!=0)
        fo << "X" << fmod(Control,s)+1 << "value" << endl;
    else
        fo << "time" << endl;
    for(int i=0;i<Input.size();i++)
    {
        fo << Input[i]<<", \t";
    }
    fo << "\n--------------------------------------------------\n\n";
    fo.close();
}

#endif // LIB_H_INCLUDED
