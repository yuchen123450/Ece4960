/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 3
 * Do ode solver for figure 3 circuit
 * ode: dV1/dt = -(1/C1R1+1/C1R2)*V1 +1/C1R2 *V2 + i(t)/C1
 *      dV2/dt = 1/C2R2 * V1 -(1/C2R2+C2R3)*V2
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include "TopLevelModel.h"
#include "Fig3Circuit.h"

using namespace std;

double BasicCircuit::Current(double t)
{
    if ((fmod(t*pow(10,9),20))<=1)
    {
        return 0.0001*(fmod(t*pow(10,9),20));
    }
    else if(((fmod(t*pow(10,9),20))>1) && ((fmod(t*pow(10,9),20))<=10))
    {
        return 0.0001;
    }
    else if(((fmod(t*pow(10,9),20))>10) && ((fmod(t*pow(10,9),20))<=11))
    {
        return 0.0001*(11-(fmod(t*pow(10,9),20)));
    }
    else if(((fmod(t*pow(10,9),20))>11) && ((fmod(t*pow(10,9),20))<=20))
    {
        return 0;
    }
}
void BasicCircuit::Testit()
{
    vector<double> Time;
    vector<double> It(2200);
    for(int i=0;i<2200;i++)
    {
        int a = i;
        Time.push_back((double)a*pow(10,-9)/100);
        It[i]   = Current(Time[i]);
    }
    DisplayVector(It);
}

vector<double> BasicCircuit::ODE(double t,vector<double> In)
{
    vector<double> result(2);
    result[0] = Current(t)/C1;
    result[1] = 0;
    return result;
}

void BasicCircuit::GoShowFig3V1V2()
{
    int done;
    int iteration = int((stop - start)/dt);
    double a[MaxSize][MaxSize] = {{-(1/(C1*R1)+1/(C1*R2)),  1/(C1*R2),  0,0,0},
                                  {1/(C2*R2)   ,-(1/(C2*R2)+1/(C2*R3)),0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0}};
    vector< vector<double> > V(MaxSize);
    V[0].push_back(0);
    V[1].push_back(0);
    vector<double> X(2);
    X[0]=0;
    X[1]=0;
    /**
     * Backward Euler
     */
    printf("Backward Euler\n");
    done = Integrate(0, iteration,a,V,X,start,stop,dt,this);
    cout << (done == 1?"Done":"Not done")<<endl;

    /**
     * Forward Euler
     */
    printf("Forward Euler\n");
    done = Integrate(1, iteration,a,V,X,start,stop,dt,this);
    cout << (done == 1?"Done":"Not done")<<endl;

    /**
     * Trapezoidal Euler
     */
    printf("Trapezoidal Euler\n");
    done = Integrate(2, iteration,a,V,X,start,stop,dt,this);
    cout << (done == 1?"Done":"Not done")<<endl;

    /**
     * One step RK34
     */
    printf("fixed dt RK34\n");
    done = Integrate(3, iteration,a,V,X,start,stop,dt,this);
    cout << (done == 1?"Done":"Not done")<<endl;

    /**
     * Adaptive RK34
     */
    printf("Adaptive RK34\n");
    done = Integrate(4, iteration,a,V,X,start,stop,dt,this);
    cout << (done == 1?"Done":"Not done")<<endl;
}



