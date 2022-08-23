//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_TRAPEZE_H
#define POLYNOMIAL_H_TRAPEZE_H
#include "Polygon.h"



class Trapeze : public Polygon {
public:
    explicit Trapeze(std::vector<Point> const &points);

    Trapeze(Point const &p1, Point const &p2, Point const &p3, Point const &p4);

    Trapeze(Trapeze const &trapeze);

    Trapeze &operator=(Trapeze const &trapeze);

    ~Trapeze() override;

};


#endif //POLYNOMIAL_H_TRAPEZE_H
