/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * main
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include "PerformValidation.h"
#include "Fig3Circuit.h"
#include "EKVcircuit.h"

using namespace std;

int main()
{
    /* perform validation */
    printf("show the validation of ODE solver by test dxdt = 4e^(0.8t)-0.5x: \n");
    GoTest(1,0,5);
    printf("\n\n");

    /* show fig3 circuit value of V1 V2 */
    printf("show fig3 circuit V1 && V2 with all 5 method:\n");
    BasicCircuit Fig3(pow(10,-12),pow(10,-12),10000,10000,10000,0,100*pow(10,-9),0.2*pow(10,-9));
    Fig3.GoShowFig3V1V2();
    printf("\n\n");

    /* show EKV circuit value of V1 V2 */
    printf("show EKV circuit V1 && V2 with Forward and RK34:\n");
    EKVcircuit Fig5(pow(10,-12),pow(10,-12),10000,10000,5,0,100*pow(10,-9),0.2*pow(10,-9));
    Fig5.GoShowEKVcircuit();
}
