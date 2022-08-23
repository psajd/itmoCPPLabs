#ifndef LAB4_CUBE_H
#define LAB4_CUBE_H

#include "vector"
#include "string"
#include "array"
#include "iostream"
#include "GL/glut.h"
#include <random>
#include <iostream>
#include <sstream>

enum s
{
    top = 0,
    left = 1,
    front = 2,
    right = 3,
    bottom = 4,
    back = 5
};

enum color
{
    white = 'w',
    yellow = 'y',
    blue = 'b',
    green = 'g',
    red = 'r',
    orange = 'o'
};


std::vector<std::string> split(const std::string &s, char delim);

void set_color(char c);

inline std::mt19937 &generator();

int my_rand(int min, int max);

class Cube
{
private:

    std::string moves_to_win;
    int moves_counter = 0;
    bool is_solving = false;

    class Side
    {
    private:
        friend Cube;
        std::string name_;
        std::array<std::array<char, 3>, 3> matrix_;

        void left_rotate();

        void right_rotate();

    public:

        friend std::istream &operator>>(std::istream &is, Cube &cube);

        friend std::ostream &operator<<(std::ostream &is, Cube &cube);

        Side();

        Side(const Side &side);

        Side(char color, std::string name);

        Side &operator=(Side const &side);

        bool check_side_equality(char c);

        char get_color(size_t i, size_t j);

        void print(std::ostream &os = std::cout);

        void print_with_t(std::ostream &os = std::cout);

        void draw(double x, double y);

    };

    void sweep(const std::string& s);

    Cube &front_left_rotation();

    void get_function(const std::string &s);

    Cube &front_right_rotation();

    void print_front_side(std::ostream &os = std::cout);

    Cube &top_to_front();

    Cube &right_to_front();

    Cube &left_to_front();

    Cube &bottom_to_front();

    Cube &back_to_front();

public:

    void set_solving_flag(bool f);

    std::string get_moves_to_win();

    explicit Cube(const std::string& s);

    void execute(const std::vector<std::string> &cmds, bool is_draw = false);

    void execute(const std::string &cmd, bool is_draw = false);

    void print_cube(std::ostream &os = std::cout);

    std::array<Side, 6> sides_;

    Cube();

    void swap(Cube &cube);

    Cube(const Cube &cube);

    Cube &operator=(const Cube &cube);

    void draw();

    void shuffle();

    Cube &r();

    Cube &r_();

    Cube &r2();

    Cube &l();

    Cube &l_();

    Cube &l2();

    Cube &u();

    Cube &u_();

    Cube &u2();

    Cube &d();

    Cube &d_();

    Cube &d2();

    Cube &f();

    Cube &f_();

    Cube &f2();

    Cube &b();

    Cube &b_();

    Cube &b2();

    Cube &x();

    Cube &y();

    Cube &z();

    Cube &x_();

    Cube &y_();

    Cube &z_();

    Cube &x2();

    Cube &y2();

    Cube &z2();
};

std::istream &operator>>(std::istream &is, Cube &cube);

std::ostream &operator<<(std::ostream &is, Cube &cube);

#endif //LAB4_CUBE_H
