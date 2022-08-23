#include "Closed_Polyline.h"

Closed_Polyline::Closed_Polyline(size_t size) : Polyline(size) {}

Closed_Polyline::Closed_Polyline(std::vector<Point> const &points) : Polyline(points) {}

Closed_Polyline::Closed_Polyline(Closed_Polyline const &closedPolyline) : Closed_Polyline(closedPolyline.points_) {}

Closed_Polyline &Closed_Polyline::operator=(const Closed_Polyline &closedPolyline) {
    if (this != &closedPolyline) {
        Closed_Polyline(closedPolyline).swap(*this);
    }
    return *this;
}

Closed_Polyline::~Closed_Polyline() = default;

double Closed_Polyline::get_perimeter() const {
    double perimeter = 0;
    for (size_t i = 0; i < size_ - 1; ++i) {
        perimeter += get_line_length(points_[i], points_[i + 1]);
    }
    perimeter += get_line_length(points_[0], points_[size_ - 1]);
    Polyline t;
    return perimeter;
}


double Closed_Polyline::get_area() const { return 0; }
