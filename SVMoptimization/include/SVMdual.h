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
    protected:
        bool Checktrain();
        double CalTrainingAccuracy();
    private:
        /* all privates are data*/
        vector<double> Gradient;
        double rho;
        vector<double> E;
        vector<double> y;
        vector< vector<double> > Xtrain;
        double K(vector<double> a, vector<double> b);
};

#endif // SVMDUAL_H
