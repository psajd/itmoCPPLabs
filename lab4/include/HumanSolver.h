#ifndef LAB4_HUMANSOLVER_H
#define LAB4_HUMANSOLVER_H

#include "Cube.h"
#include "algorithm"
#include "windows.h"
#include "set"
#include "Solver.h"

class HumanSolver : public Solver
{
private:

    Cube &cube_;

    void pif_paf();

    void left_pif_paf();

    void left_edge_swap();

    bool check_second_layer();

    bool check_upper_edges();

    bool check_lower_corners();

    void right_edge_swap();

    void create_correct_upper_corners();

    void lower_cross();

    void right_lower_cross();

    void first_layer();

    void second_layer();

    void upper_cross();

    void right_corners();

    void top_side();

    void final_boss();

public:

    std::string solve() override;

    explicit HumanSolver(Cube &cube);
};


#endif //LAB4_HUMANSOLVER_H
