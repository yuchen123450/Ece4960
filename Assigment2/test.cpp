#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include "test.h"
#include "lib.h"

using namespace std;


bool pass[9];

vector<double> createb1(int num,int VecSize)
{
    vector<double> b(VecSize);
    for(int i=0;i<VecSize;i++)
    {
        if (num!=0)
            i==num-1?b[i]=1:b[i]=0;
        else if (num==0)
            b[i]=1;
    }
    return b;
}

void testAddition()
{
    vector<double> X1(5);
    vector<double> X2(5);
    vector<double> result(5);
    for(int i=0;i<5;i++)
    {
        X1[i]=i;
        X2[i]=5-i;
    }
    result=Addition(X1,X2);
    DisplayVector(result);
    for(int i=0;i<5;i++)
    {
        if (result[i]==5)
            printf("addition test col %d match\n",i);
    }
}

void FullProduct(double A[5][5],vector<double> X,vector<double> &b)
{
    printf("b=\n");
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            b[i]+= A[i][j]*X[j];
        }
        printf("    %.2lf\n",b[i]);
    }
}

bool testproduct(ComprassTypeMatrix Input,double A[5][5], vector<double> X, vector<double> &b)
{
    vector<double> bcomp(5);
    bool pass=true;
    b=Product(Input,X);
    if (b.size()==X.size())
        printf("size match \n");
    FullProduct(A,X,bcomp);
    for(int i=0;i<5;i++)
    {
        if (bcomp[i]!=b[i])
        {
            pass=false;
            break;
        }
    }
    if (pass)
        printf("Product test value match\n");
    else printf("product test failed\n");
    return pass;
}


double SecondNorm(ComprassTypeMatrix SparseM, double A[5][5])
{
    bool NonZeroHaveSameIndi;
    double norm=0;
    if (SparseM.Rank!=5)
    {
        printf("the size of sparse matrix is not 5\n");
        return 0;
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            NonZeroHaveSameIndi=false;
            for(int Sp=0;Sp<SparseM.arrayPtr[i+1]-SparseM.arrayPtr[i];Sp++)
            {
                if (SparseM.arrayIndi[SparseM.arrayPtr[i]+Sp]==j)
                {
                    NonZeroHaveSameIndi= true;
                    norm += pow(A[i][j]-SparseM.arrayValue[SparseM.arrayPtr[i]+Sp],2);
                    break;
                }
            }
            if (!NonZeroHaveSameIndi)
                norm += pow(A[i][j],2);
        }
    }
    return norm;
}
void Trans2FullMatrix(ComprassTypeMatrix Input,double OutPut[5][5])   //transform from Compress row form into Full Matrix
{
    int RowPtr;
    int ColPtr=0;
    int RowPrinted;
    int ValueIndi=0;
    for(int row=0;row<5;row++)
    {
        RowPrinted=0;
        RowPtr=Input.arrayPtr[row+1];
        for (int col=0;col<5;col++)
        {
            if (col==Input.arrayIndi[ColPtr])
            {
                if (Input.arrayPtr[row+1]-Input.arrayPtr[row] > RowPrinted )
                {
                    OutPut[row][col]=(double)Input.arrayValue[ValueIndi];
                    ValueIndi++;
                    ColPtr ++;
                    RowPrinted ++;
                 }
                else
                {
                    OutPut[row][col]=0.0;
                }
            }
            else
            {
                OutPut[row][col]=0.0;
            }
        }
    }
}

void DisplayFullMatrix(double A[5][5])
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("  %.1lf  ",A[i][j]);
        }
        printf("\n");
    }
}

bool testmatrixD(ComprassTypeMatrix Input, double A[5][5])
{
    struct ComprassTypeMatrix DD;
    double dis[5][5];
    DD=CreateDMatrix(Input);
    printf("Diagonal matrix:\n");
    DisplaySparseMatrix(DD);
    Trans2FullMatrix(DD,dis);
    DisplayFullMatrix(dis);
    if (SecondNorm(DD,A)==0)
        return true;
    else
        return false;
}

bool testmatrixLU(ComprassTypeMatrix Input, double A[5][5])
{
    struct ComprassTypeMatrix LU;
    double dis[5][5];
    LU=CreateLUMatrix(Input);
    printf("L+U matrix:\n");
    DisplaySparseMatrix(LU);
    Trans2FullMatrix(LU,dis);
    DisplayFullMatrix(dis);
    if (SecondNorm(LU,A)==0)
        return true;
    else
        return false;
}

bool testrowPermute(ComprassTypeMatrix Input, double A[5][5])
{
    double dis[5][5];
    vector<double> b(5);
    PermuteSparse(Input,b,1,3);
    DisplaySparseMatrix(Input);
    Trans2FullMatrix(Input,dis);
    DisplayFullMatrix(dis);
    if (SecondNorm(Input,A)==0)
        return true;
    else
        return false;
}

bool testcolPermute(ComprassTypeMatrix Input, double A[5][5])
{
    double dis[5][5];
    vector<double> b(5);
    PermuteColomn(Input,b,1,3);
    DisplaySparseMatrix(Input);
    Trans2FullMatrix(Input,dis);
    DisplayFullMatrix(dis);
    if (SecondNorm(Input,A)==0)
        return true;
    else
        return false;
}

bool testDiagonalMaximize(ComprassTypeMatrix Input,double A[5][5])
{
    vector<double> Xcomp(5);
    vector<double> b(5);
    double dis[5][5];
    for(int i=0;i<5;i++)
    {
        Xcomp[i]=i+1;
        i==0?b[i]=1:b[i]=0;
    }
    Trans2FullMatrix(Input,dis);
    DisplayFullMatrix(dis);
    DiagonalMaximize(Input,Xcomp,b);
    printf("result:\n");
    Trans2FullMatrix(Input,dis);
    DisplayFullMatrix(dis);
    printf("corresponding Xcomp:\n");
    DisplayVector(Xcomp);
    printf("corresponding b:    \n");
    DisplayVector(b);
    if (SecondNorm(Input,A)==0)
        return true;
    else
        return false;
}

void test1()
{
    struct ComprassTypeMatrix TestData;
    for (int i=0;i<12;i++)
    {
        TestData.arrayValue[i]=(double)(i+1);
    }
    for(int i=0;i<9;i++)
        pass[i]=false;
    double A[5][5];

    TestData.arrayIndi[0]=0;
    TestData.arrayIndi[1]=1;
    TestData.arrayIndi[2]=4;
    TestData.arrayIndi[3]=0;
    TestData.arrayIndi[4]=1;
    TestData.arrayIndi[5]=2;
    TestData.arrayIndi[6]=1;
    TestData.arrayIndi[7]=2;
    TestData.arrayIndi[8]=4;
    TestData.arrayIndi[9]=3;
    TestData.arrayIndi[10]=0;
    TestData.arrayIndi[11]=4;
    TestData.arrayPtr[0]=0;
    TestData.arrayPtr[1]=3;
    TestData.arrayPtr[2]=6;
    TestData.arrayPtr[3]=9;
    TestData.arrayPtr[4]=10;
    TestData.arrayPtr[5]=12;

    vector<double> X(5);
    vector<double> b(5);
    for(int i=0;i<5;i++)
    {
        X[i]=i+1;
        b[i]=5-i;
    }
    /*TestData in both sparse and full matrix form*/
    printf("\n");
    Trans2FullMatrix(TestData,A);
    DisplayFullMatrix(A);
    if (SecondNorm(TestData,A)==0)
        pass[0]=true;

    /*test Diagonal matrix transformation*/
    double sample1[5][5]={1,0,0,0,0,0,5,0,0,0,0,0,8,0,0,0,0,0,10,0,0,0,0,0,12};
    pass[1]=testmatrixD(TestData,sample1);

    /*test L+U matrix transformation*/
    double sample2[5][5]={0,2,0,0,3,4,0,6,0,0,0,7,0,0,9,0,0,0,0,0,11,0,0,0,0};
    pass[2]=testmatrixLU(TestData,sample2);

    /*test product Ax correctness*/
    printf("product test:\n");
    pass[3]=testproduct(TestData,A,X,b);
    printf("\n");
    DisplayVector(b);

    /*test row permute*/
    printf("row permute test:\n");
    double sample3[5][5]={0,7,8,0,9,4,5,6,0,0,1,2,0,0,3,0,0,0,10,0,11,0,0,0,12};
    pass[4]=testrowPermute(TestData,sample3);

    /*test col permute*/
    printf("col permute test:\n");
    double sample4[5][5]={0,2,1,0,3,6,5,4,0,0,8,7,0,0,9,0,0,0,10,0,0,0,11,0,12};
    pass[5]=testcolPermute(TestData,sample4);

    /*test diagonal maximization*/
    printf("maximize diagonal test:\n");
    double sample5[5][5]={12,0,0,0,11,0,10,0,0,0,9,0,8,7,0,0,0,6,5,4,3,0,0,2,1};
    pass[6]=testDiagonalMaximize(TestData,sample5);

    string  test[9]={" sparse transformation"," Diagonal check       "," L+U check            "," product test         "," row permute test     "," col permute test     "," MaximizeDiagonal test"};

    for(int i=0;i<7;i++)
        cout << "test" << i+1 << test[i] <<(pass[i]?":    pass": ":    failed")<<endl;
}


void test2()
{
    struct ComprassTypeMatrix WholeTest;
    WholeTest.arrayValue[0]=1;
    WholeTest.arrayValue[1]=2;
    WholeTest.arrayValue[2]=0.1;
    WholeTest.arrayValue[3]=0.1;
    WholeTest.arrayValue[4]=5;

    WholeTest.arrayPtr[0]=0;
    WholeTest.arrayPtr[1]=1;
    WholeTest.arrayPtr[2]=3;
    WholeTest.arrayPtr[3]=5;
    WholeTest.arrayIndi[0]=0;
    WholeTest.arrayIndi[1]=1;
    WholeTest.arrayIndi[2]=2;
    WholeTest.arrayIndi[3]=0;
    WholeTest.arrayIndi[4]=2;
    WholeTest.NonZeroNumber=5;
    WholeTest.Rank=3;
    vector<double> b(3);
    vector<double> Xcomp(3);
    vector<double> X(3);
    vector<double> Xresult(3);
    b[0]=3;
    b[1]=-3.9;
    b[2]=5.3;
    Xcomp[0]=1;
    Xcomp[1]=2;
    Xcomp[2]=3;
    double dis[3][3];
    double eps;

    /*diagonal maximization*/
    DiagonalMaximize(WholeTest,Xcomp,b);

    /*generate D and L+U*/
    struct ComprassTypeMatrix DD;
    struct ComprassTypeMatrix LU;
    DD=CreateDMatrix(WholeTest);
    LU=CreateLUMatrix(WholeTest);
    DD.Rank=WholeTest.Rank;
    LU.Rank=WholeTest.Rank;

    /*get D inv*/
    InverseSparseDiagonal(DD);

    for(int i=0;i<51;i++)
    {
        X= Addition(Product(DD,Product(LU,X)),Product(DD,b));
        eps=abs(VecNorm(Addition(Neg(b),Product(WholeTest,X)))/VecNorm(b));
        printf("epsilon=%lf at %d step\n",eps,i);
    }

    for(int i=0;i<Xresult.size();i++)
    {
        Xresult[Xcomp[i]-1]=X[i];
    }
    DisplayVector(X);
    DisplayVector(Xcomp);
    DisplayVector(Xresult);
}
