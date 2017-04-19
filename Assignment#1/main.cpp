/*
    Author: Chen Yu
    Date: Feb.16th, 2017
    netID: cy436
*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdio.h>
#include <climits>
#include <limits>
#include <stdlib.h>
#include <malloc.h>
#include "generate.h";
#include "check.h"
#include <float.h>
#include <fstream>


using namespace std;
#define PiDigits 30
ofstream file_writer( "output.txt" );

int main()
{
    FILE * pFile;
    pFile = fopen ("output_long.txt","w");

    /*int overflow by using Fabonacci*/
    printf("int overflow by using Fabonacci Begins\n");
    file_writer << "int overflow by using Fabonacci Begins"<<endl;
    bool Overflow=0;
    printf("Positive addition\n");
    file_writer << "Positive addition"<<endl;
    Overflow = Fabo(1,2);
    file_writer << "The overflow         "<< (Overflow?"exist":"not exist" )<<endl;

    printf("Negative addition\n");
    file_writer << "Negative addition"<<endl;
    Overflow = Fabo(-2,-3);
    file_writer << "The overflow         "<< (Overflow?"exist":"not exist" )<<endl;
    printf("\n");
    file_writer << endl;

    /*int divided by zero*/
    printf("int divided by zero Begins\n");
    file_writer << "int divided by zero Begins"<<endl;

    try
    {
        float dividend,divisor;
        dividend = 5;
        divisor  = 0;
        if (divisor == 0)
            throw dividend/divisor;
        else printf("dividend/divisor=%f\n",dividend/divisor);
    }
    catch(float num)
    {
        printf("the divisor is zero, it shows %f\n",num);
        file_writer << "The divisor is zero, integer divided by zero is "<< num <<endl;
    }
    printf("\n");
    file_writer << endl;

    /*Float overflow*/
    printf("Float overflow Detection Begins\n");
    file_writer << "Float overflow Detection Begins"<<endl;
    float OverFlowFloat[4];
    OverFlowFloat[0]=2;
    OverFlowFloat[1]=-2;
    OverFlowFloat[2]=0.2;
    OverFlowFloat[3]=-0.2;
    int iteration=1;
    for(int i=0;i<4;i++)
    {
        for(int iteration;iteration<100;iteration++)
        {
            printf("Current value is %f\n",OverFlowFloat[i]);
            OverFlowFloat[i]= pow(OverFlowFloat[i], 3);
            if (OverFlowFloat[i]==pow(OverFlowFloat[i], 3))
                break;
        }
        printf("overfloat value is %f at iteration=%d\n",OverFlowFloat[i],iteration);
        file_writer << "overfloat test "<< i <<"    "<<(iteration==100?"fail":"pass")<<endl;
    }
    printf("\n");
    file_writer << endl;

    /*Float limits generation*/
    float limits[5];
    limits[0]=FloatInfGenerate();
    limits[1]=FloatNinfGenerate();
    limits[2]=FloatPosiZeroGenerate();
    limits[3]=FloatNegaZeroGenerate();
    limits[4]=FloatNaNGenerate();

    /*INF and NINF in 1/x,sin(x),exp(x)*/
    printf("INF and NINF in 1/x,sin(x),exp(x)\n");
    file_writer << "INF and NINF in 1/x,sin(x),exp(x) Begins"<<endl;
    int passed_tests;
    for(int i=0;i<4;i++)
    {
        passed_tests=0;
        printf("1/%f = %f;  ",limits[i],1/limits[i]);
        limits[(i+2)%4]==1/limits[i]?passed_tests++:0;
        printf("sin(%f) = %f;  ",limits[i],sin(limits[i]));
        if ((i==0 || i==1) && CheckNaN(sin(limits[i])))
            passed_tests++;
        else if (((i==2 || i==3)) && (limits[i]==limits[i]))
            passed_tests++;
        printf("exp(%f) = %f\n",limits[i],exp(limits[i]));
        if ((i==0) && CheckInf(exp(limits[i])))
            passed_tests++;
        else if ((i==1) && CheckPositiveZero((exp(limits[i]))))
            passed_tests++;
        else if (((i==2)||(i==3)) && (exp(limits[i])==1))
            passed_tests++;
        file_writer <<"1/x,sin(x),exp(x) at "<<limits[i]<<" passed:  "<<passed_tests<<" (in 3)"<<endl;
    }
    printf("\n");
    file_writer << endl;

    /*Signed zero in limLog,limsinx/x*/
    printf("Signed zero in limLog,limsinx/x Begins\n");
    file_writer << "Signed zero in limLog,limsinx/x Begins"<<endl;
    for(int i=2;i<4;i++)
    {
        printf("Log(x) = %f at %f;  ",log(limits[i]),limits[i]);
        printf("sin(x)/x = %f at %f\n",sin(limits[i])/limits[i],limits[i]);
    }
    printf("sin(x)/|x| = %f at %f\n",sin(limits[3])/abs(limits[3]),limits[3]);
    printf("\n");
    file_writer << endl;

    /*Nan Detecting*/
    float nan=FloatNaNGenerate();
    passed_tests=0;
    printf("Nan Detecting Begins\n");
    file_writer << "Nan Detecting Begins"<<endl;
    for(int i=0;i<4;i++)
    {
        if (CheckNaN(nan+limits[i]))
        {
            printf("nan+%f = nan\n",limits[i]);
            passed_tests++;
        }
        if (CheckNaN(nan*limits[i]))
        {
            printf("nan*%f = nan\n",limits[i]);
            passed_tests++;
        }
        if (CheckNaN(nan-limits[i]))
        {
            printf("nan-%f = nan\n",limits[i]);
            passed_tests++;
        }

        if (CheckNaN(nan/limits[i]))
        {
            printf("nan/%f = nan\n",limits[i]);
            passed_tests++;
        }
    }
    file_writer << "Nan Detecting test passed:  "<<passed_tests<<" (in 16)"<<endl;
    printf("\n");
    file_writer << endl;

    /*Soft Landing*/
    printf("Soft Landing Begins\n");
    file_writer << "Soft Landing Begins"<<endl;
    float x,y;
    //subtraction
    x=1.2;
    y=1.3;
    for(int i=1;i<40;i++)
    {
        printf("x-y=%f;   \n",x-y);
        x/=100;
        y/=100;
        if (x-y==0)
            break;
    }
    if (x-y<pow(2,-149))
    {
        printf("soft landing subtraction test pass\n");
        file_writer << "Soft Landing subtraction test pass"<<endl;
    }
    else
    {
        printf("soft landing subtraction test failed\n");
        file_writer << "Soft Landing subtraction test failed"<<endl;
    }

    //division
    x=1.2;
    y=1.3;
    for(int i=1;i<40;i++)
    {
        printf("x/y=%f;   \n",x/y);
        x/=100;
        y/=100;
        if (x/y==1)
            break;
    }
    if (x-y<pow(2,-149))
    {
        printf("soft landing division test pass\n");
        file_writer << "Soft Landing division test pass"<<endl;
    }
    else
    {
        printf("soft landing division test failed\n");
        file_writer << "Soft Landing division test failed"<<endl;
    }

    //sin
    x=1.0;
    for(int i=1;i<40;i++)
    {
        printf("sin(1.234567890123*x)/x=%f;   \n",sin(1.23456789012345*x)/x);
        x/=100;
        if (sin(1.23456789012345*x)/x==1.23456789012345)
            break;
    }
    if (sin(1.23456789012345*x)/x<pow(2,-149))
    {
        printf("soft landing sin test pass\n");
        file_writer << "Soft Landing sin test pass"<<endl;
    }
    else
    {
        printf("soft landing sin test failed\n");
        file_writer << "Soft Landing sin test failed"<<endl;
    }

    printf("\n");
    file_writer << endl;

    /*pi generation*/
    GeneratePi();
    file_writer << "pi generate successfully by using <pi=4*(1-1/3+1/5-1/7+1/9...)>"<<endl;


   return 0;
}
