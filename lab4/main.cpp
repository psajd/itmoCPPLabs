
#include <fstream>
#include "include/Cube.h"
#include "include/HumanSolver.h"

const static char *USAGE_MESSAGE = " ================ Rubik's Cube usage =============== \n"
                                   "Rotate the cube using the keyboard. Keys: \n"
                                   "z - right(R)\n"
                                   "x - left(L)\n"
                                   "c - up(U)\n"
                                   "v - down(D)\n"
                                   "b - back(B)\n"
                                   "n - front(F)\n"
                                   "left mouse button - F'\n"
                                   "right mouse button - F\n"
                                   "WASD - cube rotation  \n"
                                   "'1' - shuffle \n"
                                   "'2' - checking the correct state of the cube\n"
                                   "'3' - execute your shuffle \n"
                                   "'4' - collect cube\n\n"
                                   "For input cube from file, enter 6 3x3 matrices in this order: \n"
                                   "top-left-front-right-bottom-back\n\n";

static const int windowWidth = 600,
        windowHeight = 610;


Cube cube("");

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cube");
    glClearColor(0.9, 1, 1, 0.0);
    glShadeModel(GL_FLAT);
}

void display()
{
    cube.draw();
    //std::cout << std::endl << std::endl<< "=========================="<< std::endl << std::endl;
    //std::cout << cube;

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void right_spin()
{
    cube.f();
    glutIdleFunc(nullptr);
    glutPostRedisplay();
}

void left_spin()
{
    cube.f_();
    glutIdleFunc(nullptr);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(left_spin);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(right_spin);
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
        {
            cube.x_();
            glutPostRedisplay();
            break;
        }
        case 'w':
        {
            cube.x();
            glutPostRedisplay();
            break;
        }
        case 'a':
        {
            cube.y();
            glutPostRedisplay();
            break;
        }
        case 'd':
        {
            cube.y_();
            glutPostRedisplay();
            break;
        }
        case 'z':
        {
            cube.r();
            glutPostRedisplay();
            break;
        }
        case 'x':
        {
            cube.l();
            glutPostRedisplay();
            break;
        }
        case 'c':
        {
            cube.u();
            glutPostRedisplay();
            break;
        }
        case 'v':
        {
            cube.d();
            glutPostRedisplay();
            break;
        }
        case 'b':
        {
            cube.b();
            glutPostRedisplay();
            break;
        }
        case 'n':
        {
            cube.f();
            glutPostRedisplay();
            break;
        }
        case '1':
        {
            cube.shuffle();
            glutPostRedisplay();
            break;
        }
        case '2':{
            HumanSolver checker(cube);
            checker.check_statement();
            glutPostRedisplay();
            break;
        }
        case '3':
        {
            std::string s;
            getline(std::cin, s);
            cube.execute(s, true);
            s.clear();
            glutPostRedisplay();
            break;
        }
        case '4':
        {
            HumanSolver solver(cube);
            std::string moves = solver.solve();
            std::cout << moves;
            glutPostRedisplay();
            break;
        }
    }
}


int main(int argc, char **argv)
{

    std::ifstream a("cube.in");
    std::cout << USAGE_MESSAGE;
    //a >> cube;
    init(argc, argv);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(nullptr);
    glutMainLoop();

    return 0;
}


