/**
 * Assignment 3
 * Chen Yu(cy436)
 * completed on 2017.04.02
 *
 * main code
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "MatrixSolver.h"
#include "ExtractParameter.h"
#include "PerformValidation.h"
#include <string>
#include "test.h"
#include "EKVModel.h"

using namespace std;

int main()
{
    /**
     * sample test for up to 4 dim matrix solver
     */
//    double A[5][5]={{1,2,0,0,0},
//                    {4,5,6,0,0},
//                    {0,7,8,0,0},
//                    {0,0,0,10,0},
//                    {0,0,0,0,0}};
//    vector<double> X(5);
//    for(int i=0;i<5;i++)
//        X[i]=i;
//    DirectFullMatrixSolver DMS(A,X);
//    DMS.DisplayVector(DMS.DirectSolve(A,X));

    GoTestMatrixSolver();
    /**
     *  task 2
     *  perform validation of the power law equation
     */


    /**perform validation
     */
    PerformValidation Pv;
    Pv.runExtraction();

    /**read in EKV Data
     */
    ifstream fin("outputNMOS.txt");
    if ( ! fin.is_open() )
    {
        cout << "Could not open file!" << '\n';
    }

    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(256, '\n');

    double receiver1,receiver2,receiver3;                   // 3 receiver to store Id, Vgs and Vds
    vector<double> Id,Vgs,Vds;
    for(int i=0;i<1010;i++)
    {
        fin >> receiver1 >> receiver2 >> receiver3;
        Id.push_back(receiver3);
        Vgs.push_back(receiver1);
        Vds.push_back(receiver2);
    }

    /**
     * compute EKV equation result
     */
    printf("-------------------------------\n");
    printf("EKV extraction start:\n");
    printf("task 4:\n");
    Task4 EKV4problem(Id,Vgs,Vds,pow(10,-7),1.1,1.1);
    EKV4problem.runExtract();

    printf("task 5:\n");
    Task5 EKV5problem(Id,Vgs,Vds,pow(10,-7),1.1,1.1);
    EKV5problem.runExtract();
//
    /**
     * full search
     */
    vector<double> Is(8);
    vector<double> Kappa(7);
    vector<double> Vth(10);
    Is[0] = pow(10,-8);
    Is[1] = 3*pow(10,-8);
    Is[2] = pow(10,-7);
    Is[3] = 3*pow(10,-7);
    Is[4] = pow(10,-6);
    Is[5] = 3*pow(10,-6);
    Is[6] = pow(10,-5);
    Is[7] = 3*pow(10,-6);
    Kappa[0] = 0.2;
    Kappa[1] = 0.3;
    Kappa[2] = 0.4;
    Kappa[3] = 0.5;
    Kappa[4] = 0.6;
    Kappa[5] = 0.7;
    Kappa[6] = 0.8;
    Vth[0] = 1.1;
    Vth[1] = 1.2;
    Vth[2] = 1.3;
    Vth[3] = 1.4;
    Vth[4] = 1.5;
    Vth[5] = 1.6;
    Vth[6] = 1.7;
    Vth[7] = 1.8;
    Vth[8] = 1.9;
    Vth[9] = 2.0;
    vector<double> FullParamResult;
    printf("-------------------------------\n");
    printf("full search start:\n");
     printf("task 4:\n");
    FullParamResult = EKV4problem.FullParameterSearch(Is,Kappa,Vth);
    printf("Smallest value happened @ Is=%.9lf, Kappa=%lf, Vth=%lf\n",FullParamResult[0],FullParamResult[1],FullParamResult[2]);
    printf("Second Smallest value happened @ Is=%.9lf, Kappa=%lf, Vth=%lf\n",FullParamResult[3],FullParamResult[4],FullParamResult[5]);

     printf("task 5:\n");
    FullParamResult = EKV5problem.FullParameterSearch(Is,Kappa,Vth);
    printf("Smallest value happened @ Is=%.9lf, Kappa=%lf, Vth=%lf\n",FullParamResult[0],FullParamResult[1],FullParamResult[2]);
    printf("Second Smallest value happened @ Is=%.9lf, Kappa=%lf, Vth=%lf\n",FullParamResult[3],FullParamResult[4],FullParamResult[5]);

}
