#include "../include/Cube.h"

void Cube::execute(const std::vector<std::string> &cmds, bool is_draw)
{
    for (auto &cmd: cmds)
    {
        if (is_draw){
            Sleep(100);
            draw();
        }
        get_function(cmd);
    }
}


void Cube::execute(const std::string &cmd, bool is_draw)
{
    execute(split(cmd, ' '), is_draw);
}


Cube::Cube()
{
    sides_[top] = Side(white, "top");
    sides_[bottom] = Side(yellow, "bottom");
    sides_[front] = Side(green, "front");
    sides_[back] = Side(blue, "back");
    sides_[left] = Side(orange, "left");
    sides_[right] = Side(red, "right");
}

Cube::Cube(const std::string& s)
{
    sides_[top] = Side(white, "top");
    sides_[bottom] = Side(yellow, "bottom");
    sides_[front] = Side(green, "front");
    sides_[back] = Side(blue, "back");
    sides_[left] = Side(orange, "left");
    sides_[right] = Side(red, "right");
    execute(s);
}

Cube::Cube(const Cube &cube)
{
    for (auto x : {top, bottom, front, back, left, right}){
        sides_[x] = Side(cube.sides_[x]);
    }
}

Cube &Cube::operator=(const Cube &cube)
{
    if (&cube != this)
    {
        Cube(cube).swap(*this);
    }
    return *this;
}

void Cube::print_cube(std::ostream &os)
{
    for (auto &s: sides_)
    {
        os << s.name_ << '\n';
        s.print(os);
        os << "\n\n";
    }
}

void Cube::print_front_side(std::ostream &os)
{
    sides_[front].print(os);
}

Cube::Side::Side()
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        matrix_[i].fill(0);
    }
}

Cube::Side::Side(char color, std::string name) : name_(std::move(name))
{

    for (std::size_t i = 0; i < 3; ++i)
    {
        matrix_[i].fill(color);
    }
}

Cube::Side &Cube::Side::operator=(const Cube::Side &side)
{
    if (&side != this)
    {
        for (std::size_t i = 0; i < 3; ++i)
        {
            matrix_[i].fill(side.matrix_[i][i]);
        }
    }
    return *this;
}

void Cube::Side::print(std::ostream &os)
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            os << matrix_[i][j] << ' ';
        }
        if (i != 2)
        {
            os << "\n";
        }
    }
}

void Cube::Side::print_with_t(std::ostream &os)
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        os << "\t  ";
        for (std::size_t j = 0; j < 3; ++j)
        {
            os << matrix_[i][j] << ' ';
        }
        if (i != 2)
        {
            os << "\n";
        }
    }
}

void Cube::Side::left_rotate()
{
    std::array<std::array<char, 3>, 3> temp(matrix_);
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            matrix_[i][j] = temp[j][2 - i];
        }
    }
}

void Cube::Side::right_rotate()
{
    std::array<std::array<char, 3>, 3> temp(matrix_);
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            matrix_[i][j] = temp[2 - j][i];
        }
    }
}

void Cube::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    sides_[top].draw(225, 5);
    sides_[front].draw(225, 155);
    sides_[right].draw(375, 155);
    sides_[left].draw(75, 155);
    sides_[bottom].draw(225, 305);
    sides_[back].draw(225, 455);
    glPopMatrix();
    glutSwapBuffers();
}

void set_color(char c)
{
    if (c == white)glColor3f(1, 1, 1);
    else if (c == yellow) glColor3f(1, 1, 0);
    else if (c == blue) glColor3f(0, 0, 1);
    else if (c == green) glColor3f(0, 1, 0);
    else if (c == red) glColor3f(0.9, 0, 0);
    else if (c == orange) glColor3f(1, 0.6, 0);
}

void Cube::Side::draw(double x, double y)
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            double x_ = x + j * 50, y_ = y + i * 50;
            glColor3f(0, 0, 0);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
            glVertex2d(x_, y_);
            glVertex2d(x_, y_ + 50);
            glVertex2d(x_ + 50, y_ + 50);
            glVertex2d(x_ + 50, y_);
            glEnd();
            set_color(matrix_[i][j]);
            glRectd(x_, y_, x_ + 50, y_ + 50);
        }
    }
}

std::mt19937 &generator()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

int my_rand(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator());
}

void Cube::shuffle()
{
    std::size_t value_of_sweeps = my_rand(10, 15);
    std::size_t value_of_rotations;
    for (std::size_t i = 0; i < value_of_sweeps; ++i)
    {
        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { r(); }
        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { l(); }

        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { u(); }
        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { d(); }

        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { f(); }
        value_of_rotations = my_rand(0, 2);
        for (std::size_t j = 0; j < value_of_rotations; ++j) { b(); }

    }
}

std::istream &operator>>(std::istream &is, Cube &cube)
{
    for (std::size_t i = 0; i < 6; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            for (std::size_t k = 0; k < 3; ++k)
            {
                is >> cube.sides_[i].matrix_[j][k];
            }
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, Cube &cube)
{
    cube.sides_[top].print_with_t(os);
    os << "\n";
    for (std::size_t i = 0; i < 3; ++i)
    {
        os << "    ";
        for (auto &side: std::vector<s>{left, front, right})
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                os << cube.sides_[side].matrix_[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
    cube.sides_[bottom].print_with_t(os);
    os << '\n';
    cube.sides_[back].print_with_t(os);
    os << "\n" << '\n';
    return os;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

Cube::Side::Side(const Cube::Side &side)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            matrix_[i][j] = side.matrix_[i][j];
        }
    }
    name_ = side.name_;
}

char Cube::Side::get_color(size_t i, size_t j)
{
    return matrix_[i][j];
}

bool Cube::Side::check_side_equality(char c)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (matrix_[i][j] != c){
                return false;
            }
        }
    }
    return true;
}

void Cube::swap(Cube &cube)
{
    for (auto x : {top, bottom, front, back, left, right}){
        std::swap(sides_[x], (cube.sides_[x]));
    }
}


void Cube::set_solving_flag(bool f)
{
    moves_counter = 0;
    is_solving = f;
}


