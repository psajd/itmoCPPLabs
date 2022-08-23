//
// Created by днс on 19.02.2022.
//

#include "Regular_polygon.h"

Regular_polygon::~Regular_polygon() = default;

Regular_polygon::Regular_polygon(const std::vector<Point> &points) : Polygon(points) {
    if (!check_regular_polygon(*this)) {
        throw std::logic_error("Regular polygon: Not regular polygon");
    }
}

Regular_polygon::Regular_polygon(Regular_polygon const &regularPolygon) :
        Regular_polygon(regularPolygon.points_) {}

inline double Regular_polygon::get_area() const {
    return (((double) size_ * get_line_length(points_[0], points_[1])
             * get_line_length(points_[0], points_[1]))
            / (4 * tan(PI / (double) size_)));
}

/*      eto pizdec =(
bool check_regular_polygon(Regular_polygon const &regularPolygon) {
    if (regularPolygon.get_area() - regularPolygon.Polygon::get_area() < EPS) {
        return true;
    }
    return false;
}
*/

bool check_regular_polygon(Regular_polygon const &regularPolygon) {
    for (size_t i = 0; i < regularPolygon.size_ - 2; ++i) {
        if (get_line_length(regularPolygon.points_[i], regularPolygon.points_[i + 1]) -
            get_line_length(regularPolygon.points_[i + 1], regularPolygon.points_[i + 2]) >= EPS) {
            return false;
        }
    }
    if (get_line_length(regularPolygon.points_[0], regularPolygon.points_[1]) -
        get_line_length(regularPolygon.points_[regularPolygon.size_ - 1],
                        regularPolygon.points_[regularPolygon.size_ - 2]) >= EPS) {
        return false;
    }
    if (regularPolygon.get_area() - regularPolygon.Polygon::get_area() < EPS) {
        return true;
    }
    

}

Regular_polygon &Regular_polygon::operator=(const Regular_polygon &regularPolygon) {
    if (&regularPolygon != this) {
        Regular_polygon(regularPolygon).swap(*this);
    }
    return *this;
}
