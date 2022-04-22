//
// Created by uros on 22/04/22.
//

#include "forParallelRegression.h"

std::atomic<double> x_sum(0), x2_sum(0), y_sum(0), x_ysum(0);

struct FunctionCalculator{
    tbb::concurrent_vector<Point> &points;

    void operator()(const tbb::blocked_range<int> &range) const {
        for (int i = range.begin(); i != range.end(); ++i) {
            x_sum = x_sum + points[i].get_x();
            y_sum = y_sum + points[i].get_y();
            x2_sum = x2_sum + pow(points[i].get_x(), 2);
            x_ysum = x_ysum + points[i].get_x() * points[i].get_y();
        }
    }
    FunctionCalculator(tbb::concurrent_vector<Point> &points): points(points){};
};


void forParallelRegression::calculate_Function(tbb::concurrent_vector<Point> &points) {
    int n = points.size();
    FunctionCalculator functionCalculator(points);
    tbb::parallel_for(tbb::blocked_range<int>(0,n),functionCalculator);

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);
}

std::vector<Point> forParallelRegression::calculate_points(std::vector<double> &x) {


    return nullptr;
}
