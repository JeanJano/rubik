#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

void print_cube_state(Cube cube) {
    std::cout << "Corners (position, orientation):\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << "(" << cube.corners[i].pos << ", " << cube.corners[i].ori << ") ";
    }
    std::cout << "\n";

    std::cout << "Edges (position, orientation):\n";
    for (int i = 0; i < 12; ++i) {
        std::cout << "(" << cube.edges[i].pos << ", " << cube.edges[i].ori << ") ";
    }
    std::cout << "\n";
}