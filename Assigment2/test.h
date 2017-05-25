/** test
 * some test cases with multiple test strategies
 * Chen Yu
 * 5/24/2017
 *
 */
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stdio.h>

#include "MatrixOperate.h"

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

using namespace std;

vector<double> createb1(int num,int VecSize);


/**
 * Modular test try to run all test embedded in existed matrix operate class, those tests generally test for each small function
 * Generally these tests are only included in parent class
 * Random some groups of input value and tests these output
 */
void runModularTest();   //

/** mainly check functions in subclass works as expected
 * Parallel computing the same problem with 2 subclass systems
 * Check the result between two system: compress matrix operator and full matrix operator
 *
 */
class MainFunctionalTest
{
public:
    /* constructor and destructor */
    MainFunctionalTest();
    virtual ~MainFunctionalTest();
    void runTest();
private:
    CompressTypeMatrix TestCompressData;
    vector< vector<double> >  TestFullData;
};

#endif // TEST_H_INCLUDED
