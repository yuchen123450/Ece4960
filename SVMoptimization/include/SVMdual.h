/**  SVR module
 *
 * SVR problem setting
 * Initialize something in SVR problem
 * Chen Yu
 * May.23/2017
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include "ExtractionParameter.h"
#include "MatrixOperate.h"

#ifndef SVMDUAL_H
#define SVMDUAL_H

using namespace std;
class SVMdual
{
    public:
        /*constructor and destructor*/
         SVMdual(vector< vector<double> > X,vector<double> Y,double Epsilon);
        virtual ~SVMdual();

        /*data*/
        int DSize;
        int FeatureSize;
        double Epsilon;
        vector<double> alpha;

        /*function*/
        double objective(vector<double> alpha);
        double CalculateRho();
        double DotProduct(vector<double> a, vector<double> b);
        void GetExtract();
        double Predict(vector<double> Xtest);
        vector<double> Predict(vector< vector<double> > Xtest);
        double CalR2Accuracy(vector< vector<double> >Xtest);
        double CalRmseAccuracy(vector< vector<double> > Xtest);
    protected:
        bool Checktrain();
        double CalTrainingR2Accuracy();
        double CalTrainingRmseAccuracy();
    private:
        /* all privates are data*/
        vector<double> Gradient;
        vector< vector<double> > LocalMinSet;
        double rho;
        vector<double> E;
        vector<double> y;
        vector< vector<double> > Xtrain;
        double K(vector<double> a, vector<double> b);
};

#endif // SVMDUAL_H
