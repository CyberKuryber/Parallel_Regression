//
// Created by uros on 02/06/22.
//

#include "TaskParallelRegressionSTL.h"

struct PointsCalculator {
    /**struct that enables to calculate uniform points using parallel for
  @param uses previously generated points and uniformly distributed points on x axis
 */
    std::vector<Point> &points;
    std::vector<double> &x;
    double a, b;

    void operator()(const tbb::blocked_range<int> &range) const {
        for (int i = range.begin(); i != range.end(); ++i) {
            points.push_back(Point(x[i], a * x[i] + b));
        }
    }

    PointsCalculator(std::vector<Point> &points, std::vector<double> &x, double a, double b)
            : points(points), x(x), a(a), b(b) {};
};

void TaskParallelRegressionSTL::calculate_Function(std::vector<Point> &points) {
    /**
 * calculates parameters of approximated linear function
 * @param value concurrent_vector point reference to previously generated points with error
 */
    std::vector<double> s = calculate_sums(points, 0, points.size());

    double x_sum = s[0];
    double y_sum = s[1];
    double x2_sum = s[2];
    double x_ysum = s[3];
    double n = points.size();

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);
}

std::vector<Point> TaskParallelRegressionSTL::calculate_points(std::vector<double> &x) {
    /**
* calculates points of approximated linear function
* @param value uniformly distributed values of x axis
* @return Points of approximated function calculated using param and previously calculated linear function params
*/
    std::vector<Point> points;
    PointsCalculator pointsCalculator(points, x, a, b);
    tbb::parallel_for(tbb::blocked_range<int>(0, x.size()), pointsCalculator);
    return points;
}

std::vector<double>
TaskParallelRegressionSTL::calculate_sums(std::vector<Point> &points, int start_idx, int stop_idx) {
    /**
 * Creates task group and recursivly splits length of this part of calculation on vector using start and stop index
 * @param values concurrent_vector point reference to previously generated points with error first and last+1 index of this part of calculation
     * @return sums of x,y,x^2,xy stored in vector
 */
    tbb::task_group g;
    std::vector<double> first;
    std::vector<double> second;
    int diff = (stop_idx - start_idx) / 2;
    if ((stop_idx - start_idx) > cutoff) {
        g.run([&] { first = calculate_sums(points, start_idx, start_idx + diff); });
        g.run([&] { second = calculate_sums(points, start_idx + diff, stop_idx); });
        g.wait();
        for (int i = 0; i < 4; ++i) {
            first[i] += second[i];
        }
        return first;
    } else {
        return sums(points, start_idx, stop_idx);
    }

}

std::vector<double> TaskParallelRegressionSTL::sums(std::vector<Point> &points, int start_idx, int stop_idx) {
    /**
* Serially calculates sums on this part of the vector (called when split parts are too small)
* @param values concurrent_vector point reference to previously generated points with error first and last+1 index of this part of calculation
 * @return sums of x,y,x^2,xy stored in vector
*/

    double x_sum = 0, y_sum = 0, x2_sum = 0, x_ysum = 0;

    for (int i = start_idx; i < stop_idx; i++) {
        x_sum = x_sum + points[i].get_x();
        y_sum = y_sum + points[i].get_y();
        x2_sum = x2_sum + pow(points[i].get_x(), 2);
        x_ysum = x_ysum + points[i].get_x() * points[i].get_y();
    }
    std::vector<double> s = {x_sum, y_sum, x2_sum, x_ysum};
    return s;
}
