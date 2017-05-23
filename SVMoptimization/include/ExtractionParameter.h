/** ExtractionParameter
 *
 *  Solve for the local minimum
 *  Extra module: Trust-Tech
 *  Include LOS test
 *
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "MatrixOperate.h"

#ifndef EXTRACTIONPARAMETER_H
#define EXTRACTIONPARAMETER_H

using namespace std;

template <typename T>
class ExtractionParameter
{
    public:
        /*constructor*/
        ExtractionParameter(T *ptr)
        {
            /**
            * Initialize starting point with a guess (1,1,....,1,1)
            *
            */
            vector<double> temp(1);
            temp[0] = 1;
            for(int i=0;i<ptr->DSize;i++)
            {
                a.push_back(temp);                  // a[i][0]   = 1
                TempParam.push_back(1);     // Temp[i] = 1
                ExitPoint.push_back(temp);   // exit point[0] == initial guess
            }
            /*store ptr point to SVM*/
            ptr = ptr;
            vector<vector<double> > A(ptr->DSize, vector<double>(ptr->DSize));
            Hess = A;
            vector<double> B(ptr->DSize,0);
            Jacobi      = B;
            Gradient   = B;
        };

        /*destructor*/
         virtual ~ExtractionParameter()
        {
         //   delete ptr;
        };

        vector<double> GoExtract(T *ptr)
        {
            vector<double> da;
            vector<double> delta;
            delta.push_back(0);
            double dsum;
            int loop=0;
            while(loop<200)
            {
                /**
                 *  Using Newtons Methods
                 *
                 */
                dsum = 0; //reset new delta
                Jacobi = PartialDeriv(ptr,TempParam);       //Jacobi f vector on RHS
                HMatrix(ptr);                                                  //Hess matrix LHS
                MatrixOperate< vector<vector<double> > > DeltaA(Hess, Jacobi);
                da = DeltaA.DirectSolve(Hess,Jacobi);       //solve Hess x da = Jacobi
                for(int i=0;i<ptr->DSize;i++)
                {
                    TempParam[i] -= da[i];
                    a[i].push_back(da[i]);
                    dsum += pow(da[i],2)/pow(TempParam[i],2);//dsum = da(0)^2/a(0)^2 + da(1)^2/a(1)^2 ... da(n)^2/a(n)^2
                }
                delta.push_back(dsum);
                //DisplayVector(TempParam);
                //printf("%lf\n",ptr->objective(TempParam));
                if (dsum<pow(10,-14))
                {
                    break;
                    Gradient = da;
                }
                loop++;
            }
            return TempParam;
        };
        int TrustTechModule()
        {
            vector<double> Temp;
            vector<double> Prev;
            vector<double> Temp2;
            vector<double> Prev2;
            int Find=0;
            for(int i=0;i<ptr->DSize;i++)
            {
                /* set 2 direction: positive (increase) or negative (decrease) iteratively along certain feature to find global minimum*/
                int timer = 0;                                                                                              // set a timer to limit max search time
                Prev   = TempParam;
                Temp = TempParam;
                Prev2 = TempParam;
                Temp2= TempParam;
                double step = 0.001;                                                                                 // initialize changing step = 0.001
                double step2 = 0.001;                                                                               // initialize changing step2 = 0.001
                double Diff,Diff2;
                while(timer<100)                                                                                     // set max search times: 150
                {
                    Diff =  ptr->objective(Temp) - ptr->objective(Prev);
                    Diff2 =  ptr->objective(Temp2) - ptr->objective(Prev2);

                    /*break when detect exit point*/
                    if (( Diff < 0) || (Diff2 < 0))                                              // if I see obj value is no longer increasing, I know I got an exit point
                    {
                        (Diff<0)?ExitPoint.push_back(Temp):ExitPoint.push_back(Temp2);                            // push_back Exit point, positive part or negative part?
                        Find ++;                                                                                                                                    // # of Found exit point increment
                        break;
                    }

                    /*update one iteration*/
                    Prev[i]       = Temp[i];
                    Temp[i]   += step;
                    Prev2[i]     = Temp2[i];
                    Temp2[i] += step2;

                    /*adjust changing step*/
                    if (( ptr->objective(Temp) - ptr->objective(Prev) ) > Diff)                  //when obj increasing faster along i th dimension,
                    {
                        step /=2;                                                                             // slow the increasing step
                    }
                    else if (( ptr->objective(Temp) - ptr->objective(Prev) ) < Diff)         //when obj increasing slower along i th dimension
                    {
                        step *= 2;                                                                           // speed up the increasing step
                    }

                    /*adjust changing step2*/
                    if (( ptr->objective(Temp2) - ptr->objective(Prev2) ) > Diff2)          //when obj increasing faster along i th dimension,
                    {
                        step2 /=2;                                                                          // slow the increasing step
                    }
                    else if (( ptr->objective(Temp2) - ptr->objective(Prev2) ) < Diff2) //when obj increasing slower along i th dimension
                    {
                        step2 *= 2;                                                                       // speed up the increasing step
                    }
                }
            }
            return Find;
        };

        void Reset(int currentExit)                                                            // reset to current exit point
        {
            TempParam = ExitPoint[currentExit];
        }

        bool TestExtract(T *ptr)
        {
            bool LOSisTrue = true;
            vector<double> temp;
            for(int i=0;i<ptr->DSize;i++)
            {
                temp = TempParam;
                temp[i] *= 1.001;
                if ((ptr->objective(temp) ) < (ptr->objective(TempParam) ) )               // if any direction has a continuous result less than LOS, then the LOS is wrong
                {
                    LOSisTrue = false;
                    break;
                }
            }
            return LOSisTrue;
        };

        /*update Jacobi vector*/
        vector<double>  PartialDeriv(T *ptr,vector<double> param)
        {
            vector<double> result(ptr->DSize);
            vector<double> temp;
            for(int i=0;i<ptr->DSize;i++)
            {
                temp = param;
                temp[i] *= 1.0001;
                result[i] = (ptr->objective(temp)-ptr->objective(param))/(0.0001*param[i]);   // dobj/da(i) = obj(1.0001*a1,a2,a3...)-obj(a1,a2,...)   /0.0001a1
            }
            return result;
        };

        /*update Hess Matrix*/
        void HMatrix(T *ptr)
        {
            vector<double> temp;
            for(int i=0;i<ptr->DSize;i++)                   //row increasing
            {
                for(int j=0;j<ptr->DSize;j++)               //col increasing
                {
                    temp      = TempParam;
                    temp[j]  *= 1.0001;
                    Hess[i][j]= (PartialDeriv(ptr,temp)[i]-PartialDeriv(ptr,TempParam)[i])/(0.0001*TempParam[j]);
                }
            }
        };
    protected:

    private:
        vector<double>      Gradient;
        vector< vector<double> > a;
        vector< vector<double> > ExitPoint;
        vector<double> TempParam;
        vector< vector<double> > Hess;
        vector<double> Jacobi;
        T *ptr;
};

#endif // EXTRACTIONPARAMETER_H
