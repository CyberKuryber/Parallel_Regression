//
// Created by uros on 20/04/22.
//

#include "InputHandler.h"

void InputHandler::parse_input() {
    std::ifstream infile(INPUT_FILE);
    std::string s;
    infile >> s;
    std::string delimiter = "|";
    this->a = std::stod(s.substr(0, s.find(delimiter)));
    this->b = std::stod(s.substr(1, s.find(delimiter)));
}

tbb::concurrent_vector<Point> points;

struct Shaker {
    double increment;
    double x_error;
    double y_error;
    double a;
    double b;

    void operator()(const tbb::blocked_range<int> &range) const {
        short data;
        for (int i = range.begin(); i != range.end(); ++i) {
            srand(time(NULL));
            double x_rand = rand() % 101 - 50;
            double y_rand = rand() % 101 - 50;

            double new_x = increment * (i + 1) + x_error * x_rand / 100 * increment * (i + 1);
            double new_y = (a * increment * (i + 1) + b) + y_error * y_rand / 100 * (a * increment * (i + 1) + b);


            points.push_back(Point(new_x, new_y));
        }
    }

    Shaker(double a, double b, double increment, double x_error, double y_error) : a(a), b(b), increment(increment),
                                                                                   x_error(x_error),
                                                                                   y_error(y_error) {};
};


tbb::concurrent_vector<Point>
InputHandler::generate_dots(double x_min, double x_max, double x_error, double y_error, int point_count) {
    Shaker shaker(a, b, x_max - x_min, x_error, y_error);

    tbb::parallel_for(tbb::blocked_range<int>(0, point_count), shaker);
    return points;

}