#include "../include/Solver.h"

Solver::Solver(Cube &cube) : cube_(cube) {}

void Solver::check_statement()
{
    solve();
    std::cout << "perfect cube";
    exit(1);
}
