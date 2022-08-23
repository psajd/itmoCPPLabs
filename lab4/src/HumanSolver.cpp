#include "../include/HumanSolver.h"


HumanSolver::HumanSolver(Cube &cube) : Solver(cube), cube_(cube) {}

std::string HumanSolver::solve()
{
    cube_.set_solving_flag(true);
    lower_cross();
    right_lower_cross();
    first_layer();
    second_layer();
    upper_cross();
    right_corners();
    top_side();
    final_boss();
    cube_.set_solving_flag(false);
    return cube_.get_moves_to_win();
}

void HumanSolver::pif_paf()
{
    cube_.execute(split("R U R' U'", ' '));
}

void HumanSolver::left_pif_paf()
{
    cube_.execute(split("L' U' L U", ' '));
}

void HumanSolver::lower_cross()
{
    auto center = cube_.sides_[front].get_color(1, 1);
    cube_.x2();
    int c = 0;
    while (center != cube_.sides_[front].get_color(1, 2) or center != cube_.sides_[front].get_color(1, 0) or
           center != cube_.sides_[front].get_color(0, 1) or center != cube_.sides_[front].get_color(2, 1))
    {
        c++;
        while (center == cube_.sides_[top].get_color(1, 2) or center == cube_.sides_[bottom].get_color(1, 2) or
               center == cube_.sides_[back].get_color(1, 2))
        {
            while (center == cube_.sides_[front].get_color(1, 2))
            {
                cube_.f();
            }
            while (center != cube_.sides_[front].get_color(1, 2))
            {
                cube_.r();
            }
            cube_.f();
        }
        cube_.z();
        if (c == 4)
        {
            if (center == cube_.sides_[left].get_color(1, 2) or center == cube_.sides_[left].get_color(1, 0))
            {
                cube_.l();
            } else if (center == cube_.sides_[right].get_color(1, 2) or center == cube_.sides_[right].get_color(1, 0))
            {
                cube_.r();
            } else if (center == cube_.sides_[top].get_color(0, 1) or center == cube_.sides_[top].get_color(2, 1))
            {
                cube_.u();
            } else if (center == cube_.sides_[bottom].get_color(0, 1) or center == cube_.sides_[bottom].get_color(2, 1))
            {
                cube_.d();
            }
            c = 0;
        }
    }
    cube_.x2();
}

void HumanSolver::right_lower_cross()
{
    auto center = cube_.sides_[front].get_color(1, 1);
    cube_.x2();
    while (center == cube_.sides_[front].get_color(1, 2) or center == cube_.sides_[front].get_color(1, 0) or
           center == cube_.sides_[front].get_color(0, 1) or center == cube_.sides_[front].get_color(2, 1))
    {
        if (cube_.sides_[top].get_color(1, 1) == cube_.sides_[top].get_color(2, 1) and
            center == cube_.sides_[front].get_color(0, 1))
        {
            cube_.u2();

        } else if (cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(1, 2) and
                   center == cube_.sides_[front].get_color(1, 0))
        {
            cube_.l2();
        } else if (cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(1, 0) and
                   center == cube_.sides_[front].get_color(1, 2))
        {
            cube_.r2();

        } else if (cube_.sides_[bottom].get_color(1, 1) == cube_.sides_[bottom].get_color(0, 1) and
                   center == cube_.sides_[front].get_color(2, 1))
        {
            cube_.d2();
        }
        cube_.f();
    }
    cube_.x2();
}


bool HumanSolver::check_lower_corners()
{
    return cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(2, 0) and
           cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(2, 2) and
           cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(2, 0) and
           cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(2, 2) and
           cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(2, 0) and
           cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(2, 2) and
           cube_.sides_[back].get_color(1, 1) == cube_.sides_[back].get_color(0, 0) and
           cube_.sides_[back].get_color(1, 1) == cube_.sides_[back].get_color(0, 2);
}

void HumanSolver::first_layer()
{
    auto center = cube_.sides_[front].get_color(1, 1);
    cube_.x_();
    while (!check_lower_corners())
    {

        if (cube_.sides_[front].get_color(2, 2) == center or
            cube_.sides_[right].get_color(2, 0) == center or // нижний угол с цветом центра
            cube_.sides_[bottom].get_color(0, 2) == center)
        {
            std::set<char> corner{cube_.sides_[front].get_color(2, 2), cube_.sides_[right].get_color(2, 0),
                                  cube_.sides_[bottom].get_color(0, 2), cube_.sides_[front].get_color(1, 1),
                                  cube_.sides_[right].get_color(1, 1)};

            if (corner.size() == 3) // угол на своём месте
            {
                while (cube_.sides_[front].get_color(1, 1) != cube_.sides_[front].get_color(2, 2) and
                       cube_.sides_[right].get_color(1, 1) != cube_.sides_[right].get_color(2, 0))
                {
                    pif_paf();
                }
            } else // не на своём месте
            {
                pif_paf();
            }
        } else
        {
            for (int i = 0; i < 4; ++i)
            {
                std::set<char> corner{cube_.sides_[front].get_color(0, 2), cube_.sides_[right].get_color(0, 0),
                                      cube_.sides_[top].get_color(2, 2), cube_.sides_[front].get_color(1, 1),
                                      cube_.sides_[right].get_color(1, 1)};

                if (corner.size() == 3 and
                    (cube_.sides_[front].get_color(0, 2) == center or
                     cube_.sides_[right].get_color(0, 0) == center or
                     cube_.sides_[top].get_color(2, 2) == center))
                {
                    while (cube_.sides_[front].get_color(1, 1) != cube_.sides_[front].get_color(2, 2) or
                           cube_.sides_[right].get_color(1, 1) != cube_.sides_[right].get_color(2, 0))
                    {
                        pif_paf();
                    }

                }
                cube_.u();
            }
        }

        cube_.y_();
    }
    cube_.x();
}

bool HumanSolver::check_second_layer()
{
    return cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(1, 0) and
           cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(1, 2) and
           cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(1, 0) and
           cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(1, 2) and
           cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(1, 0) and
           cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(1, 2) and
           cube_.sides_[back].get_color(1, 1) == cube_.sides_[back].get_color(1, 0) and
           cube_.sides_[back].get_color(1, 1) == cube_.sides_[back].get_color(1, 2);
}

void HumanSolver::right_edge_swap()
{
    pif_paf();
    cube_.y();
    left_pif_paf();
    cube_.y_();
}

void HumanSolver::left_edge_swap()
{
    left_pif_paf();
    cube_.y_();
    pif_paf();
    cube_.y();
}

void HumanSolver::second_layer()
{
    cube_.x_();
    auto center = cube_.sides_[top].get_color(1, 1);

    while (!check_second_layer())
    {
        if (cube_.sides_[front].get_color(1, 1) != cube_.sides_[front].get_color(1, 2) or
            cube_.sides_[right].get_color(1, 1) != cube_.sides_[right].get_color(1, 0) or
            cube_.sides_[front].get_color(1, 1) != cube_.sides_[front].get_color(1, 0) or
            cube_.sides_[left].get_color(1, 1) != cube_.sides_[left].get_color(1, 2))
        {
            for (int i = 0; i < 4; i++)
            {
                if ((cube_.sides_[front].get_color(1, 1) == cube_.sides_[left].get_color(0, 1)
                     and cube_.sides_[right].get_color(1, 1) == cube_.sides_[top].get_color(1, 0)) or
                    ((cube_.sides_[left].get_color(0, 1) == center or
                      cube_.sides_[top].get_color(1, 0) == center) and
                     cube_.sides_[front].get_color(1, 2) != center and
                     cube_.sides_[right].get_color(1, 0) != center and
                     !(cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(1, 2) and
                       cube_.sides_[right].get_color(1, 1) == cube_.sides_[right].get_color(1, 0))))
                {
                    right_edge_swap();
                }

                if ((cube_.sides_[front].get_color(1, 1) == cube_.sides_[right].get_color(0, 1)
                     and cube_.sides_[left].get_color(1, 1) == cube_.sides_[top].get_color(1, 2)) or
                    ((cube_.sides_[right].get_color(0, 1) == center or
                      cube_.sides_[top].get_color(1, 2) == center) and
                     cube_.sides_[front].get_color(1, 0) != center and
                     cube_.sides_[left].get_color(1, 2) != center and
                     !(cube_.sides_[front].get_color(1, 1) == cube_.sides_[front].get_color(1, 0) and
                       cube_.sides_[left].get_color(1, 1) == cube_.sides_[left].get_color(1, 2))))
                {
                    left_edge_swap();
                }
                cube_.u();
            }
        }
        cube_.y_();
    }
    cube_.x();
}

void HumanSolver::upper_cross()
{
    cube_.x_();
    auto center = cube_.sides_[top].get_color(1, 1);

    if (cube_.sides_[top].get_color(1, 2) == center and cube_.sides_[top].get_color(2, 1) == center and
        cube_.sides_[top].get_color(0, 1) == center and cube_.sides_[top].get_color(1, 0) == center)
    {
        cube_.x();
        return;
    } else if (cube_.sides_[top].get_color(1, 0) == center and cube_.sides_[top].get_color(1, 2) == center)
    {
        cube_.f();
        pif_paf();
        cube_.f_();
    } else if (cube_.sides_[top].get_color(0, 1) == center and cube_.sides_[top].get_color(2, 1) == center)
    {
        cube_.u();
        cube_.f();
        pif_paf();
        cube_.f_();
    } else
    {
        for (int i = 0; i < 4; ++i)
        {
            if (cube_.sides_[top].get_color(0, 1) == center and cube_.sides_[top].get_color(1, 0) == center)
            {
                cube_.f();
                pif_paf();
                pif_paf();
                cube_.f_();
                cube_.x();
                return;
            }
            cube_.u();
        }
        cube_.f();
        pif_paf();
        cube_.f_().u2().f();
        pif_paf();
        pif_paf();
        cube_.f_();
    }
    cube_.x();
}


void HumanSolver::right_corners()
{
    cube_.x2();
    int c = 0;
    while (true)
    {
        c++;
        std::set<char> left_lower_corner{cube_.sides_[front].get_color(2, 0), cube_.sides_[left].get_color(2, 2),
                                         cube_.sides_[left].get_color(1, 1),
                                         cube_.sides_[bottom].get_color(1, 1), cube_.sides_[bottom].get_color(0, 0)};
        std::set<char> right_lower_corner{cube_.sides_[front].get_color(2, 2), cube_.sides_[bottom].get_color(1, 1),
                                          cube_.sides_[bottom].get_color(0, 2),
                                          cube_.sides_[right].get_color(1, 1), cube_.sides_[right].get_color(2, 0)};
        std::set<char> right_upper_corner{cube_.sides_[front].get_color(0, 2), cube_.sides_[top].get_color(1, 1),
                                          cube_.sides_[top].get_color(2, 2),
                                          cube_.sides_[right].get_color(1, 1), cube_.sides_[right].get_color(0, 0)};

        if (left_lower_corner.size() == right_lower_corner.size() and
            right_lower_corner.size() == right_upper_corner.size() and right_upper_corner.size() == 3)
        {
            cube_.x2();
            break;
        } else if (right_lower_corner.size() == right_upper_corner.size() and right_upper_corner.size() == 3)
        {
            cube_.z2();
            create_correct_upper_corners();
            cube_.u_();
            cube_.x();
            break;
        } else if (left_lower_corner.size() == right_upper_corner.size() and right_upper_corner.size() == 3)
        {
            create_correct_upper_corners();
            cube_.x_();
            continue;
        }
        if (c == 4)
        {
            cube_.z();
            c = 0;
        }
        cube_.f();
    }
}

void HumanSolver::top_side()
{
    cube_.x();
    auto center = cube_.sides_[bottom].get_color(1, 1);
    for (int i = 0; i < 4; ++i)
    {
        while (cube_.sides_[bottom].get_color(0, 2) != center)
        {
            pif_paf();
        }
        cube_.d_();
    }
    cube_.x_();
}

void HumanSolver::create_correct_upper_corners()
{
    cube_.x();
    pif_paf();
    pif_paf();
    pif_paf();
    cube_.y();
    left_pif_paf();
    left_pif_paf();
    left_pif_paf();
}

void HumanSolver::final_boss()
{
    cube_.x_();
    while (check_upper_edges())
    {
        for (int i = 0; i < 4; ++i)
        {
            if (cube_.sides_[front].check_side_equality(cube_.sides_[front].get_color(1, 1)))
            {
                break;
            }
            cube_.y();
        }

        pif_paf();
        left_pif_paf();
        for (int i = 0; i < 5; ++i) { pif_paf(); }
        for (int i = 0; i < 5; ++i) { left_pif_paf(); }

    }
    cube_.x();
}

bool HumanSolver::check_upper_edges()
{
    return (!cube_.sides_[front].check_side_equality(cube_.sides_[front].get_color(1, 1)) or
            !cube_.sides_[back].check_side_equality(cube_.sides_[back].get_color(1, 1)) or
            !cube_.sides_[left].check_side_equality(cube_.sides_[left].get_color(1, 1)) or
            !cube_.sides_[right].check_side_equality(cube_.sides_[right].get_color(1, 1)));
}


