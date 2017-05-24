/** Matrix Operator
 *
 * Chen Yu
 * 5/23/2017
 * Input: matrix A, vector X or vector b
 * Output: corresponding vector b or vector X satisfying Ax=b
 *
 */

 #include <vector>
 #include <stdlib.h>

 using namespace std;
#ifndef MATRIXOPERATE_H
#define MATRIXOPERATE_H


/** define a new struct type to store compress matrix
 *
 *  Includes array value, array pointer and array of indices
 *
 */

struct CompressTypeMatrix                                           // Compress matrix consists of vector of value, ptr, and indices
{
    vector<double> arrayValue;
    vector<int> arrayIndi;
    vector<int> arrayPtr;
    int NonZeroNumber=0;
    int Rank=0;
    int rowSize=0;
    int colSize=0;
};

/* add more points into an existed sparse matrix*/
int AddElementIntoSparseM(CompressTypeMatrix &Input, int a, int B, double C, int pointer, int &rowpointer);

/** Parent class for matrix operator
 *
 * There are some function shared by both compress matrix and full matrix, for example some special vector operator and matrix display
 * Subclasses are compress matrix operator and full matrix operator
 * Many small pieces of function has it own test cases.
 */
class MatrixOperate
{
    public:
        MatrixOperate();
        virtual ~MatrixOperate();
        /* operation in vector */
        vector<double> Neg(vector<double> Input);
        void testNeg();                                                                 // inverse test with addition: a+-a=0, so is the test pass, it shows both Neg and Addition are correctly implemented

        double VecNorm(vector<double> Input);
        void testVecNorm();

        vector<int> Convert2Int(vector<double> Input);
        int Zeroes(vector<double> &X);

        vector<double> Addition(vector<double> X1, vector<double> X2);
        void testAddition();

        bool VEq(vector<double> A, vector<double>  B);

        /*switch*/
        template<class T>
        void SwitchTwoNumber(T &A, T &B)    // switch two value
        {
            int media;
            media=A;                                            // c=A
            A=B;                                                   // A=B
            B=media;                                            // B =c
        }

        /* display stuff */
        void DisplayVector(vector<double> Input);
        void DisplaySparseMatrix(CompressTypeMatrix SparseM);
        void DisplayFullMatrix(vector< vector<double> A);

        vector< vector<double> > Trans2FullMatrix(CompressTypeMatrix Input)   //transform from Compress row form into Full Matrix

    protected:
        bool IsSparseMatrix;
    private:
};


/** Subclass for sparse matrix operator
 *
 * There are some function special for sparse matrix operator
 * Key function is to solve the matrix problem Ax=b by given A,b or get product result by given A,x
 * The matrix solver is design to use Jacobi Iterative solver
 *
 */
class SparseMatrixOperate: public MatrixOperate
{
    public:
        SparseMatrixOperate(CompressTypeMatrix MatrixA, vector<double> X, vector<double> b);
        virtual ~SparseMatrixOperate();
        CompressTypeMatrix CreateDMatrix(CompressTypeMatrix Input);
        CompressTypeMatrix CreateLUMatrix(CompressTypeMatrix Input);
        void PermuteRow(CompressTypeMatrix &Input, vector<double> &b, int RowIndex1, int RowIndex2);
        void PermuteColumn(CompressTypeMatrix &Input, vector<double> &X, int ColIndex1, int ColIndex2);
        void DiagonalMaximize(CompressTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b);

        vector<double> JacobiSolve();
        vector<double> Product(CompressTypeMatrix Input, vector<double> X);
    protected:
        CompressTypeMatrix CreateDMatrix();
        CompressTypeMatrix CreateLUMatrix();
    private:
        CompressTypeMatrix A;
        CompressTypeMatrix D;
        CompressTypeMatrix LU;
        void InverseSparseDiagonal(CompressTypeMatrix &Input);
        vector<double> x;
        vector<double> b;
};

/** Subclass for full matrix operator
 *
 * There are some function special for full matrix operator
 * Key function is to solve the matrix problem Ax=b by given A,b or get product result by given A,x
 * The matrix solver is design to test compress matrix correctness
 *
 */

 class FullMatrixOperate: public MatrixOperate
{
    public:
        FullMatrixOperate(vector< vector<double> >A, vector<double> X, vector<double> b);
        virtual ~FullMatrixOperate();
        void PermuteRow(vector< vector<double> > &Input, vector<double> &b, int RowIndex1, int RowIndex2);
        void PermuteColumn(vector< vector<double> > &Input, vector<double> &X, int ColIndex1, int ColIndex2);

        vector<double> JacobiSolve();
        vector<double> Product(CompressTypeMatrix Input, vector<double> X);
    protected:
        CompressTypeMatrix CreateDMatrix();
        CompressTypeMatrix CreateLUMatrix();
    private:
        vector< vector<double> > A;
        vector< vector<double> > D;
        vector< vector<double> > LU;
        void InverseSparseDiagonal(CompressTypeMatrix &Input);
        vector<double> x;
        vector<double> b;
        void DiagonalMaximize(CompressTypeMatrix &Input,vector<double> &Xcomp,vector<double> &b);
};
#endif // MATRIXOPERATE_H
