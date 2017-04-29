/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 4
 * Do ode solver for figure 3 circuit
 * ode: dV1/dt = -(1/C1R1+1/C1R2)*V1 +1/C1R2 *V2 + i(t)/C1
 *      dV2/dt = 1/C2R2 * V1 -(1/C2R2+C2R3)*V2
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include <string>



#ifndef FIG3CIRCUIT_H_INCLUDED
#define FIG3CIRCUIT_H_INCLUDED

using namespace std;


class BasicCircuit
{
private:
    double C1,C2,R1,R2,R3;
    double start,stop,dt;
    double Current(double t);
public:

    char *Title = "Fig3CircuitSimulation.txt";

    vector<double> ODE(double t,vector<double> In);
    void Testit();
    BasicCircuit(double a, double b, double c, double d, double e,double s0, double s1,double st){
        C1 = a;
        C2 = b;
        R1 = c;
        R2 = d;
        R3 = e;
        start = s0;
        stop  = s1;
        dt  = st;
    };
    ~BasicCircuit(){};
    void GoShowFig3V1V2();

};

#endif // FIG3CIRCUIT_H_INCLUDED
