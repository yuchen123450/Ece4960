#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <float.h>
#include <ctype.h>
#include <stdarg.h>
#include "Test.h"
#include "SVMdual.h"

using namespace std;

int main()
{
    /**
     * read file
     *
     */
    const int RowElements=4;  // assume X have 4 features

    /*open the file*/
    ifstream fin("test.txt");
    if (! fin.is_open())
    {
        cout << "Could not open file!" << '\n';
    }

    /*ignore the title and top comments*/
    while (fin.peek() == '%') fin.ignore(256, '\n');

    vector<double> Y;   //assume Y is only 1 dimensional
    vector< vector<double> > X;
    string str;
    int RowNumber = 1;
    int parity = 0;
    int Cfeature = 0;
    vector<double> Inter;
    while(getline(fin, str,','))  // get str till next comma
    {
        istringstream ss(str);
        double num;
        while(ss >> num)          // when ss is convertable to be double, store it into num
        {
            if (parity == 0)      // single row
            {
                if(Cfeature==0)
                    X.push_back(Inter);
                X[(RowNumber-1)/2].push_back(num);
                Cfeature++;
                if(Cfeature == 4)
                {
                    Cfeature= 0;
                    parity  = 1;
                    RowNumber ++;
                }
            }
            else if (parity == 1) // even row
            {
                Y.push_back(num);
                parity  = 0;
                RowNumber ++;
            }
        }
    }

    /**
     * test
     * only for Matrix operator
     * other tests are included in their own class
     */
    MatrixTest Test1;
    Test1.RunTest();

    /**
     * compute
     *
     */
    vector<double> Xtest(4);
    Xtest[0]=1;
    Xtest[1]=2;
    Xtest[2]=3;
    Xtest[3]=6;
    double Epsilon=0;
    double result;
    SVMdual svm(X,Y,Epsilon);
    svm.GetExtract();
    result = svm.Predict(Xtest);
    printf("prediction result:%lf\n", result);

    /* compute training error */
    vector<double> yEst;
    yEst = svm.Predict(X);
    DisplayVector(yEst);
    DisplayVector(Y);
}
