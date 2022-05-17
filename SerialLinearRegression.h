//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H
#define PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H

#include <vector>
#include <cmath>
#include "tbb/concurrent_vector.h"
#include "Point.h"

class SerialLinearRegression {
public:
    void calculate_Function(tbb::concurrent_vector<Point> &points);

    std::vector<Point> calculate_points(std::vector<double> &x);

//private:
    double a;
    double b;


};


#endif //PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H
