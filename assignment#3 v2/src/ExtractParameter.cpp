#include <vector>
#include <stdlib.h>
#include "ExtractParameter.h"
#include "../MatrixSolver.h"
using namespace std;
/** Parent class
 *  Do extract parameter
 * \return
 *
 */

ExtractParameter::ExtractParameter()
{
    vector<double> arb(MaxtrixSolverSize);
    G=arb;                                                                                          // initialize a size to G
    /* Initialize the Gradient and Jacobi matrix to be all 0 */
    for(int i=0;i<MaxtrixSolverSize;i++)
    {
        G[i]=0;                                                                                     // G all 0
        for(int j=0;j<MaxtrixSolverSize;j++)
        {
            J[i][j]=0;                                                                              // J all 0
        }
    }
}

ExtractParameter::~ExtractParameter()
{

}

vector<double> ExtractParameter::OneIteratioinUpdate()     // parameter alpha Update each iteration
{
    vector<double> Medium;
    DirectFullMatrixSolver Solve(J,G);
    Medium = Solve.DirectSolve(J,G);                                     // Medium result the result from solving Jacobi and gradient
    double d=0;
    for(int i=0; i<ProblemSize;i++)
    {
        TempParam[i] -= Medium[i];                                          // only pick Problem size of value in return value from matrix solver
        d += pow(Medium[i]/TempParam[i],2);                         // sum of d(alpha)/alpha ^2
    }
    alpha.push_back(TempParam);                                          // push back New temporary parameter to historical alpha
    Delta.push_back(d);
    return TempParam;
}

/** subclass
 *
 * Quasi-Newton Method
 *
 */



/** subclass
 *
 * Secant method
 *
 */

