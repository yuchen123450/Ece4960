/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * TopLevel Model
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include "TopLevelModel.h"

void LoadValue(bool y[MaxSize],vector< vector<double> > &V, vector<double> Input)
{
    for(int i=0;i<MaxSize;i++)
    {
        if (y[i])
        {
            V[i].push_back(Input[i]);
        }
    }

}

void ShowValue(bool y[MaxSize],vector< vector<double> > V)
{
    for(int i=0;i<MaxSize;i++)
    {
        if (y[i])
        {
            printf("X%d value:\n",i+1);
            DisplayVector(V[i]);
        }
    }
}
