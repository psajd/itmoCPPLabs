//
// Created by днс on 19.02.2022.
//

#ifndef POLYNOMIAL_H_POLYLINE_H
#define POLYNOMIAL_H_POLYLINE_H
#include "Point.h"

class Polyline {
protected:
    std::vector<Point> points_;
    size_t size_;

public:

    explicit Polyline(size_t size = 0);

    explicit Polyline(std::vector<Point> const &points);

    Polyline(Polyline const &line);

    Polyline &operator=(Polyline const &line);

    virtual ~Polyline();

    void swap(Polyline &line);

    [[nodiscard]] virtual double get_perimeter() const;

};


inline bool intersect(double a, double b, double c, double d);

inline double area(Point const &p1, Point const &p2, Point const &p3);

double get_line_length(Point const &p1, Point const &p2);

bool check_lines_intersection(Point const &p1, Point const &p2, Point const &p3, Point const &p4);

bool check_self_intersection(std::vector<Point> const &point);


#endif //POLYNOMIAL_H_POLYLINE_H
