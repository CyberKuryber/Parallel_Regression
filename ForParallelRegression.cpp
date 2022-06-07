//
// Created by uros on 22/04/22.
//

#include "ForParallelRegression.h"


struct FunctionCalculatorPF {
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

    void join(const FunctionCalculatorPF &functionCalculatorPF) {
        x_sum += functionCalculatorPF.x_sum;
        y_sum += functionCalculatorPF.y_sum;
        x2_sum += functionCalculatorPF.x2_sum;
        x_ysum += functionCalculatorPF.x_ysum;
    }

    FunctionCalculatorPF(FunctionCalculatorPF &functionCalculatorPF, tbb::split) : points(functionCalculatorPF.points) {};

    FunctionCalculatorPF(tbb::concurrent_vector<Point> &points) : points(points) {};
};

struct PointsCalculatorPF {
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

    PointsCalculatorPF(tbb::concurrent_vector<Point> &points, tbb::concurrent_vector<double> &x, double a, double b)
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
    FunctionCalculatorPF functionCalculatorPF(points);
    tbb::parallel_reduce(tbb::blocked_range<int>(0, n), functionCalculatorPF);
    double x_ysum = functionCalculatorPF.x_ysum;
    double x_sum = functionCalculatorPF.x_sum;
    double x2_sum = functionCalculatorPF.x2_sum;
    double y_sum = functionCalculatorPF.y_sum;

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
    PointsCalculatorPF pointsCalculatorPF(points, x, a, b);
    tbb::parallel_for(tbb::blocked_range<int>(0, x.size()), pointsCalculatorPF);

  //  tbb::parallel_sort(points, less_than_point());


    return points;
}


