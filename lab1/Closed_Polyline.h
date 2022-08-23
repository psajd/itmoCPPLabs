//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_CLOSED_POLYLINE_H
#define POLYNOMIAL_H_CLOSED_POLYLINE_H
#include "Polyline.h"

class Closed_Polyline : public Polyline {
public:

    explicit Closed_Polyline(size_t size = 0);

    explicit Closed_Polyline(std::vector<Point> const &points);

    Closed_Polyline(Closed_Polyline const &closedPolyline);

    Closed_Polyline &operator=(Closed_Polyline const &closedPolyline);

    ~Closed_Polyline() override;

    [[nodiscard]] double get_perimeter() const override;

    [[nodiscard]] virtual inline double get_area() const;


};


#endif //POLYNOMIAL_H_CLOSED_POLYLINE_H
