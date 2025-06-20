#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

void print_cubie_state(const Cube_cubie& cube) {
    std::cout << "Corners (position, orientation):\n";
    for (const auto& cornerCubie : cube.corners) {
        std::cout << "(" << corner_to_string(static_cast<Corner>(cornerCubie.pos))
                  << ", " << cornerCubie.ori << ") ";
    }
    std::cout << "\nEdges (position, orientation):\n";
    for (const auto& edgeCubie : cube.edges) {
        std::cout << "(" << edge_to_string(static_cast<Edge>(edgeCubie.pos))
                  << ", " << edgeCubie.ori << ") ";
    }
    std::cout << "\n";
}

void print_scramble(const std::vector<std::string>& scramble) {
    std::cout << "Scramble: ";
    for (const std::string& move : scramble) {
        std::cout << move << " ";
    }
    std::cout << std::endl;
}