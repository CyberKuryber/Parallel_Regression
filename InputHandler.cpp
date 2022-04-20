//
// Created by uros on 20/04/22.
//

#include "InputHandler.h"

void InputHandler::parse_input() {
    std::ifstream infile(INPUT_FILE);
    std::string s ;
    infile>>s;
    std::string delimiter = "|";
    this->a =std::stod(s.substr(0, s.find(delimiter)));
    this->b =std::stod(s.substr(1, s.find(delimiter)));
}

std::vector<Point> InputHandler::generate_dots(double x_min, double x_max, double x_error, double y_error, int ponts) {
    return nullptr;
}