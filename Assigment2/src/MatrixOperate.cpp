/** Matrix Operator
 *
 * Chen Yu
 * 5/23/2017
 * Input: matrix A, vector X or vector b
 * Output: corresponding vector b or vector X satisfying Ax=b
 */
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "MatrixOperate.h"

using namespace std;

 int AddElementIntoSparseM(CompressTypeMatrix &Input, int A, int B, double C, int pointer,int &rowpointer)     // add one more element into SparseMatrix
{
        Input.arrayIndi.push_back(A-1);                                 // add a indices to arryindi: normal expression col is A, but store in c++, the array col indice should be A-1
        Input.arrayValue.push_back(C);                                  // add a value
        Input.NonZeroNumber++;                                            // more nonzero number
        if (B == rowpointer)                                                    // still on the same row as previous added element
            Input.arrayPtr[B]++;                                                // increment arrayptr number on such row
        else if (B>rowpointer)                                                // when input point is on another row
        {
            for(int j=rowpointer+1;j<=B;j++)                          // from the previous row to the input point row, all rows' ptr should be the same as previous row ptr number
            {
                Input.arrayPtr.push_back(Input.arrayPtr[rowpointer]);
                Input.Rank++;                                                      // increase the rank till input row B
            }
            Input.arrayPtr[B]++;                                                // row B contains one more point than previous rows
        }
        rowpointer=B;
        return 1;
}



/**
 * Matrix Operate
 * parent class
 *
 */

MatrixOperate::MatrixOperate()
{
    //ctor
}

MatrixOperate::~MatrixOperate()
{
    //dtor
}

vector<double> MatrixOperate::Neg(vector<double> Input)                 // turn all elements in vector to negative value
{
    vector<double> result(Input.size());
    for(int i=0;i<Input.size();i++)                                                              // row increasing
        result[i]=-Input[i];                                                                             // every element change to its negative value
    return result;
}

void MatrixOperate::testNeg()                                                                  // inverse test with addition: a+-a=0
{
    /* do a random test */
    int r=rand() % 100;                                                                               //  vector scale is random, upper limit is 100
    vector<double>  a(r);
    vector<double>  Sresult(r,0);                                                               // sample solution should be all in 0
    /* initialize a values */
    for(int i=0;i<r;i++)
    {
        a[i] = (double)(rand() % 100);                                                          // all values in vector should also be random
    }                                                                                                             // a is a very random vector

    if (VEq( Addition(a,Neg(a)), Sresult ) )
        printf("Neg random value test:                      pass\n");
    else
        printf("Neg random value test:                      failed\n");
}

vector<int> MatrixOperate::Convert2Int(vector<double> Input)             // convert double vector into integers
{
    vector<int> Output(Input.size());
    for(int i=0;i<Input.size();i++)
    {
        Output[i]=(int)Input[i];                                                                       // convert every int element into double
    }
    return Output;
}

double MatrixOperate::VecNorm(vector<double> Input)// calculate vector's second norm
{
    double result=0;
    for(int i=0;i<Input.size();i++)
        result += pow(Input[i],2);                                                                   //   result store sum of square of each term in vector
    return sqrt(result);                                                                                 // return square root of that sum
}

void MatrixOperate::testVecNorm()                                                          // test whether VecNorm operated correctly
{
    int r=rand() % 20;                                                                                  // set random number less than 20
    double Sresult = pow((double)r,2.0);                                                    // set sample result = r^2
    vector<double> a(r);
    for(int i=0;i<r;i++)
    {
        a[i]=2*i-1;                                                                                         // set vector = 1,3,5,7.....2i-1
    }
    if (Sresult == VecNorm(a))
        printf("VecNorm random value test:                      pass\n");
    else
        printf("VecNorm random value test:                      failed\n");
}

int MatrixOperate::Zeroes(vector<double> &X)                                     //make vector all zero
{
    for(int i=0;i<X.size();i++)
    {
        X[i]=0;                                                                                              // clear all terms in vector
    }
    return 1;
}

vector<double> MatrixOperate::Addition(vector<double> X1, vector<double> X2)        // create vector equals to the sum of 2 vectors
{
    vector<double> b(X1.size());
    if (X1.size()!=X2.size())                                                                       // whether X1 has the same size of X2
    {
        printf("error: addition between different size vectors\n");
    }
    else
    {
        for(int i=0;i<X1.size();i++)                                                              // row increasing
            b[i]=X1[i]+X2[i];                                                                          // add them together
        return b;
    }
}

void MatrixOperate::testAddition()
{
    vector<double> X1(5);                                                                         // initialize X1,X2
    vector<double> X2(5);
    vector<double> result;
    vector<double> Sresult(5,5);                                                                // sample correct result should be 5,5,5,5,5
    for(int i=0;i<5;i++)
    {
        X1[i]=i;                                                                                              // X1 = 0,1,2,3,4
        X2[i]=5-i;                                                                                          // X2 = 5,4,3,2,1
    }
    result=Addition(X1,X2);
    if (VEq(result,Sresult))                                                                           // if X1 + X2 = 5,5,5,5,5 then pass
        printf("addition fiexed value test:                      pass\n");
    else
        printf("addition fiexed value test:                      failed\n");
}

bool MatrixOperate::VEq(vector<double> A, vector<double>  B)
{
    try
    {
        bool Eq=true;
        if(A.size()!=B.size())                                                                          //except when a vector size different from b vector size
            throw "two array have different size";
        for(int i=0;i<A.size();i++)
        {
            if ((abs(A[i])-abs(B[i]))/(abs(A[i]+abs(B[i]))) > pow(10,-14))    // any element in vector are different means vectors are different,
            {
                Eq = false;
                break;
            }
        }
        return Eq;
    }
    catch(const char* msg)                                                                           // exception handling
    {
        cerr << msg << endl;
    }
}

void MatrixOperate::DisplayVector(vector<double> Input)                      // display vector
{
    for(int i=0;i<Input.size();i++)                                                                 // row increasing
    {
        printf("%lf; ",Input[i]);                                                                        // print each term value
    }
    printf("\n");
}

void MatrixOperate::DisplaySparseMatrix(CompressTypeMatrix SparseM) // display sparse matrix
{
    /* display sparse matrix value vector */
    printf("sparse matrix value is:   ");
    for(int i=0;i<SparseM.NonZeroNumber;i++)
    {
        printf("%.2lf;  ",SparseM.arrayValue[i]);
    }
    printf("\n");

    /* display sparse matrix ptr vector */
    printf("sparse matrix row pointer is:   ");
    for(int i=0;i<6;i++)
    {
        printf("%d;  ",SparseM.arrayPtr[i]);
    }
    printf("\n");

    /* display sparse matrix indices vector */
    printf("sparse matrix indices is:   ");
    for(int i=0;i<SparseM.NonZeroNumber;i++)
    {
        printf("%d;  ",SparseM.arrayIndi[i]);
    }
    printf("\n");
}

void MatrixOperate::DisplayFullMatrix(vector< vector<double> > A)
{
    for(int i=0;i<A.size();i++)
    {
        for(int j=0;j<A[0].size(); j++)
        {
            printf("  %.1lf  ",A[i][j]);
        }
        printf("\n");
    }
}

vector< vector<double> > MatrixOperate::Trans2FullMatrix(CompressTypeMatrix Input)   //transform from Compress row form into Full Matrix
{
    int Size=Input.Rank;
    vector< vector<double> > OutPut(Size, vector<double>(Size));                                        // initialize the output as the rank or compress matrix
    int RowPtr;
    int ColPtr=0;                                                                                                                          // initialize the column pointer to be 0
    int RowPrinted;
    int ValueIndi=0;                                                                                                                     // initialize the value indice 0
    for(int row=0;row<Size;row++)                                                                                           // row increasing
    {
        RowPrinted=0;                                                                                                                   // for each row, at the beginning has printed no point
        RowPtr=Input.arrayPtr[row+1];                                                                                         // the first nonzero value has indices here
        for (int col=0;col<Size;col++)                                                                                          // row increasing
        {
            if (col==Input.arrayIndi[ColPtr])                                                                                   // when the column indice in compress matrix is nonzero
            {
                if (Input.arrayPtr[row+1]-Input.arrayPtr[row] > RowPrinted )                                 // check in the compress matrix, whether this row has already printed out all nonzero value
                {
                    OutPut[row][col]=(double)Input.arrayValue[ValueIndi];                                     //  full matrix receive the nonzero in compress matrix
                    ValueIndi++;                                                                                                         // find next column pointer of nonzero in compress matrix
                    ColPtr ++;                                                                                                             // column pointer increment
                    RowPrinted ++;                                                                                                    // in the row, printed points increment
                 }
                else                                                                                                                            // all other condition full matrix should still store 0
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
    return OutPut;
}
/**
 * SparseMatrix Operate
 * subclass
 *
 */

SparseMatrixOperate::SparseMatrixOperate(CompressTypeMatrix MatrixA, vector<double> X, vector<double> B)
{
    /* default set Operate class */
    A=MatrixA;
    x=X;
    b=B;
    IsSparseMatrix = true;
    D = CreateDMatrix();                // compute Diagonal Matrix from A
    LU = CreateLUMatrix();            // compute Lower and Upper Matrix from A
}

SparseMatrixOperate::~SparseMatrixOperate()
{
    //dtor
}

vector<double> SparseMatrixOperate::Product(CompressTypeMatrix Input, vector<double> X)                // do product Ax
{
    vector<double> b(X.size());
    int cont;
    cont=Zeroes(b);                                                                 // initialize output with all zeroes
    if(X.size()!=Input.Rank)
    {
        printf("vector size is different from that matrix rank\n");
        printf("vector size: %d,   matrix size: %d \n", X.size(),Input.Rank);
        return b;
    }
    for(int i=0;i<Input.Rank;i++)                                                                                                   // row increasing
    {
        for(int j=0;j<Input.arrayPtr[i+1]-Input.arrayPtr[i];j++)                                                       // search out each row nonzero number
        {
            b[i]+=Input.arrayValue[Input.arrayPtr[i]+j]*X[Input.arrayIndi[Input.arrayPtr[i]+j]];      // sum of each row nonzero number * vector term with the same column indices
        }
    }
    return b;
}



CompressTypeMatrix SparseMatrixOperate::CreateDMatrix(CompressTypeMatrix Input)                                                                 // get a Diagonal Matrix from Input Matrix
{
    struct CompressTypeMatrix MatrixD;
    MatrixD.arrayPtr.push_back(0);                                                  // initialize default zero for compress output's ptr vector
    int Dptrpointer=0,Dpointer=0;                                                     // build compress matrix from 0,0
    int feedback;
    for(int i=0;i<Input.Rank;i++)                                                       // row increasing
    {
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)              // search start from next row first nonzero column
        {
            if (Input.arrayIndi[j]==i)                                                      // if Aij is nonzero: i=j, then add an element to D matrix
            {
                feedback = AddElementIntoSparseM(MatrixD,Input.arrayIndi[j]+1,i+1,Input.arrayValue[j],Dpointer,Dptrpointer);            //add an element to D matrix
                Dpointer++;                                             // increase D pointer
                break;                                                      // stop the search in the row
            }
        }
    }
    return MatrixD;
}

CompressTypeMatrix SparseMatrixOperate::CreateLUMatrix(CompressTypeMatrix Input)                                                             // get a LU Matrix from Input Matrix
{
    struct CompressTypeMatrix matrixLU;
    matrixLU.arrayPtr.push_back(0);                             // initialize default zero for compress output's ptr vector
    int LUptrpointer=0,LUpointer=0;                              // build compress matrix from 0,0
    int feedback;
    for(int i=0;i<Input.Rank;i++)                                    // row increasing
    {
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)   // search start from next row first nonzero column
        {
            if (Input.arrayIndi[j]!=i )                                           // if Aij is nonzero: i!= j, then add an element to LU matrix, LU matrix is just exclude Diagonal
            {
                feedback=AddElementIntoSparseM(matrixLU,Input.arrayIndi[j]+1,i+1,Input.arrayValue[j],LUpointer,LUptrpointer);   //add an element to D matrix
                LUpointer++;                                                        // increase D pointer
            }
        }
    }
    return matrixLU;
}

CompressTypeMatrix SparseMatrixOperate::CreateDMatrix()                                                                 // without Input, we default output Diagonal matrix of matrix A
{
   return CreateDMatrix(A);
}

CompressTypeMatrix SparseMatrixOperate::CreateLUMatrix()                                                              // without Input, we default output Diagonal matrix of matrix LU
{
    return CreateLUMatrix(A);
}

void SparseMatrixOperate::InverseSparseDiagonal(CompressTypeMatrix &Input)
{
    for(int i=0;i<Input.Rank;i++)
    {
        Input.arrayValue[i]= 1/Input.arrayValue[i];
    }
}

vector<double> SparseMatrixOperate::JacobiSolve()
{
    double eps;
    InverseSparseDiagonal(D);
    vector<double> X(A.Rank,0);
    vector<double> Z(A.Rank,0);
    for(int i=0;i<30;i++)
    {
        X= Addition(Product(D,Product(LU,X)),Product(D,b));                                 // X(k+1) = invD*invLU*X(k)+invD*b
        eps=abs(VecNorm(Addition(Neg(b),Product(A,X)))/VecNorm(b));              // calculate epsilon
        printf("epsilon=%lf at %d step\n",eps,i);
    }
    if (eps>1)
    {
        return Z;
    }
    else
    {
        return X;
    }
}

/**
 *
 * Sparse matrix permutation
 * Sparse matrix row scaling
 *
 */

void SparseMatrixOperate::PermuteRow(CompressTypeMatrix &Input,vector<double> &b, int RowIndex1, int RowIndex2)
{
    SwitchTwoNumber(b[RowIndex1-1],b[RowIndex2-1])                                                          // switch 2 number in vector b

    /*get each row # of nonzero value first*/
    int EachRowContainsNonZero[Input.Rank];
    for(int i=0;i<Input.Rank;i++)
    {
        EachRowContainsNonZero[i]=Input.arrayPtr[i+1]-Input.arrayPtr[i];
    }

    /*define intermedia array*/
    double Row2Value[EachRowContainsNonZero[RowIndex2-1]];
    int Row2Indi[EachRowContainsNonZero[RowIndex2-1]];
    double IntermediaValue[Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1]];
    int IntermediaIndi[Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1]];

    /*save initial row2 all value and indices*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex2-1];i++)
    {
        Row2Value[i]=Input.arrayValue[Input.arrayPtr[RowIndex2-1]+i];
        Row2Indi[i]=Input.arrayIndi[Input.arrayPtr[RowIndex2-1]+i];
    }
    /*save initial items between row1 and row2 all value and indices*/
    for(int i=0;i<Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1];i++)
    {
        IntermediaValue[i]=Input.arrayValue[Input.arrayPtr[RowIndex1]+i];
        IntermediaIndi[i]=Input.arrayIndi[Input.arrayPtr[RowIndex1]+i];
    }

    /*move row1 to row2*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex1-1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex2]-1-i]=Input.arrayIndi[Input.arrayPtr[RowIndex1]-1-i];
        Input.arrayValue[Input.arrayPtr[RowIndex2]-1-i]=Input.arrayValue[Input.arrayPtr[RowIndex1]-1-i];
    }

    /*move items between row1 and row2*/
    for(int i=0;i<Input.arrayPtr[RowIndex2-1]-Input.arrayPtr[RowIndex1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex1-1]+EachRowContainsNonZero[RowIndex2-1]+i]=IntermediaIndi[i];
        Input.arrayValue[Input.arrayPtr[RowIndex1-1]+EachRowContainsNonZero[RowIndex2-1]+i]=IntermediaValue[i];
    }

    /*move row2 to row1*/
    for(int i=0;i<EachRowContainsNonZero[RowIndex2-1];i++)
    {
        Input.arrayIndi[Input.arrayPtr[RowIndex1-1]+i]=Row2Indi[i];
        Input.arrayValue[Input.arrayPtr[RowIndex1-1]+i]=Row2Value[i];
    }

    /**
     * all above just shift vector of Value and vector of indices
     * right now reorder the vector of the ptr by accumulating number of nonzero values in each row after shifting
     * each row after shifting will still have the same number of nonzero values, the only difference is row
     */

    /*change ptr*/
    Input.arrayPtr[0]=0;
    int accumu=0;
    for(int i=0;i<Input.Rank;i++)                                                                           // row increasing
    {
        if (i==RowIndex1-1)                                                                                      // new row1 should contains # of nonzero values of old row 2
            accumu +=EachRowContainsNonZero[RowIndex2-1];
        else if (i==RowIndex2-1)                                                                             // new row2 should contains # of nonzero values of old row 1
            accumu +=EachRowContainsNonZero[RowIndex1-1];
        else                                                                                                                  // all the else should contain the same nonzero values
            accumu +=EachRowContainsNonZero[i];
        if(i<Input.Rank)
            Input.arrayPtr[i+1]=accumu;                                                                     // the current row ptr array store accumulated number of nonzero values
    }
    printf("\n");
}

void SparseMatrixOperate::PermuteColumn(CompressTypeMatrix &Input,vector<double> &X, int ColIndex1, int ColIndex2)
{
    SwitchTwoNumber(X[ColIndex1-1],X[ColIndex2-1]);                                 // switch 2 number in X vector
    bool Col1NonZero;
    bool Col2Nonzero;
    for(int i=0;i<Input.Rank;i++)
    {
        Col1NonZero=false;
        Col2Nonzero=false;
        int ptr1,ptr2=0;
        for(int j=Input.arrayPtr[i];j<Input.arrayPtr[i+1];j++)
        {
            if (Input.arrayIndi[j]==ColIndex1-1)
            {
                Col1NonZero=true;
                ptr1=j;
            }
            if (Input.arrayIndi[j]==ColIndex2-1)
            {
                Col2Nonzero=true;
                ptr2=j;
            }
        }
        if ((Col1NonZero==true) && (Col2Nonzero==true))
        {
            SwitchTwoNumber(Input.arrayValue[ptr1],Input.arrayValue[ptr2]);                 // switch two double in sparse.value array
        }
        else if ((Col1NonZero==true) && (Col2Nonzero==false))
        {
            Input.arrayIndi[ptr1]=ColIndex2-1;
            for(int j=ptr1+1;j<Input.arrayPtr[i+1];j++)
            {
                if (Input.arrayIndi[j]<ColIndex2-1)
                {
                    SwitchTwoNumber(Input.arrayValue[j],Input.arrayValue[j-1]);                 // switch two double in sparse.value array
                    SwitchTwoNumber(Input.arrayIndi[j],Input.arrayIndi[j-1]);                       // switch two double in sparse.integer array
                }
            }
        }
        else if ((Col1NonZero==false) && (Col2Nonzero==true))
        {
            Input.arrayIndi[ptr2]=ColIndex1-1;
            for(int j=ptr2-1;j>=Input.arrayPtr[i];j--)
            {
                if (Input.arrayIndi[j]>ColIndex1-1)
                {
                    SwitchTwoNumber(Input.arrayValue[j],Input.arrayValue[j+1]);                 // switch two double in sparse.value array
                    SwitchTwoNumber(Input.arrayIndi[j],Input.arrayIndi[j+1]);                       // switch two double in sparse.integer array
                }
            }
        }
    }
}

void SparseMatrixOperate::DiagonalMaximize(CompressTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b)
{
    int ptr;
    double Max;
    int row,col;
    bool shift;
    for(int i=0;i<Input.Rank;i++)
    {
        shift=false;
        row=0;
        col=0;
        ptr=Input.arrayPtr[i];
        Max=Input.arrayValue[ptr];
        /*Find maximum and corresponding ptr*/
        for(int j=Input.arrayPtr[i];j<Input.NonZeroNumber;j++)
        {
            if ((Input.arrayValue[j]>Max) && (Input.arrayIndi[j]>=i))
            {
                Max=Input.arrayValue[j];
                ptr=j;
                shift=true;
            }
        }
        if (shift)
        {
        /*figure out corresponding row and col*/
            for(int j=0;j<=Input.Rank;j++)
                if (ptr<Input.arrayPtr[j])
                {
                    row=j;
                    break;
                }
            col=Input.arrayIndi[ptr]+1;
        /*Do permute*/
            if ((row==i+1) && (col!=i+1))
                PermuteColomn(Input,Xcomp,i,col-1);
            if ((row!=i+1) && (col==i+1))
                PermuteSparse(Input,b,i,row-1);
            if ((row!=i+1) && (col!=i+1))
            {
                PermuteSparse(Input,b,i+1,row);
                PermuteColomn(Input,Xcomp,i+1,col);
            }
        }
    }
}
