#ifndef LAB4_SOLVER_H
#define LAB4_SOLVER_H
#include "Cube.h"

class Solver
{
private:
    Cube &cube_;
public:
    explicit Solver(Cube &cube);

    virtual std::string solve() = 0;

    void check_statement();
};

#endif //LAB4_SOLVER_H
