//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_INPUTHANDLER_H
#define PARALLEL_REGRESSION_INPUTHANDLER_H


#include "tbb/concurrent_vector.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "Point.h"
#include <string>
#include <iostream>
#include <fstream>
#include "time.h"
#include <vector>

#define INPUT_FILE "../data/input_file"

class InputHandler {
private:
    double a;
    double b;

public:
    tbb::concurrent_vector<Point> concurrent_points;
    std::vector<Point> stl_points;
    tbb::concurrent_vector<double> concurrent_x;
    std::vector<double> stl_x;


    void parse_input(std::string s);

    double calculate_original(double x) const;

    tbb::concurrent_vector<Point> generate_dots(double x_min, double x_max, double x_error, double y_error, int ponts);

    long point_num = 0;
    int x_err = 0;
    int y_err = 0;
    int min_x = 0;
    int max_x = 0;
    std::vector<int> cutoff;


};


#endif //PARALLEL_REGRESSION_INPUTHANDLER_H
