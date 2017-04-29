/**
 * Assignment 4
 * Chen Yu(cy436)
 * completed on 2017.04.21
 *
 * task 3
 * perform validation
 * ode(x,t)= 4*e^(0.8t)-0.5x
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "MatrixSolver.h"
#include "TopLevelModel.h"

using namespace std;

double ODE(double t)
{
    return 4*exp(0.8*t);
}

double GroundTruth(double t)
{
    return 4*(exp(0.8*t)-exp(-0.5*t))/1.3 + 2*exp(-0.5*t);
}

void RunTest(int TestNumber, int iteration,double a[MaxSize][MaxSize],vector<double> r,double start,double stop,double dt);

void GoTest(double dt, double start, double stop)
{
    int iteration = int((stop - start)/dt);
    double a[MaxSize][MaxSize] = {{-0.5,0,0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0},
                                  {0   ,0,0,0,0}};
    vector<double> r(5);
    r[1]=0; r[2]=0; r[3]=0; r[4]=0;

    /**
     * Backward Euler
     */
    printf("Backward Euler\n");
    RunTest(0, iteration,a, r,start,stop,dt);

    /**
     * Forward Euler
     */
    printf("Forward Euler\n");
    RunTest(1, iteration,a, r,start,stop,dt);

    /**
     * Trapezoidal Euler
     */
    printf("Trapezoidal Euler\n");
    RunTest(2, iteration,a, r,start,stop,dt);

    /**
     * One step RK34
     */
    printf("fixed dt RK34\n");
    RunTest(3, iteration,a, r,start,stop,dt);

    /**
     * Adaptive RK34
     */
    printf("Adaptive RK34\n");
    RunTest(4, iteration,a, r,start,stop,dt);

}

void RunTest(int TestNumber,int iteration,double a[MaxSize][MaxSize],vector<double> r,double start,double stop,double dt)
{
    vector<double> X;
    X.push_back(2);
    TopLevel Test(dt,X);
    vector<double> xError;
    xError.push_back(0);
    double t  = start;
    vector<double> time;
    time.push_back(t);
    vector<double> r2(5);
    vector<double> r3(5);
    r2 = r;
    r3 = r;
    if ( TestNumber == 4)
    {
        double h=dt;
        int i = 0;
        while (t<stop)
        {
             r[0] = ODE(t);
            r2[0] = ODE(t+0.5*h);
            r3[0] = ODE(t+h);
            X.push_back(Test.RK34(a,r,r2,r3,h,true,0.1,0.001)[0]);
            t += h;
            time.push_back(t);
            i++;
            xError.push_back(abs((X[i]-GroundTruth(t))/GroundTruth(t)));
        }
        printf("time steps\n");
        DisplayVector(time);
    }
    else
    {
        for(int i=0;i<iteration;i++)
        {
            r[0] = ODE(i*dt);
            r2[0] = ODE(i*dt+0.5*dt);
            r3[0] = ODE(i*dt+dt);
            if (TestNumber == 0)
            {
                X.push_back(Test.BackEuler(a,r3)[0]);
            }
            else if (TestNumber == 1)
            {
                X.push_back(Test.ForwardEuler(a,r)[0]);
            }
            else if (TestNumber == 2)
            {
                X.push_back(Test.Trapezoidal(a,r2)[0]);
            }
            else if (TestNumber == 3)
            {
                X.push_back(Test.RK34(a,r,r2,r3,dt,false,0.1,0.001)[0]);
            }
            t += dt;
            xError.push_back(abs((X[i+1]-GroundTruth(t))/GroundTruth(t)));
        }
    }
    printf("x value\n");
    DisplayVector(X);
    printf("xError in %\n");
    DisplayVector(xError);
}
