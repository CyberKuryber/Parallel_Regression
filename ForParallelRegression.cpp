//
// Created by uros on 22/04/22.
//

#include "ForParallelRegression.h"


struct FunctionCalculator {
    /**struct that enables usage of parallel reduce;
      @param uses previously generated points
     */
    tbb::concurrent_vector<Point> &points;
    double x_sum = 0, x2_sum = 0, y_sum = 0, x_ysum = 0;

    void operator()(const tbb::blocked_range<int> &range) {
        for (int i = range.begin(); i != range.end(); ++i) {
            x_sum = x_sum + points[i].get_x();
            y_sum = y_sum + points[i].get_y();
            x2_sum = x2_sum + pow(points[i].get_x(), 2);
            x_ysum = x_ysum + points[i].get_x() * points[i].get_y();
        }
    }

    void join(const FunctionCalculator &functionCalculator) {
        x_sum += functionCalculator.x_sum;
        y_sum += functionCalculator.y_sum;
        x2_sum += functionCalculator.x2_sum;
        x_ysum += functionCalculator.x_ysum;
    }

    FunctionCalculator(FunctionCalculator &functionCalculator, tbb::split) : points(functionCalculator.points) {};

    FunctionCalculator(tbb::concurrent_vector<Point> &points) : points(points) {};
};

struct PointsCalculator {
    /**struct that enables to calculate uniform points using parallel for
  @param uses previously generated points and uniformly distributed points on x axis
 */
    tbb::concurrent_vector<Point> &points;
    tbb::concurrent_vector<double> &x;
    double a, b;

    void operator()(const tbb::blocked_range<int> &range) const {
        for (int i = range.begin(); i != range.end(); ++i) {
            points.push_back(Point(x[i], a * x[i] + b));
        }
    }

    PointsCalculator(tbb::concurrent_vector<Point> &points, tbb::concurrent_vector<double> &x, double a, double b)
            : points(points), x(x), a(a), b(b) {};
};

struct less_than_point {
    /**struct that enables usage of parallel sort on Point class
 */
    inline bool operator()(const Point &point1, const Point &point) const {
        return (point1.get_x() < point.get_x());
    }
};

void ForParallelRegression::calculate_Function(tbb::concurrent_vector<Point> &points) {
    /**
* calculates parameters of approximated linear function
* @param value concurrent_vector point reference to previously generated points with error
*/

    int n = points.size();
    FunctionCalculator functionCalculator(points);
    tbb::parallel_reduce(tbb::blocked_range<int>(0, n), functionCalculator);
    double x_ysum = functionCalculator.x_ysum;
    double x_sum = functionCalculator.x_sum;
    double x2_sum = functionCalculator.x2_sum;
    double y_sum = functionCalculator.y_sum;

    this->a = (n * x_ysum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    this->b = (x2_sum * y_sum - x_sum * x_ysum) / (x2_sum * n - x_sum * x_sum);

}

tbb::concurrent_vector<Point> ForParallelRegression::calculate_points(tbb::concurrent_vector<double> &x) {
    /**
* calculates points of approximated linear function
* @param value uniformly distributed values of x axis
* @return Points of approximated function calculated using param and previously calculated linear function params
*/
    tbb::concurrent_vector<Point> points;
    PointsCalculator pointsCalculator(points, x, a, b);
    tbb::parallel_for(tbb::blocked_range<int>(0, x.size()), pointsCalculator);

    tbb::parallel_sort(points, less_than_point());


    return points;
}


