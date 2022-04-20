//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H
#define PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H

#include <vector>
#include <cmath>
#include "Point.h"

class SerialLinearRegression {
public:
    void calculate_Function(std::vector<Point>& points);
    std::vector<Point> calculate_points(std::vector<double>& x);
private:
    double a;
    double b;



};


#endif //PARALLEL_REGRESSION_SERIALLINEARREGRESSION_H
