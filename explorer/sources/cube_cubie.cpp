#include "defs_explorer.hpp"
#include "rubik_explorer.hpp"

void Cube_cubie::reset() {
    for (int i = 0; i < 8; ++i)
        corners[i] = {i, 0};
    for (int i = 0; i < 12; ++i)
        edges[i] = {i, 0};
}

std::string corner_to_string(Corner c) {
    return corner_names[static_cast<int>(c)];
}

std::string edge_to_string(Edge e) {
    return edge_names[static_cast<int>(e)];
}

std::ostream& operator<<(std::ostream& os, Edge e) {
    return os << edge_to_string(e);
}

Cube_cubie Cube_cubie::singleMove(const std::string& move, const Cube_cubie& inputCube) const{
    Cube_cubie new_cube = inputCube;
    if (move == "U"){
        new_cube.corners[0].pos = 3;
        new_cube.corners[1].pos = 0;
        new_cube.corners[2].pos = 1;
        new_cube.corners[3].pos = 2;
        new_cube.edges[0].pos = 3;
        new_cube.edges[1].pos = 0;
        new_cube.edges[2].pos = 1;
        new_cube.edges[3].pos = 2;
    } 
    else if (move == "U2"){
        new_cube.corners[0].pos = 2;
        new_cube.corners[1].pos = 3;
        new_cube.corners[2].pos = 0;
        new_cube.corners[3].pos = 1;
        new_cube.edges[0].pos = 2;
        new_cube.edges[1].pos = 3;
        new_cube.edges[2].pos = 0;
        new_cube.edges[3].pos = 1;
    } 
    else if (move == "U\'"){
        new_cube.corners[0].pos = 1;
        new_cube.corners[1].pos = 2;
        new_cube.corners[2].pos = 3;
        new_cube.corners[3].pos = 0;
        new_cube.edges[0].pos = 1;
        new_cube.edges[1].pos = 2;
        new_cube.edges[2].pos = 3;
        new_cube.edges[3].pos = 0;
    } 
    else if (move == "D"){
        new_cube.corners[4].pos = 5;
        new_cube.corners[5].pos = 6;
        new_cube.corners[6].pos = 7;
        new_cube.corners[7].pos = 4;
        new_cube.edges[4].pos = 5;
        new_cube.edges[5].pos = 6;
        new_cube.edges[6].pos = 7;
        new_cube.edges[7].pos = 4;
    } 
    else if (move == "D2"){ 
        new_cube.corners[4].pos = 6;
        new_cube.corners[5].pos = 7;
        new_cube.corners[6].pos = 4;
        new_cube.corners[7].pos = 5;
        new_cube.edges[4].pos = 6;
        new_cube.edges[5].pos = 7;
        new_cube.edges[6].pos = 4;
        new_cube.edges[7].pos = 5;
    }
    else if (move == "D\'"){
        new_cube.corners[4].pos = 7;
        new_cube.corners[5].pos = 4;
        new_cube.corners[6].pos = 5;
        new_cube.corners[7].pos = 6;
        new_cube.edges[4].pos = 7;
        new_cube.edges[5].pos = 4;
        new_cube.edges[6].pos = 5;
        new_cube.edges[7].pos = 6;
    } 
    else if (move == "F"){
        new_cube.corners[0].pos = 1;
        new_cube.corners[1].pos = 5;
        new_cube.corners[5].pos = 4;
        new_cube.corners[4].pos = 0;
        new_cube.corners[0].ori = 1;
        new_cube.corners[1].ori = 2;
        new_cube.corners[5].ori = 1;
        new_cube.corners[4].ori = 2;
        new_cube.edges[1].pos = 9;
        new_cube.edges[9].pos = 5;
        new_cube.edges[5].pos = 8;
        new_cube.edges[8].pos = 1;
        new_cube.edges[1].ori = 1;
        new_cube.edges[9].ori = 1;
        new_cube.edges[5].ori = 1;
        new_cube.edges[8].ori = 1;
    } 
    else if (move == "F2"){
        new_cube.corners[0].pos = 5;
        new_cube.corners[1].pos = 4;
        new_cube.corners[5].pos = 0;
        new_cube.corners[4].pos = 1;
        new_cube.edges[1].pos = 5;
        new_cube.edges[9].pos = 8;
        new_cube.edges[5].pos = 1;
        new_cube.edges[8].pos = 9;
    }
    else if (move == "F\'"){
        new_cube.corners[0].pos = 4;
        new_cube.corners[1].pos = 0;
        new_cube.corners[5].pos = 1;
        new_cube.corners[4].pos = 5;
        new_cube.corners[0].ori = 1;
        new_cube.corners[1].ori = 2;
        new_cube.corners[5].ori = 1;
        new_cube.corners[4].ori = 2;
        new_cube.edges[1].pos = 8;
        new_cube.edges[9].pos = 1;
        new_cube.edges[5].pos = 9;
        new_cube.edges[8].pos = 5;
        new_cube.edges[1].ori = 1;
        new_cube.edges[9].ori = 1;
        new_cube.edges[5].ori = 1;
        new_cube.edges[8].ori = 1;
    } 
    else if (move == "B"){ 
        new_cube.corners[2].pos = 3;
        new_cube.corners[3].pos = 7;
        new_cube.corners[7].pos = 6;
        new_cube.corners[6].pos = 2;
        new_cube.corners[2].ori = 1;
        new_cube.corners[3].ori = 2;
        new_cube.corners[6].ori = 2;
        new_cube.corners[7].ori = 1;
        new_cube.edges[3].pos = 11;
        new_cube.edges[11].pos = 7;
        new_cube.edges[7].pos = 10;
        new_cube.edges[10].pos = 3;
        new_cube.edges[1].ori = 1;
        new_cube.edges[9].ori = 1;
        new_cube.edges[5].ori = 1;
        new_cube.edges[8].ori = 1;
    }
    else if (move == "B2"){
        new_cube.corners[2].pos = 7;
        new_cube.corners[3].pos = 6;
        new_cube.corners[7].pos = 2;
        new_cube.corners[6].pos = 3;
        new_cube.edges[3].pos = 7;
        new_cube.edges[11].pos = 10;
        new_cube.edges[7].pos = 3;
        new_cube.edges[10].pos = 11;
    } 
    else if (move == "B\'"){
        new_cube.corners[2].pos = 6;
        new_cube.corners[3].pos = 2;
        new_cube.corners[7].pos = 3;
        new_cube.corners[6].pos = 7;
        new_cube.corners[2].ori = 1;
        new_cube.corners[3].ori = 2;
        new_cube.corners[6].ori = 2;
        new_cube.corners[7].ori = 1;
        new_cube.edges[3].pos = 10;
        new_cube.edges[10].pos = 7;
        new_cube.edges[7].pos = 11;
        new_cube.edges[11].pos = 3;
        new_cube.edges[1].ori = 1;
        new_cube.edges[9].ori = 1;
        new_cube.edges[5].ori = 1;
        new_cube.edges[8].ori = 1;
    } 
    else if (move == "R"){
        new_cube.corners[0].pos = 4;
        new_cube.corners[4].pos = 7;
        new_cube.corners[7].pos = 3;
        new_cube.corners[3].pos = 0;
        new_cube.corners[0].ori = 2;
        new_cube.corners[4].ori = 1;
        new_cube.corners[7].ori = 2;
        new_cube.corners[3].ori = 1;
        new_cube.edges[0].pos = 8;
        new_cube.edges[8].pos = 4;
        new_cube.edges[4].pos = 11;
        new_cube.edges[11].pos = 0;
        new_cube.edges[0].ori = 1;
        new_cube.edges[4].ori = 1;
        new_cube.edges[8].ori = 1;
        new_cube.edges[11].ori = 1;
    } 
    else if (move == "R2"){
        new_cube.corners[0].pos = 7;
        new_cube.corners[4].pos = 3;
        new_cube.corners[7].pos = 0;
        new_cube.corners[3].pos = 4;
        new_cube.edges[0].pos = 4;
        new_cube.edges[8].pos = 11;
        new_cube.edges[4].pos = 0;
        new_cube.edges[11].pos = 8;
    } 
    else if (move == "R\'"){
        new_cube.corners[0].pos = 3;
        new_cube.corners[4].pos = 0;
        new_cube.corners[7].pos = 4;
        new_cube.corners[3].pos = 7;
        new_cube.corners[0].ori = 2;
        new_cube.corners[4].ori = 1;
        new_cube.corners[7].ori = 2;
        new_cube.corners[3].ori = 1;
        new_cube.edges[0].pos = 11;
        new_cube.edges[8].pos = 0;
        new_cube.edges[4].pos = 8;
        new_cube.edges[11].pos = 4;
        new_cube.edges[0].ori = 1;
        new_cube.edges[4].ori = 1;
        new_cube.edges[8].ori = 1;
        new_cube.edges[11].ori = 1;
    } 
    else if (move == "L"){
        new_cube.corners[1].pos = 2;
        new_cube.corners[2].pos = 6;
        new_cube.corners[6].pos = 5;
        new_cube.corners[5].pos = 1;
        new_cube.corners[1].ori = 1;
        new_cube.corners[2].ori = 2;
        new_cube.corners[6].ori = 1;
        new_cube.corners[5].ori = 2;
        new_cube.edges[2].pos = 10;
        new_cube.edges[10].pos = 6;
        new_cube.edges[6].pos = 9;
        new_cube.edges[9].pos = 2;
        new_cube.edges[2].ori = 1;
        new_cube.edges[10].ori = 1;
        new_cube.edges[6].ori = 1;
        new_cube.edges[9].ori = 1;
    } 
    else if (move == "L2"){
        new_cube.corners[1].pos = 6;
        new_cube.corners[2].pos = 5;
        new_cube.corners[6].pos = 1;
        new_cube.corners[5].pos = 2;
        new_cube.edges[2].pos = 6;
        new_cube.edges[10].pos = 9;
        new_cube.edges[6].pos = 2;
        new_cube.edges[9].pos = 10;
    } 
    else if (move == "L\'"){
        new_cube.corners[1].pos = 5;
        new_cube.corners[2].pos = 1;
        new_cube.corners[6].pos = 2;
        new_cube.corners[5].pos = 6;
        new_cube.corners[1].ori = 1;
        new_cube.corners[2].ori = 2;
        new_cube.corners[6].ori = 1;
        new_cube.corners[5].ori = 2;
        new_cube.edges[2].pos = 9;
        new_cube.edges[10].pos = 2;
        new_cube.edges[6].pos = 10;
        new_cube.edges[9].pos = 6;
        new_cube.edges[2].ori = 1;
        new_cube.edges[10].ori = 1;
        new_cube.edges[6].ori = 1;
        new_cube.edges[9].ori = 1;
    } 
    else {std::cout<< "Fatal error in cube_cubie.cpp" << std::endl;}
    return new_cube;
}

Cube_cubie Cube_cubie::severalMoves(const std::vector<std::string>& moves, const Cube_cubie& inputCube) const {
    Cube_cubie current = inputCube;
    std::cout<< "before" << std::endl;
    print_scramble(moves);
    print_cubie_state(current);
    for (const std::string& move : moves) {
        current = this->singleMove(move, current);
    }
    std::cout<< "after" << std::endl;
    print_cubie_state(current);
    return current;
}