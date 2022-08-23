//
// Created by днс on 19.02.2022.
//

#include "Trapeze.h"


bool isParallel(Point const &p1, Point const &p2, Point const &p3, Point const &p4) {
    double x1 = p2.get_x() - p1.get_x();
    double y1 = p2.get_y() - p1.get_y();
    double x2 = p4.get_x() - p3.get_x();
    double y2 = p4.get_y() - p3.get_y();
    return fabs(x1 * y2 - x2 * y1) < EPS;
}

Trapeze::Trapeze(std::vector<Point> const &pts) : Polygon(pts) {
    if (points_.size() != 4) {
        throw std::logic_error("Trapeze: Wrong value of points");
    }
    if (!isParallel(points_[0], points_[1], points_[2], points_[3]) and
        !isParallel(points_[1], points_[2], points_[0], points_[3])) {
        throw std::logic_error("Trapeze: Not a trapeze");
    }
}

Trapeze::Trapeze(const Point &p1, const Point &p2, const Point &p3, const Point &p4) : Trapeze(
        std::vector<Point>{p1, p2, p3, p4}) {}

Trapeze::Trapeze(Trapeze const &trapeze) : Trapeze(trapeze.points_) {}

Trapeze &Trapeze::operator=(Trapeze const &trapeze) {
    if (&trapeze != this) {
        Trapeze(trapeze).swap(*this);
    }
    return *this;
}

Trapeze::~Trapeze() = default;
