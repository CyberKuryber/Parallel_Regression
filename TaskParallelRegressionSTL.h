//
// Created by uros on 02/06/22.
//

#ifndef PARALLEL_REGRESSION_TASKPARALLELREGRESSIONSTL_H
#define PARALLEL_REGRESSION_TASKPARALLELREGRESSIONSTL_H
#include <tbb/concurrent_vector.h>
#include "tbb/blocked_range.h"
#include "Point.h"
#include <cmath>
#include "tbb/parallel_sort.h"
#include "iostream"
#include "tbb/task_group.h"
#include <vector>


class TaskParallelRegressionSTL {
public:
    void calculate_Function(std::vector<Point> &points);

    std::vector<Point> calculate_points(std::vector<double> &x);

    std::vector<double> calculate_sums(std::vector<Point> &points, int start_idx, int stop_idx);

    std::vector<double> sums(std::vector<Point> &points, int start_idx, int stop_idx);


//private:
    double a;
    double b;


    double cutoff = 1000;

};


#endif //PARALLEL_REGRESSION_TASKPARALLELREGRESSIONSTL_H
