cmake_minimum_required(VERSION 3.21)
project(lab4)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab4 main.cpp src/Cube.cpp include/Cube.h src/Sweeps.cpp src/HumanSolver.cpp include/HumanSolver.h src/Solver.cpp include/Solver.h)

target_link_libraries(lab4 ${OPENGL_LIBRARIES})
target_link_libraries(lab4 ${GLUT_LIBRARIES})
target_link_libraries(lab4 -lopengl32 -g -lfreeglut)