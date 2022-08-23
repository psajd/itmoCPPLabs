//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_REGULAR_POLYGON_H
#define POLYNOMIAL_H_REGULAR_POLYGON_H
#include "Polygon.h"

class Regular_polygon : public Polygon {
public:
    explicit Regular_polygon(std::vector<Point> const &points);

    Regular_polygon(Regular_polygon const &regularPolygon);

    Regular_polygon &operator=(Regular_polygon const &regularPolygon);

    ~Regular_polygon() override;

    friend bool check_regular_polygon(Regular_polygon const &regularPolygon);

    [[nodiscard]] double get_area() const override;
};


#endif //POLYNOMIAL_H_REGULAR_POLYGON_H
