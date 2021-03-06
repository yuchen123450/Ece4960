/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 5
 * Do ode solver for figure 5 circuit
 * ode: dV1/dt = -1/C1Rg*V1 +            i(t)/C1
 *      dV2/dt =             -1/C2Rl*V2 + Vdd/RlC2-Idekv/C2
 *  IdEkv = is^2 *( log^2( 1+e^(k(Vg-Vth)/2Vth) )-log^2( 1+e^((k(Vg-Vth)-Vds)/2Vt) ) )
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include "TopLevelModel.h"
#include "EKVcircuit.h"
#include "Fig3Circuit.h"

using namespace std;
double EKVcircuit::IdEkv(double V1,double V2)
{
    return pow(Is,2) * ( pow(log( 1+exp(Kappa*(V1-Vth)/0.0052)),2) - pow(log( 1+exp((Kappa*(V1-Vth)-V2)/0.0052)),2) );
}

double EKVcircuit::Current(double t)
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
vector<double> EKVcircuit::ODE(double t,vector<double> In)
{
    vector<double> result(2);
    result[0] = Current(t)/C1;
    result[1] = Vdd/(Rl*C2)-IdEkv(In[0],In[1])/C2;
    return result;
}

void EKVcircuit::GoShowEKVcircuit()
{
    int done;
    int iteration = int((stop - start)/dt);
    double a[MaxSize][MaxSize] = {{-1/(C1*Rg),  0,  0,0,0},
                                  {0   , -1/(C2*Rl),0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0}};
    vector< vector<double> > V(MaxSize);
    V[0].push_back(2.5);
    V[1].push_back(2.5);
    vector<double> X(2);
    X[0]=2.5;
    X[1]=2.5;
    /**
     * Forward Euler
     */
    printf("Forward Euler\n");
    done = Integrate(1, iteration,a,V,X,start,stop,dt,this);
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
