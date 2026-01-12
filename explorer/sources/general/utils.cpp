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


void cornerPermCoord::printExplicitCornPermCoord() {
    std::cout << "Corner Permutation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void cornerPermCoord::printExplicitCornPermCoord2() {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void edgePermCoord::printExplicitEdgePermCoord() {
    std::cout << "edge Permutation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void edgePermCoord::printExplicitEdgePermCoord2() {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void UDSTwoCoord::printExplicitUDSTPermCoord() {
    std::cout << "edge Permutation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void UDSTwoCoord::printExplicitUDSTPermCoord2() {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}


void edgeOrientCoord::print_explicit_edge_ori_coord() const {
    std::cout << "Edge Orientation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void edgeOrientCoord::print_explicit_edge_ori_coord2() const {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
        if((i + 1) % 4 == 0)
            std::cout << " ";
    }
    std::cout << std::endl;
}


void UDSliceCoord::print_explicit_udslice_ori_coord() const {
    std::cout << "UD slice (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

void UDSliceCoord::print_explicit_udslice_ori_coord2() const {
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
        if((i + 1) % 4 == 0)
            std::cout << " ";
    }
    std::cout << std::endl;
}


void cornerPermCoord::printOrderDiagram() const {
    std::cout << "OrderDiagram (" << OrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < OrderDiagram.size(); ++i) {
        std::cout << int(OrderDiagram[i]);
        if (i + 1 < OrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
}

void cornerPermCoord::printNextOrderDiagram() const {
    std::cout << "nextOrderDiagram (" << nextOrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < nextOrderDiagram.size(); ++i) {
        std::cout << int(nextOrderDiagram[i]);
        if (i + 1 < nextOrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
}

void edgePermCoord::printOrderDiagram() const {
    std::cout << "edge OrderDiagram (" << OrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < OrderDiagram.size(); ++i) {
        std::cout << int(OrderDiagram[i]);
        if (i + 1 < OrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
}

void edgePermCoord::printNextOrderDiagram() const {
    std::cout << "edge nextOrderDiagram (" << nextOrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < nextOrderDiagram.size(); ++i) {
        std::cout << int(nextOrderDiagram[i]);
        if (i + 1 < nextOrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
}

void UDSTwoCoord::printOrderDiagram() const {
    std::cout << "UDS2 OrderDiagram (" << OrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < OrderDiagram.size(); ++i) {
        std::cout << int(OrderDiagram[i]);
        if (i + 1 < OrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
}

void UDSTwoCoord::printNextOrderDiagram() const {
    std::cout << "UDS2 nextOrderDiagram (" << nextOrderDiagram.size() << "): [ ";

    for (size_t i = 0; i < nextOrderDiagram.size(); ++i) {
        std::cout << int(nextOrderDiagram[i]);
        if (i + 1 < nextOrderDiagram.size())
            std::cout << " ";
    }

    std::cout << " ]\n";
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

std::string moveToString(GOneMove move) {
    switch (move) {
        case GOneMove::U1:  return "U";
        case GOneMove::U2:  return "U2";
        case GOneMove::U3:  return "U'";
        case GOneMove::R2:  return "R2";
        case GOneMove::F2:  return "F2";
        case GOneMove::D1:  return "D";
        case GOneMove::D2:  return "D2";
        case GOneMove::D3:  return "D'";
        case GOneMove::L2:  return "L2";
        case GOneMove::B2:  return "B2";
        default:        return "Unknown";
    }
}

uint16_t get_coord(const cornerOrientCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(const edgeOrientCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(const UDSliceCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(const cornerPermCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(const edgePermCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(const UDSTwoCoord& coord) {
    return coord.get_pure_coord();
}

uint16_t get_coord(uint16_t coord) {
    return coord;
}

Move get_move(const std::string& moveStr) {
    auto it = string_to_move.find(moveStr);
    if (it != string_to_move.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid move string: " + moveStr);
}

Move get_move(int moveIndex) {
    if (moveIndex < 0 || moveIndex > 17) {
        throw std::invalid_argument("Invalid move index: " + std::to_string(moveIndex));
    }
    return static_cast<Move>(moveIndex);
}

Move get_move(Move move) {
    return move;
}



GOneMove getGOneMve(const std::string& moveStr) {
    auto it = stringToGOneMove.find(moveStr);
    if (it != stringToGOneMove.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid move string: " + moveStr);
}

GOneMove getGOneMove(int moveIndex) {
    if (moveIndex < 0 || moveIndex > 9) {
        throw std::invalid_argument("Invalid move index: " + std::to_string(moveIndex));
    }
    return static_cast<GOneMove>(moveIndex);
}

GOneMove getGOneMove(GOneMove move) {
    return move;
}



uint16_t factorial(uint16_t n){
    return (n <= 1) ? 1 : n * factorial(n - 1);
}