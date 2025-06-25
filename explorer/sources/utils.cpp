#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"


std::string corner_to_string(Corner c) {
    return corner_names[static_cast<int>(c)];
}

std::string edge_to_string(Edge e) {
    return edge_names[static_cast<int>(e)];
}

void print_cubie_state(const cubeCubie& cube) {
    std::cout << "Corners (position, orientation):\n";
    for (const auto& cornerCubie : cube.corners) {
        std::cout << "(" << corner_to_string(static_cast<Corner>(cornerCubie.pos))
                  << ", " << static_cast<int>(cornerCubie.ori) << ") ";
    }
    std::cout << "\nEdges (position, orientation):\n";
    for (const auto& edgeCubie : cube.edges) {
        std::cout << "(" << edge_to_string(static_cast<Edge>(edgeCubie.pos))
                  << ", " << static_cast<int>(edgeCubie.ori) << ") ";
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

void cornerOrientCoord::print_explicit_corn_ori_coord() const {
    std::cout << "Corner Orientation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}