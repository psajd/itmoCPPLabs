//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_POLYGON_H
#define POLYNOMIAL_H_POLYGON_H
#include "Closed_Polyline.h"

class Polygon : public Closed_Polyline {
public:

    explicit Polygon(std::vector<Point> const &points);

    Polygon(Polygon const &polygon);

    Polygon &operator=(Polygon const &polygon);

    ~Polygon() override;

    [[nodiscard]] double get_area() const override;

};
#endif //POLYNOMIAL_H_POLYGON_H
