/**  Test module
 *
 * Test for Matrix operators
 * some accessory functional level test
 * Chen Yu
 * May.23/2017
 */


#include <vector>
#ifndef TEST_H
#define TEST_H
#define TestCaseSize 3

using namespace std;

class Test
{
    public:
        Test();
        virtual ~Test();
        bool VEq( vector<double> A, vector<double> B);
        bool AverageCheck(vector<double> a, double Abar);
    protected:
        void AverageFixedTest();
        void AverageRandTest();
    private:
};

class MatrixTest: public Test
{
    public:
        MatrixTest();
        virtual ~MatrixTest();
        void RunTest();
    protected:

    private:
        vector<bool> FixedValueTest();
        bool RandomValueTest();
        vector< vector<double> > A;
        vector<double>                  X;
};
#endif // TEST_H
