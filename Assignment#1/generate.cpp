#include <iostream>
#include <cstdio>
#include <cmath>
#include <climits>
#include <limits>
#include "generate.h"
#include "check.h"

using namespace std;

bool Fabo(int initial0,int initial1)
{
   int sign=initial0;
   for(int i=0;i<50;i++)
   {
        printf("%d; ",initial0);
        initial0 += initial1;
        if (intOverFlow(initial0,sign))
        {
            printf("\n");
            printf("there exist overflow at %d number with %d\n",2*i+1,initial0);
            return 1;
        }
        printf("%d; ",initial1);
        initial1 += initial0;
        if (intOverFlow(initial1,sign))
        {
            printf("\n");
            printf("there exist overflow at %d number with %d\n",2*i+2,initial1);
            return 1;
        }
   }
        printf("%d\n; ",initial0);
        printf("%d\n; ",initial1);
    return 0;
}
float FloatInfGenerate()
{
    return std::numeric_limits<float>::infinity();
}
float FloatNinfGenerate()
{
    return 0-FloatInfGenerate();
}
float FloatNaNGenerate()
{
    return FloatInfGenerate()-FloatInfGenerate();
}

float FloatPosiZeroGenerate()
{
    return 1/FloatInfGenerate();
}
float FloatNegaZeroGenerate()
{
    return 1/FloatNinfGenerate();
}







/*generate pi by using array*/
void ArrayDivision(int input[40],int divisor, int output[40])
{
    int dividend[40];
    for(int i=0;i<40;i++)
        dividend[i]=input[i];
    for(int i=0;i<40;i++)
    {
        output[i]=dividend[i]/divisor;
        dividend[i]=dividend[i] % divisor;
        dividend[i+1] += dividend[i]*10;
    }
    output[39]=dividend[39]/divisor;
}
void PrintValue(int input[40])
{
    printf("current variable=%d.",input[0]);
    for(int i=1;i<40;i++)
    {
        printf("%d",input[i]);
    }
    printf("\n");
}
void ArrayInvers(int input[40])
{
    for(int i=0;i<40;i++)
        input[i]=-input[i];
}
void ArrayAdd(int input1[40],int input2[40],int output[40])
{
    int c=0;
    int CurrentDigit=0;
    for(int i=40;i>=0;i--)
    {
        CurrentDigit=input1[i]+input2[i]+c;
        if (CurrentDigit>=0)
        {
            output[i]=CurrentDigit % 10;
            c= CurrentDigit / 10;
        }
        else
        {
            output[i]=10-((-CurrentDigit) % 10);
            c=-(-CurrentDigit)/10-1;
        }
    }
    printf("\n");
}
void ArrayZero(int input[40])
{
    for(int i=0;i<40;i++)
        input[i]=0;
}
void Display(int input[40])
{
    printf("pi=%d.",input[0]);
    for(int i=1;i<40;i++)
    {
        printf("%d",input[i]);
    }
    printf("\n");
}
void GeneratePi()
{
    int pi[40];
    int Four[40];
    int output[500][40];
    int sign=1;
    int divisor=1;
    /*initialize*/
    ArrayZero(pi);
    ArrayZero(Four);
    Four[0]=4;
    /*division iterative*/
    for(int i=0;i<500;i++)
    {
        ArrayDivision(Four,divisor,output[i]);
        PrintValue(output[i]);
        divisor += 2;
    }
    /*addition iterative*/
    for(int i=0;i<500;i++)
    {
        if (sign==1)
            ArrayAdd(pi,output[i],pi);
        else if (sign == -1)
        {
            ArrayInvers(output[i]);
            ArrayAdd(pi,output[i],pi);
        }
        Display(pi);
        sign *= -1 ;
    }
//    for(int i=0;i<500;i++)
//        PrintValue(output[i]);      used to detect whether every even iteration execute substraction instead of addition

    /*display*/
    Display(pi);
}

