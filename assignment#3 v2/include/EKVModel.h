
#include<vector>

#ifndef EKVMODEL_H
#define EKVMODEL_H

using namespace std;


/** Parent class
 *
 * construct a model with Input: Ids, Vgs, Vds,
 * \return: best fit Is, Kappa,Vth
 *
 * FullParameterSearch has shared part in below, the subclass only deliver parameters into parent class to calculate
 *
 */

class EKVModel
{
    public:
        EKVModel();
        virtual ~EKVModel();

        template <class T>
        vector<double> FullParameter2Search(vector<double> x1,vector<double> x2, vector<double> x3, T *ptr)
        {
            vector<double> result;                                                                   // store the final return value
            vector<double> temp;                                                                    // store temporary input vector of the problem
            for(int loop=0;loop<2;loop++)                                                      // at least run twice, get 2 minimum value
            {
                result.push_back(x1[0]);                                                            // default x1[0], x2[0],x3[0] make the minimum of the system
                result.push_back(x2[0]);
                result.push_back(x3[0]);
                double Vmin= ptr->objective(result);
                temp = result;
                for(int i=0;i<x1.size();i++)                                                        // go through all x1
                {
                    temp[0]=x1[i];
                    for(int j=0;j<x2.size();j++)                                                    // go through all x2
                    {
                        temp[1]=x2[j];
                        for(int k=0;k<x3.size();k++)                                              // go through all x3
                        {
                            temp[2]=x3[k];
                            if ((ptr->objective(temp)<Vmin) && ((x1[i]!=result[0]) || (x2[j]!=result[1]) || (x3[k]!=result[2])))    // whether new value less than existed minimum
                            {
                                Vmin=ptr->objective(temp);
                                result[0+loop*3] = x1[i];                                          // each minimum value return x1
                                result[1+loop*3] = x2[j];                                          // each minimum value return x2
                                result[2+loop*3] = x3[k];                                          // each minimum value return x3
                            }
                        }
                    }
                }
            }
            return result;
        };
    protected:
        vector<double> Id;
        vector<double> Vgs;
        vector<double> Vds;
        double Is,Kappa,Vth;
    private:

};

/** Subclass Task4
 *
 * only function is Objective function
 */

class Task4: public EKVModel
{
    public:
        Task4(vector<double> Smodel,vector<double> Input1,vector<double> Input2, double x1,double x2,double x3);
        virtual ~Task4();
        double objective(vector<double> Parameter);
        void runExtract();
        vector<double> FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3);
};

/** Subclass Task5
 *
 * only function is Objective function
 */
class Task5: public EKVModel
{
    public:
        Task5(vector<double> Smodel,vector<double> Input1,vector<double> Input2, double x1,double x2,double x3);
        virtual ~Task5();
        double objective(vector<double> Parameter);
        void runExtract();
         vector<double> FullParameterSearch(vector<double> x1,vector<double> x2, vector<double> x3);
};
#endif // EKVMODEL_H
