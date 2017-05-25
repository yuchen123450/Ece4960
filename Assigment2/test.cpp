#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include "test.h"
#include "MatrixOperate.h"

using namespace std;

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

void runModularTest()   // modular test try to run all test embedded in existed matrix operate class, those tests generally test for each small function
{
    printf("Modular Test starts:\n");
    MatrixOperate ModuleTest;
    ModuleTest.testAddition();
    ModuleTest.testNeg();
    ModuleTest.testSecondNormandTran2FullMatrix();
    ModuleTest.testVecNorm();
}
/** Parallel computing to check correctness
 *
 * set a matrix given in class
 * compute that 5x5 matrix in both sparse and full matrix
 * \return pass or failed
 *
 */

MainFunctionalTest::MainFunctionalTest()
{
    printf("MainFunctionalTest(Parallel computing test) starts:\n");

    /* build a TestData*/
    CompressTypeMatrix TestData;
    vector<double> a(12,0);
    vector<int> b(12,0);
    vector<int> c(6,0);
    TestData.arrayIndi = b;
    TestData.arrayValue = a;
    TestData.arrayPtr = c;
    TestData.Rank = 5;
    TestData.NonZeroNumber = 12;

    /* given TestData corresponding value */
    for (int i=0;i<12;i++)                                   // give 12 array value
    {
        TestData.arrayValue[i]=(double)(i+1);
    }

    TestData.arrayIndi[0]=0;                              // give 12 array indices
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
    TestData.arrayPtr[0]=0;                               // give 5 array pointer
    TestData.arrayPtr[1]=3;
    TestData.arrayPtr[2]=6;
    TestData.arrayPtr[3]=9;
    TestData.arrayPtr[4]=10;
    TestData.arrayPtr[5]=12;

    /* save local private data */
    TestCompressData = TestData;
    MatrixOperate Ma;
    TestFullData          = Ma.Trans2FullMatrix(TestData);
    printf("display original Full matrix and Sparse matrix:\n");
    Ma.DisplaySparseMatrix(TestData);                                       // display sparse matrix
    Ma.DisplayFullMatrix(TestFullData);                                      // display full matrix
}

MainFunctionalTest::~MainFunctionalTest()
{
    //dtor
}

void MainFunctionalTest::runTest()
{
    vector<double> Xtest(5);                                                      // initialize a vector Xtest
    vector<double> btest(5);                                                       // initialize a vector btest
    SparseMatrixOperate SMO(TestCompressData,Xtest,btest);
    FullMatrixOperate FMO(TestFullData,Xtest,btest);

    /* product test */
    if (SMO.VEq(  SMO.Product(TestCompressData,Xtest) , FMO.Product(TestFullData,Xtest)   ) )                                  // product vector from FMO =? SMO
        printf("Product fixed value test:                                       pass\n");
    else
        printf("Product fixed value test:                                       failed\n");

    /* D matrix generation test*/
    if (SMO.SecondNorm(  SMO.CreateDMatrix(TestCompressData) , FMO.CreateDMatrix(TestFullData)   ) ==0 )             // second norm of D matrix generated from FMO and SMO =?0
        printf("Matrix D generation fixed value test:                           pass\n");
    else
        printf("Matrix D generation fixed value test:                           failed\n");

    /* LU matrix generation test*/
    if (SMO.SecondNorm(  SMO.CreateLUMatrix(TestCompressData) , FMO.CreateLUMatrix(TestFullData)   ) ==0 )        // second norm of LU matrix generated from FMO and SMO =?0
        printf("Matrix LU generation fixed value test:                          pass\n");
    else
        printf("Matrix LU generation fixed value test:                          failed\n");

    CompressTypeMatrix Ex1;                                                                                                                                         // build another compress matrix as experiment because in permute function, original memory will be covered
    vector< vector<double> >    Ex2;                                                                                                                             // build another full matrix as experiment
    Ex1 = TestCompressData;
    Ex2 = TestFullData;

    /* RowPermute test*/
    SMO.PermuteRow(Ex1,btest,1,3);                                                                                                                              // Do row permutation in each system
    FMO.PermuteRow(Ex2,btest,1,3);
    if (SMO.SecondNorm( Ex1 , Ex2 ) == 0 )                                                                                                                   // second norm of Ex1,Ex2(permutation result from sparse and full matrix system) =?0
        printf("RowPermute test fixed value test:                               pass\n");
    else
        printf("RowPermute test fixed value test:                              failed\n");

    /* Column Permute test*/
    SMO.PermuteColumn(Ex1,btest,1,3);                                                                                                                         // Do column permutation in each system
    FMO.PermuteColumn(Ex2,btest,1,3);
    if (SMO.SecondNorm( Ex1 , Ex2 ) == 0 )                                                                                                                   // second norm of Ex1,Ex2(permutation result from sparse and full matrix system) =?0
        printf("Column Permute test fixed value test:                           pass\n");
    else
        printf("Column Permute test fixed value test:                          failed\n");

    /* Diagonal Maximization test*/
    SMO.DiagonalMaximize(Ex1,Xtest,btest);                                                                                                                         // Do column permutation in each system
    FMO.DiagonalMaximize(Ex2,Xtest,btest);
    if (SMO.SecondNorm( Ex1 , Ex2 ) == 0 )                                                                                                                   // second norm of Ex1,Ex2(permutation result from sparse and full matrix system) =?0
        printf("Diagonal Maximization test fixed value test:                    pass\n");
    else
        printf("Diagonal Maximization test fixed value test:                   failed\n");
}
//
//
//void test2()
//{
//    struct CompressTypeMatrix WholeTest;
//    WholeTest.arrayValue[0]=1;
//    WholeTest.arrayValue[1]=2;
//    WholeTest.arrayValue[2]=0.1;
//    WholeTest.arrayValue[3]=0.1;
//    WholeTest.arrayValue[4]=5;
//
//    WholeTest.arrayPtr[0]=0;
//    WholeTest.arrayPtr[1]=1;
//    WholeTest.arrayPtr[2]=3;
//    WholeTest.arrayPtr[3]=5;
//    WholeTest.arrayIndi[0]=0;
//    WholeTest.arrayIndi[1]=1;
//    WholeTest.arrayIndi[2]=2;
//    WholeTest.arrayIndi[3]=0;
//    WholeTest.arrayIndi[4]=2;
//    WholeTest.NonZeroNumber=5;
//    WholeTest.Rank=3;
//    vector<double> b(3);
//    vector<double> Xcomp(3);
//    vector<double> X(3);
//    vector<double> Xresult(3);
//    b[0]=3;
//    b[1]=-3.9;
//    b[2]=5.3;
//    Xcomp[0]=1;
//    Xcomp[1]=2;
//    Xcomp[2]=3;
//    double dis[3][3];
//    double eps;
//
//    /*diagonal maximization*/
//    DiagonalMaximize(WholeTest,Xcomp,b);
//
//    /*generate D and L+U*/
//    struct CompressTypeMatrix DD;
//    struct CompressTypeMatrix LU;
//    DD=CreateDMatrix(WholeTest);
//    LU=CreateLUMatrix(WholeTest);
//    DD.Rank=WholeTest.Rank;
//    LU.Rank=WholeTest.Rank;
//
//    /*get D inv*/
//    InverseSparseDiagonal(DD);
//
//    for(int i=0;i<51;i++)
//    {
//        X= Addition(Product(DD,Product(LU,X)),Product(DD,b));
//        eps=abs(VecNorm(Addition(Neg(b),Product(WholeTest,X)))/VecNorm(b));
//        printf("epsilon=%lf at %d step\n",eps,i);
//    }
//
//    for(int i=0;i<Xresult.size();i++)
//    {
//        Xresult[Xcomp[i]-1]=X[i];
//    }
//    DisplayVector(X);
//    DisplayVector(Xcomp);
//    DisplayVector(Xresult);
//}
