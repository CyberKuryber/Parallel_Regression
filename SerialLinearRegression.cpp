//
// Created by uros on 20/04/22.
//

#include "SerialLinearRegression.h"

void SerialLinearRegression::calculate_Function(std::vector<Point>& points) {
    double x_sum = 0, x2_sum = 0, y_sum = 0, x_ysum = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        x_sum = x_sum + points[i].get_x();
        y_sum = y_sum + points[i].get_y();
        x2_sum = x2_sum + pow(points[i].get_x(), 2);
        x_ysum = x_ysum + points[i].get_x() * points[i].get_y();
    }

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);



}

std::vector<Point> SerialLinearRegression::calculate_points(std::vector<double> &x) {
    std::vector<Point> y;
    for (auto value:x) {
        y.push_back(Point(value, a*value+b));
    }
    return y;
}