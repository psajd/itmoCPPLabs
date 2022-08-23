#include <iostream>
#include <algorithm>
#include "Trapeze.h"
#include "Polynomial.h"

int main() {
    Point p1, p2, p3, p4;
    std::cin >> p1 >> p2 >> p3 >> p4;
    std::vector<Point> pts = {p1, p2, p3, p4};
    Trapeze trapeze;
    try{
        trapeze = Trapeze(pts);
        std::cout << trapeze.get_area() << std::endl << trapeze.get_perimeter();
    }
    catch (std::exception &ex){
        std::cerr << ex.what();
    }



    Polynomial<int> a(std::vector<int> {0, 1, -1});
    Polynomial<int> b(std::vector<int> {0, 1});
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << "-a = " << -a << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / 2 = " << a / 2 << std::endl;
}
