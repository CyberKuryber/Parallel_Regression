//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_POINT_H
#define PARALLEL_REGRESSION_POINT_H


class Point {
private:
    double x;
    double y;
public:
    double get_x() const;
    double set_x(double x);
    double get_y() const;
    double set_y(double y);
    Point(double x,double y): x(x),y(y) {};
};


#endif //PARALLEL_REGRESSION_POINT_H
