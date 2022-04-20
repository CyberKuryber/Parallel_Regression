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
#include <fstream>
#include "time.h"

#define INPUT_FILE "input_file"

class InputHandler {
private:
    double a;
    double b;
public:
    void parse_input();

    tbb::concurrent_vector<Point> generate_dots(double x_min, double x_max, double x_error, double y_error, int ponts);

};


#endif //PARALLEL_REGRESSION_INPUTHANDLER_H
