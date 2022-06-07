//
// Created by uros on 02/06/22.
//

#include "ForParallelRegressionSTL.h"

struct FunctionCalculatorPFS {
    /**struct that enables usage of parallel reduce;
      @param uses previously generated points
     */
    std::vector<Point> &points;
    double x_sum = 0, x2_sum = 0, y_sum = 0, x_ysum = 0;

    void operator()(const tbb::blocked_range<int> &range) {
        for (int i = range.begin(); i != range.end(); ++i) {
            x_sum = x_sum + this->points[i].get_x();
            y_sum = y_sum + this->points[i].get_y();
            x2_sum = x2_sum + pow(this->points[i].get_x(), 2);
            x_ysum = x_ysum + this->points[i].get_x() * points[i].get_y();
        }
    }

    void join(const FunctionCalculatorPFS &functionCalculatorPFS) {
        x_sum += functionCalculatorPFS.x_sum;
        y_sum += functionCalculatorPFS.y_sum;
        x2_sum += functionCalculatorPFS.x2_sum;
        x_ysum += functionCalculatorPFS.x_ysum;
    }

    FunctionCalculatorPFS(FunctionCalculatorPFS &functionCalculatorPFS, tbb::split) : points(functionCalculatorPFS.points) {};

    FunctionCalculatorPFS(std::vector<Point> &points) : points(points) {};
};

struct PointsCalculator {
    /**struct that enables to calculate uniform points using parallel for
  @param uses previously generated points and uniformly distributed points on x axis
 */
    std::vector<Point> &points;
    std::vector<double> &x;
    double a, b;

    void operator()(const tbb::blocked_range<int> &range) const {
        for (int i = range.begin(); i != range.end(); ++i) {
            points[i] = Point(x[i], a * x[i] + b);
        }
    }

    PointsCalculator(std::vector<Point> &points, std::vector<double> &x, double a, double b)
            : points(points), x(x), a(a), b(b) {};
};

struct less_than_point {
    /**struct that enables usage of parallel sort on Point class
 */
    inline bool operator()(const Point &point1, const Point &point) const {
        return (point1.get_x() < point.get_x());
    }
};

void ForParallelRegressionSTL::calculate_Function(std::vector<Point> &points) {
    /**
* calculates parameters of approximated linear function
* @param value concurrent_vector point reference to previously generated points with error
*/

    int n = points.size();
    FunctionCalculatorPFS functionCalculatorPFS(points);
    tbb::parallel_reduce(tbb::blocked_range<int>(0, n), functionCalculatorPFS);
    double x_ysum = functionCalculatorPFS.x_ysum;
    double x_sum = functionCalculatorPFS.x_sum;
    double x2_sum = functionCalculatorPFS.x2_sum;
    double y_sum = functionCalculatorPFS.y_sum;

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);

}

std::vector<Point> ForParallelRegressionSTL::calculate_points(std::vector<double> &x) {
    /**
* calculates points of approximated linear function
* @param value uniformly distributed values of x axis
* @return Points of approximated function calculated using param and previously calculated linear function params
*/
    Point point(0, 0);
    std::vector<Point> points(x.size(), point);
    PointsCalculator pointsCalculator(points, x, a, b);
    tbb::parallel_for(tbb::blocked_range<int>(0, x.size()), pointsCalculator);

    //  tbb::parallel_sort(points, less_than_point());


    return points;
}