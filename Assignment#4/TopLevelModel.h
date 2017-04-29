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

using namespace std;

#ifndef TOPLEVELMODEL_H_INCLUDED
#define TOPLEVELMODEL_H_INCLUDED

class TopLevel
{
    private:
        double dt;
        double dto;
        vector<double> Vo;
        vector<double> V;
        int S;
    public:
        TopLevel(double a,vector<double> b)
        {
            dt  = a;
            dto = a;
            V   = b;
            Vo  = b;
            S   = b.size();
        };
        ~TopLevel(){};
        void Reset()
        {
            V=Vo;
            dt=dto;
        };
        vector<double> BackEuler(double Coef[MaxSize][MaxSize], vector<double> f)
        {
            vector<double> Var;
            double Matrix[MaxSize][MaxSize];
            for(int i=0;i<MaxSize;i++)
            {
                for(int j=0;j<MaxSize;j++)
                {
                    if(i==j)
                    {
                        Matrix[i][j]=1-dt*Coef[i][j];
                    }
                    else
                    {
                        Matrix[i][j]=-dt*Coef[i][j];
                    }
                }
            }
            vector<double> RHS;
            RHS = f;
            for(int i=0;i<S;i++)
            {
                RHS[i] *= dt;
                RHS[i] += V[i];
            }
            DirectFullMatrixSolver BEULER(Matrix,RHS);
            Var  = BEULER.DirectSolve(Matrix,RHS);
            V = Var;
            return Var;
        };
        vector<double> ForwardEuler(double Coef[MaxSize][MaxSize], vector<double> f)
        {
            vector<double> Var(S);
            for(int i=0;i<S;i++)
            {
                Var[i] = dt * f[i];
                for(int j=0;j<S;j++)
                {
                    Var[i] += V[j]* dt * Coef[i][j];
                }
                Var[i] += V[i];
            }
            V = Var;
            return Var;
        };
        vector<double> Trapezoidal(double Coef[MaxSize][MaxSize], vector<double> f)
        {
            vector<double> Var;
            double Matrix[MaxSize][MaxSize];
            for(int i=0;i<MaxSize;i++)
            {
                for(int j=0;j<MaxSize;j++)
                {
                    if(i==j)
                    {
                        Matrix[i][j]=1-dt*Coef[i][j]/2;
                    }
                    else
                    {
                        Matrix[i][j]=-dt*Coef[i][j]/2;
                    }
                }
            }
            vector<double> RHS;
            RHS = f;
            for(int i=0;i<S;i++)
            {
                RHS[i] *= dt;
                RHS[i] += V[i];
                for(int j=0;j<S;j++)
                {
                    RHS[i] += V[j]* dt * Coef[i][j]/2;
                }
            }
            DirectFullMatrixSolver TraEULER(Matrix,RHS);
            Var  = TraEULER.DirectSolve(Matrix,RHS);
            V = Var;
            return Var;
        }
        vector<double> RK34(double Coef[MaxSize][MaxSize], vector<double> f1,vector<double>f2,vector<double>f3, double &h,bool Adaptive,double Tol1,double Tol2)
        {
            vector<double> Var(S);
            vector<double> E(S);
            vector<double> Err(S);
            vector<double> k1(S);
            vector<double> V1(S);
            vector<double> k2(S);
            vector<double> V2(S);
            vector<double> k3(S);
            vector<double> V3(S);
            vector<double> k4(S);
            /* compute k1*/
            for(int i=0;i<S;i++)
            {
                k1[i] = f1[i];
                for(int j=0;j<S;j++)
                {
                    k1[i] += V[j] * Coef[i][j];
                }
                V1[i] = k1[i]*dt/2+V[i];
            }
            /* compute k2 */
            for(int i=0;i<S;i++)
            {
                k2[i] = f2[i];
                for(int j=0;j<S;j++)
                {
                    k2[i] += V1[j] * Coef[i][j];
                }
                V2[i] = k2[i]*dt/2 + V[i];
            }
            /* compute k3*/
            for(int i=0;i<S;i++)
            {
                k3[i] = f2[i];
                for(int j=0;j<S;j++)
                {
                    k3[i] += V2[j] * Coef[i][j];
                }
                V3[i] = k3[i]*dt + V[i];
            }
            /* compute k4*/
            for(int i=0;i<S;i++)
            {
                k4[i] = f3[i];
                for(int j=0;j<S;j++)
                {
                    k4[i] += V3[j] * Coef[i][j];
                }
            }

            /*COMPUTE FINAL RESULT*/
            for(int i=0;i<S;i++)
            {
                Var[i] = V[i]+dt*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
                E[i]   = (-5*k1[i]+6*k2[i]+8*k3[i]-9*k4[i])*h/72;
                Err[i] = E[i]/Var[i];
            }
            V = Var;
            if (Adaptive)
            {
                double Er=0;
                for(int i=0;i<S;i++)
                {
                    Er += Err[i]*Err[i];
                }
                Er = sqrt(Er/S);
                if ( Er > Tol1)
                {
                    h /= 2;
                    dt/= 2;
                }
                else if ( Er < Tol2)
                {
                    h *= 2;
                    dt*= 2;
                }
            }
            return Var;
        };
};

void LoadValue(bool y[MaxSize],vector< vector<double> > &V, vector<double> Input);
void ShowValue(bool y[MaxSize],vector< vector<double> > V);

template <class T>
void SaveValue(bool y[MaxSize],int Iter,int S,vector< vector<double> > V, T *ptr)
{
    for(int i=0;i<MaxSize;i++)
    {
        if (y[i])
        {
            SaveVector(Iter,S,V[i],ptr);
            Iter++;
        }
    }
}

template <class T>
int Integrate(int MethodSelection,int iteration,double a[MaxSize][MaxSize],vector< vector<double> > V, vector<double> X, double start,double stop,double dt, T *ptr)
{
    /* construct Top level model*/
    TopLevel TopOde(dt,X);
    int s=X.size();
    /* set how may vector we have to use to store variables in ODE*/
    bool y[MaxSize];
    (V[0].size()==0)?printf("error in Integrate\n"):y[0]=true;
    for(int i=1;i<MaxSize;i++)
    {
        (V[i].size()==0)?y[i]=false:y[i]=true;
    }

    /* definition of variables we need */
    double t  = start;
    vector<double> time;
    time.push_back(t);
    vector<double> r;
    vector<double> r2;
    vector<double> r3;
    vector<double> Intermedia;
    Intermedia = X;
    /* start main calculation*/
    if ( MethodSelection == 4)       // when time step is adaptive
    {
        double h=dt;
        int i = 0;
        while (t<stop)          //run RK34 with time adaptive
        {
             r = ptr->ODE(t,Intermedia);
            r2 = ptr->ODE(t+0.5*h,Intermedia);
            r3 = ptr->ODE(t+h,Intermedia);
            ExpandVector(r);
            ExpandVector(r2);
            ExpandVector(r3);
            t += h;
            time.push_back(t);
            Intermedia = TopOde.RK34(a,r,r2,r3,h,true,0.1,0.001);
            LoadValue(y,V,Intermedia);
            i++;
        }
    }
    else    // when time step is fixed
    {
        for(int i=0;i<iteration;i++)
        {
             r = ptr->ODE(t,Intermedia);
            r2 = ptr->ODE(t+0.5*dt,Intermedia);
            r3 = ptr->ODE(t+dt,Intermedia);
            ExpandVector(r);
            ExpandVector(r2);
            ExpandVector(r3);
            if (MethodSelection == 0) //Backward
            {
                Intermedia = TopOde.BackEuler(a,r3);
                LoadValue(y,V,Intermedia);
            }
            else if (MethodSelection == 1) //Forward
            {
                Intermedia = TopOde.ForwardEuler(a,r);
                LoadValue(y,V,Intermedia);
            }
            else if (MethodSelection == 2) //Trapezoidal
            {
                Intermedia = TopOde.Trapezoidal(a,r2);
                LoadValue(y,V,Intermedia);
            }
            else if (MethodSelection == 3) //RK34
            {
                Intermedia = TopOde.RK34(a,r,r2,r3,dt,false,0.1,0.001);
                LoadValue(y,V,Intermedia);
            }
            t += dt;
            time.push_back(t);
        }
    }
    //ShowValue(y,V);
    int control = MethodSelection*s;
    SaveValue(y,control,s,V,ptr);
    if (MethodSelection==4)
        SaveVector(1,0,time,ptr);
    return 1;
}
#endif // TOPLEVELMODEL_H_INCLUDED
