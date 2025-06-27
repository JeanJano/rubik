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

// void print_scramble(const std::vector<std::string>& scramble) {
//     std::cout << "Scramble: ";
//     for (const std::string& move : scramble) {
//         std::cout << move << " ";
//     }
//     std::cout << std::endl;
// }

void print_scramble(const std::vector<Move>& scramble) {
    std::cout << "Scramble:\n";
    for (const Move& move : scramble) {
        std::cout << static_cast<int>(move) << ": (" << moveToString(move) << ") ";
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

void cornerOrientCoord::print_explicit_corn_ori_coord2() const {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

std::string moveToString(Move move) {
    switch (move) {
        case Move::U1:  return "U";
        case Move::U2:  return "U2";
        case Move::U3:  return "U'";
        case Move::R1:  return "R";
        case Move::R2:  return "R2";
        case Move::R3:  return "R'";
        case Move::F1:  return "F";
        case Move::F2:  return "F2";
        case Move::F3:  return "F'";
        case Move::D1:  return "D";
        case Move::D2:  return "D2";
        case Move::D3:  return "D'";
        case Move::L1:  return "L";
        case Move::L2:  return "L2";
        case Move::L3:  return "L'";
        case Move::B1:  return "B";
        case Move::B2:  return "B2";
        case Move::B3:  return "B'";
        default:        return "Unknown";
    }
}