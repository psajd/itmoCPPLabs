
#include "Polygon.h"


Polygon::~Polygon() = default;

Polygon::Polygon(std::vector<Point> const &points) : Closed_Polyline(points) {
    if (points.size() < 3) {
        throw std::logic_error("Polygon: Not a polygon");
    } else if (check_self_intersection(points)) {
        throw std::logic_error("Polygon: Polygon have intersects");
    }
}

Polygon::Polygon(Polygon const &polygon) : Closed_Polyline(polygon.points_) {}


Polygon &Polygon::operator=(const Polygon &polygon) {
    if (this != &polygon) {
        Polygon(polygon).swap(*this);
    }
    return *this;
}

double Polygon::get_area() const {
    double area = 0;
    for (size_t i = 0; i < size_; ++i) {
        Point p1 = i ? points_[i - 1] : points_.back(),
                p2 = points_[i];
        area += (p1.get_x() - p2.get_x()) * (p1.get_y() + p2.get_y());
    }
    return fabs(area) / 2;
}
