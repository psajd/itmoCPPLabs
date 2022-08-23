#include "Point.h"

Point::Point(double x, double y) {
    x_ = x;
    y_ = y;
}

Point::Point(Point const &p) : Point(p.x_, p.y_) {}

void Point::swap(Point &p) {
    std::swap(x_, p.x_);
    std::swap(y_, p.y_);
}

Point &Point::operator=(Point const &p) {
    if (this != &p) {
        Point(p).swap(*this);
    }
    return *this;
}

double &Point::get_x() { return x_; }

double &Point::get_y() { return y_; }

double Point::get_x() const { return x_; }

double Point::get_y() const { return y_; }


std::istream &operator>>(std::istream &is, Point &p) {
    is >> p.get_x() >> p.get_y();
    return is;
}

std::ostream &operator<<(std::ostream &out, Point const &p) {
    out << "(" << p.get_y() << ", " << p.get_y() << ")";
    return out;
}