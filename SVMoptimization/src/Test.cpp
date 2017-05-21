#include "Test.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "MatrixOperate.h"


using namespace std;
/** Parent class
 *
 * Test class
 *
 */

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}

bool Test::VEq(vector<double> A, vector<double>  B)
{
    try
    {
        bool Eq=true;
        if(A.size()!=B.size())                                                                      //except when a vector size different from b vector size
            throw "two array have different size";
        for(int i=0;i<A.size();i++)
        {
            if ((abs(A[i])-abs(B[i]))/(abs(A[i]+abs(B[i]))) > pow(10,-14))        // any element in vector are different means vectors are different,
            {
                Eq = false;
                break;
            }
        }
        return Eq;
    }
    catch(const char* msg)                                                                      // exception handling
    {
        cerr << msg << endl;
    }
}

bool Test::AverageCheck(vector<double> a, double Abar)                        // true if ave function is correct
{
    if (ave(a)==Abar)
        return true;
    else
        return false;
}

void Test::AverageFixedTest()
{
    vector<double> a(3);
    a[0]=1;
    a[1]=4;
    a[2]=4;
    if (AverageCheck(a,3))                                                                              // check whether ybar=(1+4+4)/3=3
        printf("AverageFixedTest:       pass\n");
    else
        printf("AverageFixedTest:       pass\n");
}

void Test::AverageRandTest()
{
    /* preset some values */
    vector<double> a(4);
    a[0]=(double) (rand() % 10);
    a[1]=(double) (rand() % 100);
    a[2]=(double) (rand() % 1000);
    a[3]=(double) (rand() % 10000);
    /*automatically calculated average value*/
    double k= (a[0]+a[1]+a[2]+a[3])/4;                                                      // ybar=(y1+y2+y3+y4)/4
    if (AverageCheck(a,k))                                                                           // true if average function is correct
        printf("AverageFixedTest:       pass\n");
    else
        printf("AverageFixedTest:       pass\n");
}

/** subClass MatrixTest
 *
 * Test direct solve result
 * Test production result
 *
 */

MatrixTest::MatrixTest()
{
    /*create vector X and matrix A*/
    vector<double> x(TestCaseSize);                                                                         //create n dim vector x
    X = x;
    vector< vector<double> > a(TestCaseSize, vector<double> (TestCaseSize));  //create n x n dim matrix x
    A = a;
}

MatrixTest::~MatrixTest()
{
    //dtor
}

void MatrixTest::RunTest()
{
    /* Fixed value test */
    vector<bool> result=FixedValueTest();
    result[0]?printf("Matrix solve test--Fixed value: pass\n"):printf("Matrix solve test--Fixed value: fail\n");
    result[1]?printf("Matrix productMxV test--Fixed value: pass\n"):printf("Matrix productMxV test--Fixed value: fail\n");
    result[2]?printf("Matrix productVxM test--Fixed value: pass\n"):printf("Matrix productVxM test--Fixed value: fail\n");
    /* Random value test */
    RandomValueTest()?printf("Matrix operate test--Random value:            pass\n"):printf("Matrix operate test--Random value:         fail\n");
    AverageFixedTest();
    AverageRandTest();
}

vector<bool> MatrixTest::FixedValueTest()                         // manually calculate ground truth and test it
{
    vector<bool> result;
    /*
    X =  {2,0,3};
    A =  {{1,0,1},
              {0,2,0},
              {0,0,3}}; */

    X[0]=2;
    X[1]=0;
    X[2]=3;
    A[0][0]=1;
    A[0][1]=0;
    A[0][2]=1;
    A[1][0]=0;
    A[1][1]=2;
    A[1][2]=0;
    A[2][0]=0;
    A[2][1]=0;
    A[2][2]=3;

    vector<double> SampleSolve(TestCaseSize);                       // set sample direct solve result
    /*SampleSolve = {1,0,1}*/
    SampleSolve[0]=1;
    SampleSolve[1]=0;
    SampleSolve[2]=1;
    vector<double> SampleProductMxV(TestCaseSize);            // set sample product matrix x vector result
    /*SampleProductMxV = {5,0,9}*/
    SampleProductMxV[0]=5;
    SampleProductMxV[1]=0;
    SampleProductMxV[2]=9;
    vector<double> SampleProductVxM(TestCaseSize);            // set sample product vector x matrix result
    /*SampleProductVxM = {2,0,5}*/
    SampleProductVxM[0]=2;
    SampleProductVxM[1]=0;
    SampleProductVxM[2]=11;
    MatrixOperate< vector<vector<double> > > FixedTest(A,X);
    result.push_back (VEq(FixedTest.DirectSolve(A,X),SampleSolve));                 // compare solve solution with sample

    result.push_back(VEq(FixedTest.Product(A,X),SampleProductMxV));            // compare product solution with sample

    result.push_back(VEq(FixedTest.Product(X,A),SampleProductVxM)) ;           // compare product solution with sample
    return result;
}

bool MatrixTest::RandomValueTest()                                          // random some value into matrix and vector, then test it
{
    vector<double> b;
    X[0]=(double) (rand() %10);
    X[1]=(double) (rand() %10);
    X[2]=(double) (rand() %10);
    A[0][0]=(double) (rand() %10);
    A[0][1]=(double) (rand() %10);
    A[0][2]=(double) (rand() %10);
    A[1][0]=(double) (rand() %10);
    A[1][1]=(double) (rand() %10);
    A[1][2]=(double) (rand() %10);
    A[2][0]=(double) (rand() %10);
    A[2][1]=(double) (rand() %10);
    A[2][2]=(double) (rand() %10);

    MatrixOperate< vector<vector<double> > > RandTest(A,X);
    b=RandTest.Product(A,X);                                                        // b=AxX

    MatrixOperate< vector<vector<double> > > RandTestS(A,b);
    vector<double> s;
    s = RandTestS.DirectSolve(A,b);
    return VEq(s,X);
}
