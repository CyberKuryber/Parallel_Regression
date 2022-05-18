//
// Created by uros on 22/04/22.
//

#ifndef PARALLEL_REGRESSION_FORPARALLELREGRESSION_H
#define PARALLEL_REGRESSION_FORPARALLELREGRESSION_H


#include <tbb/concurrent_vector.h>
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "Point.h"
#include <cmath>
#include "tbb/parallel_sort.h"
#include "iostream"

class ForParallelRegression {
public:
    void calculate_Function(tbb::concurrent_vector<Point> &points);

    tbb::concurrent_vector<Point> calculate_points(tbb::concurrent_vector<double> &x);

//private:
    double a;
    double b;
};


#endif //PARALLEL_REGRESSION_FORPARALLELREGRESSION_H
