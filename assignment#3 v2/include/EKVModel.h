
#include<vector>

#ifndef EKVMODEL_H
#define EKVMODEL_H

using namespace std;


/** Parent class
 *
 * construct a model with Input: Ids, Vgs, Vds,
 * \return: best fit Is, Kappa,Vth
 *
 */

class EKVModel
{
    public:
        EKVModel();
        virtual ~EKVModel();
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

};
#endif // EKVMODEL_H
