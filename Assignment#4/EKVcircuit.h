/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 5
 * Do ode solver for figure 5 circuit
 * ode: dV1/dt = -1/C1Rg*V1 +            i(t)/C1
 *      dV2/dt =             -1/C2Rl*V2 + Vdd/RlC2-Idekv/C2
 *  IdEkv = is^2 *( log^2( 1+e^(k(Vg-Vth)/2Vt) )-log^2( 1+e^((k(Vg-Vth)-Vds)/2Vt) ) )
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include <string>
#ifndef EKVCIRCUIT_H_INCLUDED
#define EKVCIRCUIT_H_INCLUDED

class EKVcircuit
{
private:
    double C1,C2,Rl,Rg,Vdd;
    double start,stop,dt;
    double Is   = 5*pow(10,-6);
    double Kappa= 0.7;
    double Vth  = 1;
    double IdEkv(double V1,double V2);
    double Current(double t);

public:
    char *Title = "EKVCircuitSimulation.txt";

    vector<double> ODE(double t,vector<double> In);
    EKVcircuit(double a, double b, double c, double d, double e,double s0, double s1,double st){
        C1 = a;
        C2 = b;
        Rl = c;
        Rg = d;
        Vdd= e;
        start = s0;
        stop  = s1;
        dt  = st;
    };
    ~EKVcircuit(){};
    void GoShowEKVcircuit();

};

#endif // EKVCIRCUIT_H_INCLUDED
