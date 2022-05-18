//
// Created by uros on 20/04/22.
//

#include "SerialLinearRegression.h"

void SerialLinearRegression::calculate_Function(tbb::concurrent_vector<Point> &points) {
    /**
     * calculates parameters of approximated linear function
     * @param value concurrent_vector point reference to previously generated points with error
     */
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
    /**
 * calculates points of approximated linear function
 * @param value uniformly distributed values of x axis
     * @return Points of approximated function calculated using param and previously calculated linear function params
 */
    std::vector<Point> y;
    for (auto value: x) {
        y.push_back(Point(value, a * value + b));
    }
    return y;
}