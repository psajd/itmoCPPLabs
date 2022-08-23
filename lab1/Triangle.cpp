#include "Triangle.h"

Triangle::Triangle(const std::vector<Point> &points) : Closed_Polyline(points) {
    if (points_.size() != 3) {
        throw std::logic_error("Triangle: Wrong value of points");
    }
    double a = get_line_length(points[0], points_[1]);
    double b = get_line_length(points[1], points_[2]);
    double c = get_line_length(points[0], points_[2]);
    if (!(a + b > c and a + c > b and c + b > a)) {
        throw std::logic_error("Triangle: Not a triangle");
    }
}

Triangle::Triangle(Point const &p1, Point const &p2, Point const &p3) : Triangle(std::vector<Point>{p1, p2, p3}) {}

Triangle::Triangle(const Triangle &triangle) : Triangle(points_) {}

Triangle &Triangle::operator=(const Triangle &triangle) {
    if (this != &triangle) {
        Triangle(triangle).swap(*this);
    }
    return *this;
}

Triangle::~Triangle() = default;

inline double Triangle::get_area() const {
    return fabs((points_[1].get_x() - points_[0].get_x()) * (points_[2].get_y() - points_[0].get_y()) -
                (points_[1].get_y() - points_[0].get_y()) * points_[2].get_x() - points_[0].get_x()) / 2.0;
}
