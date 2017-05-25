/** ExtractionParameter
 *
 *  Solve for the local minimum
 *  Include LOS test
 *  Input: Initial guess, objective function
 *  Output: local minimum parameter
 */


#include <vector>
#include <stdlib.h>
#include "../MatrixSolver.h"


#define MaxLoops 50
#ifndef EXTRACTPARAMETER_H
#define EXTRACTPARAMETER_H

/** Parent class contains function that renew the Temporary fit value based on given Jacobi and Gradient
 *
 * Given Gradient and Jacobi
 * Store current information
 * \return next iteration's Temporary parameter values
 *
 */

class ExtractParameter
{
    public:
        ExtractParameter();
        virtual ~ExtractParameter();
        vector<double> OneIteratioinUpdate();                                          // parameter alpha Update each iteration
    protected:
        vector< vector<double> > alpha;                                                   // historical extracted parameter result; last column of value should be the same as best parameter
        vector<double> TempParam;                                                          // temporary solved parameter result;
        vector<double> absDeviation;                                                        // historical iterative absolute deviation
        vector<double> Delta;                                                                    // historical iterative delta
        int ProblemSize;
        vector<double> G;                                                                          // Gradient
        double J[MaxtrixSolverSize][MaxtrixSolverSize];                         // Jacobi matrix
    private:

};


/** subclass Quasi-Newton
 *
 * Mainly used to get Jacobi and Gradient
 * only constructor, and a pointer point to specific objective function
 * \return: Jacobi and Gradient
 *
 */

template <class T>
class QuasiNewtonMethod: public ExtractParameter
{
    public:
        QuasiNewtonMethod(vector<double> InitialGuess);                     // quasi newton just need 1 initial guess and go along gradient descent
        virtual ~QuasiNewtonMethod();

        vector<double> runExtract(T *ptr);
        vector<double> CalculatedS(T *ptr);                                             // calculate dS
        vector< vector<double> > TwoIterationExtract(T *ptr);                                  // One iteration extract is needed for secant method, not every initial guess works for secant;

    protected:

        /* Jacobi and Gradient generation*/
        void CalJacobiGradient(T *ptr);                                                     // generate Jacobi and Gradient
        vector<double>  PartialDeriv(T *ptr,vector<double> param);
        void HMatrix(T *ptr);

    private:
};

/** subclass Secant method
 *
 * Mainly used to get Jacobi and Gradient
 * only constructor, and a pointer point to specific objective function
 * in constructor, at least 3 initial points are needed
 * \return: Jacobi and Gradient
 *
 */
template <class T>
class SecantMethod: public ExtractParameter
{
    public:
        SecantMethod(vector< vector<double> > InitialGuess);             // Secant method need at least 3 initial guess to process
        virtual ~SecantMethod();

        vector<double> runExtract(T *ptr);                                              // the same as above
        vector<double> CalculatedS(T *ptr);                                           // to avoid incidence happen, actually for code reuse, should implement in parent class
    protected:

        void CalJacobiGradient(T *ptr);                                                   // renew Jacobi and Hess in the class
        vector<double>  PartialDeriv(T *ptr, int Iteration);
        void HMatrix(T *ptr);

    private:
        int currentIteration;
};



/* Template function*/


/** Quasi Newton Gradient and Jacobi matrix build
 *
 *  Input is included in class
 *  current parameter value
 * \return: G(gradient),J(jacobi)
 *
 */
 template <class T>
QuasiNewtonMethod<T>::QuasiNewtonMethod(vector<double> InitialGuess)
{
    ProblemSize = InitialGuess.size();                                        // InitialGuess size means how many parameter in the specific problem
    TempParam  = InitialGuess;                                                   // Temporary parameter value is the initial guess
    alpha.push_back(TempParam);                                             // renew alpha[i] to be current initial guess value
    Delta.push_back(0);
}
template <class T>
QuasiNewtonMethod<T>::~QuasiNewtonMethod()
{

}
template <class T>
vector<double>  QuasiNewtonMethod<T>::PartialDeriv(T *ptr,vector<double> param)
{
    vector<double> result(ProblemSize);                                                                                      // result should be the same size as ProblemSize,
    vector<double> temp;
    for(int i=0;i<ProblemSize;i++)
    {
        temp = param;
        temp[i] *= 1.0001;                                                                                                                 // change a(i) to 1.0001a(i)
        result[i] = (ptr->objective(temp)-ptr->objective(param))/(0.0001*param[i]);                     // dobj/da(i) = obj(1.0001*a1,a2,a3...)-obj(a1,a2,...)   /0.0001a1
    }
    return result;
};
template <class T>
void QuasiNewtonMethod<T>::HMatrix(T *ptr)
{
    vector<double> temp;
    for(int i=0;i<ProblemSize;i++)                                                                                                  //row increasing
    {
        for(int j=0;j<ProblemSize;j++)                                                                                              //col increasing
        {
            temp      = TempParam;
            temp[j]  *= 1.0001;                                                                                                             // change a(i)(j) to 1.0001 a(i)(j)
            J[i][j]= (PartialDeriv(ptr,temp)[i]-PartialDeriv(ptr,TempParam)[i])/(0.0001*TempParam[j]);  // the same as Partial Derivative, but dobj/a(i) change to d(dobj/a(i)) /a(j)
        }
    }
};
template<class T>
void QuasiNewtonMethod<T>::CalJacobiGradient(T *ptr)
{
    G=PartialDeriv(ptr,TempParam);
    HMatrix(ptr);
}
template<class T>
vector<double> QuasiNewtonMethod<T>::runExtract(T *ptr)
{
    for(int i=0;i<MaxLoops;i++)                                                    // set max loop searching time
    {
        CalJacobiGradient(ptr);                                                        // every loop calculate new Gradient and Jacobi first
        TempParam = OneIteratioinUpdate();                                   // iteratively renew the alpha;

        if (Delta[Delta.size()-1]<pow(10,-7))                                  // when delta less than 10^(-7), break the loop
        {
            break;
        }
    }
    return TempParam;
};

template<class T>
vector< vector<double> > QuasiNewtonMethod<T>::TwoIterationExtract(T *ptr)
{
    vector< vector<double> >result;
    result.push_back(TempParam);
    CalJacobiGradient(ptr);                                                        // every loop calculate new Gradient and Jacobi first
    result.push_back(OneIteratioinUpdate());                            // iteratively renew the alpha;
    CalJacobiGradient(ptr);                                                        // Did the same thing twice
    result.push_back(OneIteratioinUpdate());
    return result;
};

template<class T>
vector<double> QuasiNewtonMethod<T>::CalculatedS(T *ptr)                                             // calculate dS
{
    vector<double> result(ProblemSize);
    double da;
    vector<double> temp1;
    vector<double> temp2;
    for(int i=0;i<ProblemSize;i++)
    {
        temp1 = alpha[alpha.size()-2];
        temp2 = alpha[alpha.size()-2];
        da     = alpha[alpha.size()-1][i]-alpha[alpha.size()-2][i];                                                                          // last result - second last result at [i]
        temp1[i] = alpha[alpha.size()-1][i];
        result[i]=ptr->objective(temp1) * alpha[alpha.size()-2][i] / (da * ptr->objective(temp2) );                     //dS(i) = obj(a(t-1)+dai)*ai/(obj(a(t-1))*dai)
    }
    return result;
}
/** Secant Gradient and Jacobi matrix build
 *
 *  Input is included in class
 *  historical alpha value
 * \return: G(gradient),J(jacobi)
 *
 */
 template<class T>
SecantMethod<T>::SecantMethod(vector< vector<double> > InitialGuess)
{
    ProblemSize = InitialGuess[0].size();                                        // InitialGuess size means how many parameter in the specific problem
    currentIteration = InitialGuess.size()-1;                                     // current iteration point to the last vector in historical parameter sets
    alpha = InitialGuess;
    TempParam = InitialGuess[currentIteration];
    for(int i=0;i<currentIteration+1;i++)                                         // generate the same size of some accessory vector
    {
        Delta.push_back(0);                                                              // set all Delta at the beginning as 0
        absDeviation.push_back(0);                                                  // set all absolute deviation at the beginning as 0
    }
}

template<class T>
SecantMethod<T>::~SecantMethod()
{
    //dtor
}

template <class T>
vector<double>  SecantMethod<T>::PartialDeriv(T *ptr, int Iteration)
{
    double fDifference= ptr->objective(alpha[Iteration]) - ptr->objective(alpha[Iteration-1]);  // f(alpha@t)- f(alpha@t-1)
    vector<double> result(ProblemSize);
    for(int i=0;i<ProblemSize;i++)
    {
        result[i] = fDifference/(alpha[Iteration][i]-alpha[Iteration-1][i]);                                    // dobj/da(i) = f(alpha@t)- f(alpha@t-1)/(alpha@t- alpha@t-1)
    }
    return result;
};

template <class T>
void SecantMethod<T>::HMatrix(T *ptr)
{
    for(int i=0;i<ProblemSize;i++)                                                                                           //row increasing
    {
        for(int j=0;j<ProblemSize;j++)                                                                                       //col increasing
        {
            J[i][j]= (PartialDeriv(ptr,currentIteration)[i]-PartialDeriv(ptr,currentIteration-1)[i])/(alpha[currentIteration][j]-alpha[currentIteration-1][j]);  // the same as Partial Derivative, but dobj/a(i) change to d(dobj/a(i)) /a(j)
        }
    }
};
template<class T>
void SecantMethod<T>::CalJacobiGradient(T *ptr)
{
    G=PartialDeriv(ptr,currentIteration);                                       // renew Gradient
    HMatrix(ptr);                                                                           // renew Jacobi
}

template<class T>
vector<double> SecantMethod<T>::runExtract(T *ptr)
{
    for(int i=0;i<MaxLoops;i++)                                                    // set max loop searching time
    {
        DirectFullMatrixSolver Dis(J,G);
        Dis.DisplayFullMatrix(J);
        Dis.DisplayVector(G);
        CalJacobiGradient(ptr);                                                        // every loop calculate new Gradient and Jacobi first

        TempParam = OneIteratioinUpdate();                                   // iteratively renew the alpha;
        if (Delta[Delta.size()-1]<pow(10,-7))                                  // when delta less than 10^(-7), break the loop
        {
            break;
        }
    }
    return TempParam;
};

template<class T>
vector<double> SecantMethod<T>::CalculatedS(T *ptr)                                             // calculate dS
{
    vector<double> result(ProblemSize);
    double da;
    vector<double> temp1;
    vector<double> temp2;
    for(int i=0;i<ProblemSize;i++)
    {
        temp1 = alpha[alpha.size()-2];
        temp2 = alpha[alpha.size()-2];
        da     = alpha[alpha.size()-1][i]-alpha[alpha.size()-2][i];
        temp1[i] = alpha[alpha.size()-1][i];
        result[i]=ptr->objective(temp1) * alpha[alpha.size()-2][i] / (da * ptr->objective(temp2) );                     //dS(i) = obj(a(t-1)+dai)*ai/(obj(a(t-1))*dai)
    }
    return result;
}
#endif // EXTRACTPARAMETER_H
