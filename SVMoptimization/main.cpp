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

#define MaxTrainingSize 23
#define MaxTestingSize   5

using namespace std;

int main()
{
    /**
     * read file
     *
     */
    const int RowElements=269;  // assume X have 269 features

    /*open the file*/
    //ifstream fin("test.txt");
    ifstream fin("solr_s0428_train_data.txt");

    if (! fin.is_open())
    {
        cout << "Could not open file!" << '\n';
    }

    /*ignore the title and top comments*/
    //while (fin.peek() == '%') fin.ignore(256, '\n');

    /* initialize read in parameter */
    vector<double> Y;                                                           // assume Y is only 1 dimensional
    vector< vector<double> > X;
    string str;
    int RowNumber = 1;
    int parity = 0;
    int Cfeature = 0;                                                               // current feature
    vector<double> Inter;
    int counter1 = 0;                                                              // set a counter to count how many X vector input as training set and control dimension of Data size
    int counter2 = 0;                                                              // set a counter to count X test
    double num;
    vector< vector<double> > Xtest;
    vector<double> Ytest;

    /* initialize read in parameter */
    while(getline(fin, str,','))                                                 // get str till next comma
    {
        istringstream ss(str);
        while(ss >> num)                                                        // when ss is convertable to be double, store it into num
        {
            if (parity == 0)                                                         // single row
            {
                if(Cfeature==0)                                                   // if a new row start
                    (counter1<MaxTrainingSize)?X.push_back(Inter):Xtest.push_back(Inter);                                                                                                      // push a new row to X, if training size approach, then do to Xtest
                (counter1< MaxTrainingSize)?X[(RowNumber-1)/2].push_back(num):Xtest[(RowNumber-1)/2-MaxTrainingSize].push_back(num);         // push new element to X[i], if training size approach, then do to Xtest
                Cfeature++;                                                         // Cfeature increment
                if(Cfeature == RowElements)                                   // at the end of the row
                {
                    Cfeature= 0;                                                    // pointer to next row head
                    parity  = 1;                                                       // next row is even
                    RowNumber ++;                                             // increase row number
                }
            }
            else if (parity == 1)                                               // even row
            {
                (counter1<MaxTrainingSize)?Y.push_back(num):Ytest.push_back(num);                          // push back value to training label, if training set full, then give to testing label
                parity  = 0;
                RowNumber ++;
                (counter1<MaxTrainingSize)?counter1 ++:counter2++;                                                         // count input vector and corresponding label
            }
        }
        /* set dimension of learning set */
        if ((counter1 >= MaxTrainingSize)  && (counter2 >= MaxTestingSize) )                                    // set training size less than max training size
        {
            break;
        }
    }


    //DisplayFullMatrix(X);
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
//    vector<double> Xtest(4);                      // basic test in only 4 dimensions
//    Xtest[0]=1;
//    Xtest[1]=2;
//    Xtest[2]=3;
//    Xtest[3]=6;

    double Epsilon=0.2;
    vector<double> result;
    SVMdual svm(X,Y,Epsilon);
    svm.GetExtract();
    result = svm.Predict(Xtest);
    printf("prediction result:\n");
    DisplayVector(result);
    DisplayVector(Ytest);
    printf("----------------------------\n");
    printf("\n");

    /* compute testing error */
    double R2    = svm.CalR2Accuracy(Xtest);
    double rmse = svm.CalRmseAccuracy(Xtest);
    printf("R2 accuracy = %lf ,   rmse = %lf \n",  R2,rmse);
}
