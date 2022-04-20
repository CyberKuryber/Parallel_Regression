//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_INPUTHANDLER_H
#define PARALLEL_REGRESSION_INPUTHANDLER_H


#include <vector>
#include "Point.h"
#include <string>
#include <fstream>
#define INPUT_FILE "input_file"

class InputHandler {
private:
    double a;
    double b;
public:
    void parse_input();
    std::vector<Point> generate_dots(double x_min,double x_max, double x_error, double y_error, int ponts);

};


#endif //PARALLEL_REGRESSION_INPUTHANDLER_H
