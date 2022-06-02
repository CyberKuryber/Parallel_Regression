//
// Created by uros on 02/06/22.
//

#ifndef PARALLEL_REGRESSION_SERIALLINEARREGRESSIONSTL_H
#define PARALLEL_REGRESSION_SERIALLINEARREGRESSIONSTL_H

#include <vector>
#include <cmath>
#include "Point.h"

class SerialLinearRegressionSTL {
public:
    void calculate_Function(std::vector<Point> &points);
    std::vector<Point> calculate_points(std::vector<double> &x);

    double a;
    double b;
};


#endif //PARALLEL_REGRESSION_SERIALLINEARREGRESSIONSTL_H
