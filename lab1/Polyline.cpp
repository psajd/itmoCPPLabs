#include "Polyline.h"

inline double get_line_length(Point const &p1, Point const &p2) {
    return sqrt(((p2.get_x()) - p1.get_x()) * ((p2.get_x()) - p1.get_x()) +
                ((p2.get_y()) - p1.get_y()) * ((p2.get_y()) - p1.get_y()));
}


double area(Point const &p1, Point const &p2, Point const &p3) {
    return (p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y()) -
           (p2.get_y() - p1.get_y()) * (p3.get_x() - p1.get_x());
}

bool intersect(double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool check_lines_intersection(Point const &p1, Point const &p2, Point const &p3, Point const &p4) {
    return intersect(p1.get_x(), p2.get_x(), p3.get_x(), p4.get_x()) and
           intersect(p1.get_y(), p2.get_y(), p3.get_y(), p4.get_y()) and
           area(p1, p2, p3) * area(p1, p2, p4) <= EPS and area(p3, p4, p1) * area(p3, p4, p2) <= EPS;
}

bool check_self_intersection(std::vector<Point> const &points) {
    if (points.size() == 3) return false;
    for (size_t i = 0; i < points.size() - 2; ++i) {
        for (size_t j = 2 + i; j < points.size() - 2; ++j) {
            if (check_lines_intersection(points[i], points[i + 1], points[j], points[j + 1])) {
                return true;
            }
        }
    }
    return false;
}

Polyline::~Polyline() = default;


Polyline::Polyline(size_t size) {
    size_ = size;
    points_.resize(size);
}

Polyline::Polyline(std::vector<Point> const &points) {
    size_ = points.size();
    points_.resize(size_);
    for (size_t i = 0; i < size_; ++i) {
        points_[i] = points[i];
    }
}

Polyline::Polyline(Polyline const &line) : Polyline(line.points_) {}

void Polyline::swap(Polyline &line) {
    std::swap(points_, line.points_);
    std::swap(size_, line.size_);
}

Polyline &Polyline::operator=(const Polyline &line) {
    if (this != &line) {
        Polyline(line).swap(*this);
    }
    return *this;
}

double Polyline::get_perimeter() const {
    double perimeter = 0;
    for (size_t i = 0; i < size_ - 1; ++i) {
        perimeter += get_line_length(points_[i], points_[i + 1]);
    }
    return perimeter;
}

