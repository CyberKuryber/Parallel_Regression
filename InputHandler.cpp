//
// Created by uros on 20/04/22.
//

#include "InputHandler.h"

void InputHandler::parse_input() {
    std::ifstream infile;
    infile.open(INPUT_FILE);

    if (!infile.is_open()) {
        std::cout << "Couldn't open file " << INPUT_FILE << std::endl;
        std::exit(-2);
    }

    std::string s;
    std::string delimiter = "|";
    getline(infile, s);
    this->a = std::stod(s.substr(0, s.find(delimiter)));
    this->b = std::stod(s.substr(1, s.find(delimiter)));
    infile.close();
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
            double x_rand = (rand() % 101 - 50)/100.0;
            double y_rand = (rand() % 101 - 50)/100.0;
            double new_x = increment * (i + 1);
            double calculated_x_err = x_error * x_rand / 100 *new_x;
            new_x += calculated_x_err;
            double new_y = (a * increment * (i + 1) + b);
            double calculated_y_err =  y_error * y_rand / 100 * new_y;
            new_y+= calculated_y_err;


            points.push_back(Point(new_x, new_y));
        }
    }

    Shaker(double a, double b, double increment, double x_error, double y_error) : a(a), b(b), increment(increment),
                                                                                   x_error(x_error),
                                                                                   y_error(y_error) {};
};


tbb::concurrent_vector<Point>
InputHandler::generate_dots(double x_min, double x_max, double x_error, double y_error, int point_count) {
    Shaker shaker(a, b, (x_max - x_min)/point_count, x_error, y_error);

    tbb::parallel_for(tbb::blocked_range<int>(0, point_count), shaker);
    return points;

}

double InputHandler::calculate_original(double x) const {
    return this->a*x + this->b;
}
