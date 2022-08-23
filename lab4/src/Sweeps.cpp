#include "../include/Cube.h"

// левое вращение фронтальной части
Cube &Cube::front_left_rotation()
{
    std::array<std::array<char, 3>, 3> temp_left(sides_[left].matrix_);
    for (size_t i = 0; i < 3; ++i) { sides_[left].matrix_[2 - i][2] = sides_[top].matrix_[2][i]; }
    for (size_t i = 0; i < 3; ++i) { sides_[top].matrix_[2][i] = sides_[right].matrix_[i][0]; }
    for (size_t i = 0; i < 3; ++i) { sides_[right].matrix_[i][0] = sides_[bottom].matrix_[0][2 - i]; }
    for (size_t i = 0; i < 3; ++i) { sides_[bottom].matrix_[0][2 - i] = temp_left[2 - i][2]; }
    sides_[front].left_rotate();
    return *this;
}

// правое вращение фронтальной части
Cube &Cube::front_right_rotation()
{
    std::array<std::array<char, 3>, 3> temp_right(sides_[right].matrix_);
    for (size_t i = 0; i < 3; ++i) { sides_[right].matrix_[i][0] = sides_[top].matrix_[2][i]; }
    for (size_t i = 0; i < 3; ++i) { sides_[top].matrix_[2][i] = sides_[left].matrix_[2 - i][2]; }
    for (size_t i = 0; i < 3; ++i) { sides_[left].matrix_[2 - i][2] = sides_[bottom].matrix_[0][2 - i]; }
    for (size_t i = 0; i < 3; ++i) { sides_[bottom].matrix_[0][2 - i] = temp_right[i][0]; }
    sides_[front].right_rotate();
    return *this;
}


Cube &Cube::top_to_front()
{
    std::swap(sides_[bottom].matrix_, sides_[back].matrix_);
    std::swap(sides_[front].matrix_, sides_[bottom].matrix_);
    std::swap(sides_[top].matrix_, sides_[front].matrix_);
    sides_[left].right_rotate();
    sides_[right].left_rotate();
    return *this;
}

//
Cube &Cube::bottom_to_front()
{
    std::swap(sides_[top].matrix_, sides_[front].matrix_);
    std::swap(sides_[front].matrix_, sides_[bottom].matrix_);
    std::swap(sides_[bottom].matrix_, sides_[back].matrix_);
    sides_[left].left_rotate();
    sides_[right].right_rotate();
    return *this;
}

//
Cube &Cube::left_to_front()
{
    std::swap(sides_[front].matrix_, sides_[right].matrix_);
    std::swap(sides_[left].matrix_, sides_[front].matrix_);
    sides_[left].left_rotate();
    sides_[left].left_rotate();
    sides_[back].left_rotate();
    sides_[back].left_rotate();
    std::swap(sides_[left].matrix_, sides_[back].matrix_);
    sides_[top].left_rotate();
    sides_[bottom].right_rotate();
    return *this;
}

//
Cube &Cube::right_to_front()
{
    return this->left_to_front().left_to_front().left_to_front();
}

//
Cube &Cube::back_to_front()
{
    return this->bottom_to_front().bottom_to_front();
}

void Cube::sweep(const std::string& s)
{
    if (is_solving)
    {
        moves_counter++;
        moves_to_win.append(s);
        if (moves_counter > 800){
            std::cout << "\nincorrect state of the cube";
            exit(0);
        }
        Sleep(100);
        draw();
        glutPostRedisplay();
    } else
    {
        std::cout << s;
    }
}

// ========================= front
Cube &Cube::f()
{
    sweep("F ");
    return front_right_rotation();
}

Cube &Cube::f_()
{
    sweep("F' ");
    return front_left_rotation();
}


Cube &Cube::f2()
{
    sweep("F2 ");
    return front_left_rotation().front_left_rotation();
}


// ========================= right
Cube &Cube::r()
{
    sweep("R ");
    return right_to_front().front_right_rotation().left_to_front();
}

Cube &Cube::r_()
{
    sweep("R' ");
    return right_to_front().front_left_rotation().left_to_front();
}

Cube &Cube::r2()
{
    sweep("R2 ");
    return right_to_front().front_left_rotation().front_left_rotation().left_to_front();
}


// ========================= left
Cube &Cube::l()
{
    sweep("L ");
    return left_to_front().front_right_rotation().right_to_front();
}

Cube &Cube::l_()
{
    sweep("L' ");
    return left_to_front().front_left_rotation().right_to_front();
}

Cube &Cube::l2()
{
    sweep("L2 ");
    return left_to_front().front_left_rotation().front_left_rotation().right_to_front();
}


// ========================= top
Cube &Cube::u()
{
    sweep("U ");
    return top_to_front().front_right_rotation().bottom_to_front();
}

Cube &Cube::u_()
{
    sweep("U' ");
    return top_to_front().front_left_rotation().bottom_to_front();
}

Cube &Cube::u2()
{
    sweep("U2 ");
    return top_to_front().front_left_rotation().front_left_rotation().bottom_to_front();
}


// ========================= bottom
Cube &Cube::d()
{
    sweep("D ");
    return bottom_to_front().front_right_rotation().top_to_front();
}

Cube &Cube::d_()
{
    sweep("D' ");
    return bottom_to_front().front_left_rotation().top_to_front();
}

Cube &Cube::d2()
{
    sweep("D2 ");
    return bottom_to_front().front_left_rotation().front_left_rotation().top_to_front();
// r r l u u f b b r l l u u f r l l u u b
}

// ========================= back
Cube &Cube::b()
{
    sweep("B ");
    return back_to_front().front_right_rotation().back_to_front();
}

Cube &Cube::b_()
{
    sweep("B' ");
    return back_to_front().front_left_rotation().back_to_front();
}

Cube &Cube::b2()
{
    sweep("B2 ");
    return back_to_front().front_left_rotation().front_left_rotation().back_to_front();
}

Cube &Cube::x(){
    sweep("x ");
    return bottom_to_front();
}

Cube &Cube::y(){
    sweep("y ");
    return right_to_front();
}

Cube &Cube::z(){
    sweep("z ");
    return right_to_front().top_to_front().left_to_front();
}

Cube &Cube::x_(){
    sweep("x' ");
    return top_to_front();
}

Cube &Cube::y_(){
    sweep("y' ");
    return left_to_front();
}

Cube &Cube::z_(){
    sweep("z' ");
    return right_to_front().bottom_to_front().left_to_front();
}

Cube &Cube::x2(){
    sweep("x2 ");
    return top_to_front().top_to_front();
}

Cube &Cube::y2(){
    sweep("y2 ");
    return left_to_front().left_to_front();
}

Cube &Cube::z2(){
    sweep("z2 ");
    return right_to_front().bottom_to_front().bottom_to_front().left_to_front();
}

void Cube::get_function(const std::string &s)
{
    if (s == "F") { f(); }
    else if (s == "F'") { f_(); }
    else if (s == "F2") { f2(); }

    else if (s == "B") { b(); }
    else if (s == "B'") { b_(); }
    else if (s == "B2") { b2(); }

    else if (s == "R") { r(); }
    else if (s == "R'") { r_(); }
    else if (s == "R2") { r2(); }

    else if (s == "L") { l(); }
    else if (s == "L'") { l_(); }
    else if (s == "L2") { l2(); }

    else if (s == "U") { u(); }
    else if (s == "U'") { u_(); }
    else if (s == "U2") { u2(); }

    else if (s == "D") { d(); }
    else if (s == "D'") { d_(); }
    else if (s == "D2") { d2(); }
// =============   orientations
    else if (s == "x") { x(); }
    else if (s == "x'") { x_(); }
    else if (s == "x2") { x2(); }

    else if (s == "y") { y(); }
    else if (s == "y'") { y_(); }
    else if (s == "y2") { y2(); }

    else if (s == "z") { z(); }
    else if (s == "z'") { z_(); }
    else if (s == "z2") { z2(); }
}

std::string Cube::get_moves_to_win()
{
    std::string r(moves_to_win);
    moves_to_win = "";
    return r;
}









