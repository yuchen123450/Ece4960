#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED
unsigned int getmantissa(float inPutValue);
unsigned int getexponent(float inPutValue);
unsigned int getsign(float inPutValue);
bool intOverFlow(int inputValue,int sign);
bool CheckInf(float inputValue);
bool CheckNInf(float inputValue);
bool CheckNaN(float inputValue);
bool CheckPositiveZero(float inputValue);
bool CheckNegativeZero(float inputValue);
bool ToleraBySoftLanding(float inputValue);

#endif // CHECK_H_INCLUDED
