//
// Created by uros on 18/05/22.
//

#include "TaskParallelRegression.h"

void TaskParallelRegression::calculate_Function(tbb::concurrent_vector<Point> &points) {
    std::vector<double> s = calculate_sums(points,0,points.size());

    double x_ysum = s[3];
    double x_sum = s[0];
    double x2_sum = s[2];
    double y_sum = s[1];
    double n = points.size();

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);
}

tbb::concurrent_vector<Point> TaskParallelRegression::calculate_points(tbb::concurrent_vector<double> &x) {
    tbb::concurrent_vector<Point> y;
    for (auto value: x) {
        y.push_back(Point(value, a * value + b));
    }
    return y;
}

std::vector<double>  TaskParallelRegression::calculate_sums(tbb::concurrent_vector<Point> &points, int start_idx, int stop_idx) {
    tbb::task_group g;
    std::vector<double>  first;
    std::vector<double>  second;
    int diff = (stop_idx-start_idx)/2;
    if ((stop_idx- start_idx)>cutoff){
        g.run([&] {first =  calculate_sums(points,start_idx,start_idx+diff);});
        g.run([&] {second =  calculate_sums(points,start_idx+diff,stop_idx);});
        g.wait();
        for (int i = 0; i < 4; ++i) {
            first[i] += second[i];
        }
        return first;
    }
    else {
        return sums(points,start_idx,stop_idx);
    }

}

std::vector<double> TaskParallelRegression::sums(tbb::concurrent_vector<Point> &points, int start_idx, int stop_idx) {
    double x_sum=0, y_sum=0,x2_sum=0,x_ysum=0;

    for (int i = start_idx; i < stop_idx; i++) {
        x_sum = x_sum + points[i].get_x();
        y_sum = y_sum + points[i].get_y();
        x2_sum = x2_sum + pow(points[i].get_x(), 2);
        x_ysum = x_ysum + points[i].get_x() * points[i].get_y();
    }
    std::vector<double> s ={x_sum,y_sum,x2_sum,x_ysum};
    return s;
}
