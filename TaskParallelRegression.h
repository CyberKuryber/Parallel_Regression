//
// Created by uros on 18/05/22.
//

#ifndef PARALLEL_REGRESSION_TASKPARALLELREGRESSION_H
#define PARALLEL_REGRESSION_TASKPARALLELREGRESSION_H


#include <tbb/concurrent_vector.h>
#include "tbb/blocked_range.h"
#include "Point.h"
#include <cmath>
#include "tbb/parallel_sort.h"
#include "iostream"
#include "tbb/task_group.h"

class TaskParallelRegression {
public:
    void calculate_Function(tbb::concurrent_vector<Point> &points);

    tbb::concurrent_vector<Point> calculate_points(tbb::concurrent_vector<double> &x);

    std::vector<double> calculate_sums(tbb::concurrent_vector<Point> &points, int start_idx, int stop_idx);

    std::vector<double> sums(tbb::concurrent_vector<Point> &points, int start_idx, int stop_idx);


//private:
    double a;
    double b;


    double cutoff = 1000;
};


#endif //PARALLEL_REGRESSION_TASKPARALLELREGRESSION_H
