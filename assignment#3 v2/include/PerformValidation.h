/** Perform the validation of that existed problem
 *
 * Nothing input
 * show whether the extraction parameter class work as expected
 * \return: c,m be about 10 and -0.5
 *
 */

#include <cmath>
#include <stdlib.h>
#include <vector>
#include "ExtractParameter.h"

#ifndef PERFORMVALIDATION_H
#define PERFORMVALIDATION_H

using namespace std;
class PerformValidation
{
    public:
        PerformValidation();
        virtual ~PerformValidation();

        double objective(vector<double> param);
        void runExtraction();
    protected:

    private:
        vector<double> y;
        vector<double> x;
        vector<double> sample;
};

#endif // PERFORMVALIDATION_H
