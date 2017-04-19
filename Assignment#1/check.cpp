#include <iostream>
#include <cstdio>
#include <cmath>
#include "check.h"
using namespace std;

struct floatingNumber
{
     unsigned int sign;
     unsigned int mantissa;
     unsigned int exponent;
};

floatingNumber Getfloatingformat(float InputValue)
{
    floatingNumber floatform;
    unsigned int crazybinary, mantissa, exponent, sign;
    crazybinary = *((unsigned int *)& InputValue);
    floatform.mantissa = ( crazybinary & 0x7FFFFF);
    crazybinary = crazybinary >> 23;
    floatform.exponent = ( crazybinary  & 0xFF );
    crazybinary = crazybinary >> 8;
    floatform.sign = ( crazybinary & 0x01 );
    return floatform;
}

unsigned int getmantissa(float inPutValue)  //get mantissa from a float
{
    floatingNumber trans=Getfloatingformat(inPutValue);
    return trans.mantissa;
}

unsigned int getexponent(float inPutValue)  //get exponent from a float
{
    floatingNumber trans=Getfloatingformat(inPutValue);
    return trans.exponent;
}

unsigned int getsign(float inPutValue)      //get sign from a float
{
    floatingNumber trans=Getfloatingformat(inPutValue);
    return trans.sign;
}

bool intOverFlow(int inputValue,int sign)            //judge integer overflow
{
    if (sign>=0)
    {
        if (inputValue<0)
        {
            return true;
        }
        else return false;
    }
    else
    {
        if (inputValue>0)
        {
            return true;
        }
        else return false;
    }
}

bool CheckInf(float inputValue)
{
    floatingNumber floatform;
    floatform = Getfloatingformat(inputValue);
    if (floatform.mantissa==0 & floatform.exponent==255 & floatform.sign==0)
        return true;
    else return false;
}

bool CheckNInf(float inputValue)
{
    floatingNumber floatform;
    floatform = Getfloatingformat(inputValue);
    if (floatform.mantissa==0 & floatform.exponent==255 & floatform.sign==1)
        return true;
    else return false;
}

bool CheckNaN(float inputValue)
{
    floatingNumber floatform;
    floatform = Getfloatingformat(inputValue);
    if (floatform.mantissa!=0 & floatform.exponent==255)
        return true;
    else return false;
}

bool CheckPositiveZero(float inputValue)
{
    floatingNumber floatform;
    floatform = Getfloatingformat(inputValue);
    if (floatform.mantissa==0 & floatform.exponent==0 & floatform.sign==0)
        return true;
    else return false;
}

bool CheckNegativeZero(float inputValue)
{
    floatingNumber floatform;
    floatform = Getfloatingformat(inputValue);
    if (floatform.mantissa==0 & floatform.exponent==0 & floatform.sign==1)
        return true;
    else return false;
}

bool ToleraBySoftLanding(float inputValue)
{
    const float slimit=pow(2,-149);
    if (inputValue < slimit)
        return true;
    else return false;
}

