//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_TRIANGLE_H
#define POLYNOMIAL_H_TRIANGLE_H
#include "Closed_Polyline.h"

class Triangle : public Closed_Polyline {
public:

    explicit Triangle(std::vector<Point> const &points);

    Triangle(Point const &p1, Point const &p2, Point const &p3);

    Triangle(Triangle const &triangle);

    Triangle &operator=(Triangle const &triangle);

    ~Triangle() override;

    [[nodiscard]] double get_area() const override;
};

#endif //POLYNOMIAL_H_TRIANGLE_H
