//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_POINT_H
#define POLYNOMIAL_H_POINT_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "cmath"


static const double EPS = 0.00001;
static const double PI = 3.14159265;

class Point {
private:
    double x_;
    double y_;
public:
    explicit Point(double x = 0, double y = 0);

    Point(Point const &p);

    void swap(Point &p);

    Point &operator=(Point const &p);

    double &get_x();

    double &get_y();


    [[nodiscard]] double get_x() const;

    [[nodiscard]] double get_y() const;
};

std::istream &operator>>(std::istream &is, Point &p);

std::ostream &operator<<(std::ostream &os, Point const &p);


#endif //POLYNOMIAL_H_POINT_H
