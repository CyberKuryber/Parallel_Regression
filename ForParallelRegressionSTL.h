//
// Created by uros on 02/06/22.
//

#ifndef PARALLEL_REGRESSION_FORPARALLELREGRESSIONSTL_H
#define PARALLEL_REGRESSION_FORPARALLELREGRESSIONSTL_H
#include <tbb/concurrent_vector.h>
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "Point.h"
#include <cmath>
#include "tbb/parallel_sort.h"
#include "iostream"

class ForParallelRegressionSTL {
public:
    void calculate_Function(std::vector<Point> &points);

    std::vector<Point> calculate_points(std::vector<double> &x);

//private:
    double a;
    double b;
};


#endif //PARALLEL_REGRESSION_FORPARALLELREGRESSIONSTL_H
