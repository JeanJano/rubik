#include "defs_explorer.hpp"
#include "rubik_explorer.hpp"

void cubeCubie::reset() {
    for (uint8_t i = 0; i < 8; ++i)
        corners[i] = {i, 0};
    for (uint8_t i = 0; i < 12; ++i)
        edges[i] = {i, 0};
}

//definition of permutation and orientatiuon in basic moves 
cubeCubie cubeCubie::basicMove(const std::string& move, const cubeCubie& inputCube) const{
    cubeCubie newCube = inputCube;
    if (move == "U"){
        newCube.corners[0].pos = inputCube.corners[3].pos;
        newCube.corners[1].pos = inputCube.corners[0].pos;
        newCube.corners[2].pos = inputCube.corners[1].pos;
        newCube.corners[3].pos = inputCube.corners[2].pos;
        newCube.corners[0].ori = inputCube.corners[3].ori;
        newCube.corners[1].ori = inputCube.corners[0].ori;
        newCube.corners[2].ori = inputCube.corners[1].ori;
        newCube.corners[3].ori = inputCube.corners[2].ori;
        newCube.edges[0].pos = inputCube.edges[3].pos;
        newCube.edges[1].pos = inputCube.edges[0].pos;
        newCube.edges[2].pos = inputCube.edges[1].pos;
        newCube.edges[3].pos = inputCube.edges[2].pos;
        newCube.edges[0].ori = inputCube.edges[3].ori;
        newCube.edges[1].ori = inputCube.edges[0].ori;
        newCube.edges[2].ori = inputCube.edges[1].ori;
        newCube.edges[3].ori = inputCube.edges[2].ori;
    } 
    else if (move == "U2"){
        newCube.corners[0].pos = inputCube.corners[2].pos;
        newCube.corners[1].pos = inputCube.corners[3].pos;
        newCube.corners[2].pos = inputCube.corners[0].pos;
        newCube.corners[3].pos = inputCube.corners[1].pos;
        newCube.corners[0].ori = inputCube.corners[2].ori;
        newCube.corners[1].ori = inputCube.corners[3].ori;
        newCube.corners[2].ori = inputCube.corners[0].ori;
        newCube.corners[3].ori = inputCube.corners[1].ori;
        newCube.edges[0].pos = inputCube.edges[2].pos;
        newCube.edges[1].pos = inputCube.edges[3].pos;
        newCube.edges[2].pos = inputCube.edges[0].pos;
        newCube.edges[3].pos = inputCube.edges[1].pos;
        newCube.edges[0].ori = inputCube.edges[2].ori;
        newCube.edges[1].ori = inputCube.edges[3].ori;
        newCube.edges[2].ori = inputCube.edges[0].ori;
        newCube.edges[3].ori = inputCube.edges[1].ori;
    } 
    else if (move == "U\'"){
        newCube.corners[0].pos = inputCube.corners[1].pos;
        newCube.corners[1].pos = inputCube.corners[2].pos;
        newCube.corners[2].pos = inputCube.corners[3].pos;
        newCube.corners[3].pos = inputCube.corners[0].pos;
        newCube.corners[0].ori = inputCube.corners[1].ori;
        newCube.corners[1].ori = inputCube.corners[2].ori;
        newCube.corners[2].ori = inputCube.corners[3].ori;
        newCube.corners[3].ori = inputCube.corners[0].ori;
        newCube.edges[0].pos = inputCube.edges[1].pos;
        newCube.edges[1].pos = inputCube.edges[2].pos;
        newCube.edges[2].pos = inputCube.edges[3].pos;
        newCube.edges[3].pos = inputCube.edges[0].pos;
        newCube.edges[0].ori = inputCube.edges[1].ori;
        newCube.edges[1].ori = inputCube.edges[2].ori;
        newCube.edges[2].ori = inputCube.edges[3].ori;
        newCube.edges[3].ori = inputCube.edges[0].ori;
    } 
    else if (move == "D"){
        newCube.corners[4].pos = inputCube.corners[5].pos;
        newCube.corners[5].pos = inputCube.corners[6].pos;
        newCube.corners[6].pos = inputCube.corners[7].pos;
        newCube.corners[7].pos = inputCube.corners[4].pos;
        newCube.corners[4].ori = inputCube.corners[5].ori;
        newCube.corners[5].ori = inputCube.corners[6].ori;
        newCube.corners[6].ori = inputCube.corners[7].ori;
        newCube.corners[7].ori = inputCube.corners[4].ori;
        newCube.edges[4].pos = inputCube.edges[5].pos;
        newCube.edges[5].pos = inputCube.edges[6].pos;
        newCube.edges[6].pos = inputCube.edges[7].pos;
        newCube.edges[7].pos = inputCube.edges[4].pos;
        newCube.edges[4].ori = inputCube.edges[5].ori;
        newCube.edges[5].ori = inputCube.edges[6].ori;
        newCube.edges[6].ori = inputCube.edges[7].ori;
        newCube.edges[7].ori = inputCube.edges[4].ori;
    } 
    else if (move == "D2"){ 
        newCube.corners[4].pos = inputCube.corners[6].pos;
        newCube.corners[5].pos = inputCube.corners[7].pos;
        newCube.corners[6].pos = inputCube.corners[4].pos;
        newCube.corners[7].pos = inputCube.corners[5].pos;
        newCube.corners[4].ori = inputCube.corners[6].ori;
        newCube.corners[5].ori = inputCube.corners[7].ori;
        newCube.corners[6].ori = inputCube.corners[4].ori;
        newCube.corners[7].ori = inputCube.corners[5].ori;
        newCube.edges[4].pos = inputCube.edges[6].pos;
        newCube.edges[5].pos = inputCube.edges[7].pos;
        newCube.edges[6].pos = inputCube.edges[4].pos;
        newCube.edges[7].pos = inputCube.edges[5].pos;
        newCube.edges[4].ori = inputCube.edges[6].ori;
        newCube.edges[5].ori = inputCube.edges[7].ori;
        newCube.edges[6].ori = inputCube.edges[4].ori;
        newCube.edges[7].ori = inputCube.edges[5].ori;
    }
    else if (move == "D\'"){
        newCube.corners[4].pos = inputCube.corners[7].pos;
        newCube.corners[5].pos = inputCube.corners[4].pos;
        newCube.corners[6].pos = inputCube.corners[5].pos;
        newCube.corners[7].pos = inputCube.corners[6].pos;
        newCube.corners[4].ori = inputCube.corners[7].ori;
        newCube.corners[5].ori = inputCube.corners[4].ori;
        newCube.corners[6].ori = inputCube.corners[5].ori;
        newCube.corners[7].ori = inputCube.corners[6].ori;
        newCube.edges[4].pos = inputCube.edges[7].pos;
        newCube.edges[5].pos = inputCube.edges[4].pos;
        newCube.edges[6].pos = inputCube.edges[5].pos;
        newCube.edges[7].pos = inputCube.edges[6].pos;
        newCube.edges[4].ori = inputCube.edges[7].ori;
        newCube.edges[5].ori = inputCube.edges[4].ori;
        newCube.edges[6].ori = inputCube.edges[5].ori;
        newCube.edges[7].ori = inputCube.edges[6].ori;
    } 
    else if (move == "F"){
        newCube.corners[0].pos = inputCube.corners[1].pos;
        newCube.corners[1].pos = inputCube.corners[5].pos;
        newCube.corners[5].pos = inputCube.corners[4].pos;
        newCube.corners[4].pos = inputCube.corners[0].pos;
        newCube.corners[0].ori = (inputCube.corners[1].ori + 1) % 3;
        newCube.corners[1].ori = (inputCube.corners[5].ori + 2) % 3;
        newCube.corners[5].ori = (inputCube.corners[4].ori + 1) % 3;
        newCube.corners[4].ori = (inputCube.corners[0].ori + 2) % 3;
        newCube.edges[1].pos = inputCube.edges[9].pos;
        newCube.edges[9].pos = inputCube.edges[5].pos;
        newCube.edges[5].pos = inputCube.edges[8].pos;
        newCube.edges[8].pos = inputCube.edges[1].pos;
        newCube.edges[1].ori = (inputCube.edges[9].ori + 1) % 2;
        newCube.edges[9].ori = (inputCube.edges[5].ori + 1) % 2;
        newCube.edges[5].ori = (inputCube.edges[8].ori + 1) % 2;
        newCube.edges[8].ori = (inputCube.edges[1].ori + 1) % 2;
    } 
    else if (move == "F2"){
        newCube.corners[0].pos = inputCube.corners[5].pos;
        newCube.corners[1].pos = inputCube.corners[4].pos;
        newCube.corners[5].pos = inputCube.corners[0].pos;
        newCube.corners[4].pos = inputCube.corners[1].pos;
        newCube.corners[0].ori = inputCube.corners[5].ori;
        newCube.corners[1].ori = inputCube.corners[4].ori;
        newCube.corners[5].ori = inputCube.corners[0].ori;
        newCube.corners[4].ori = inputCube.corners[1].ori;
        newCube.edges[1].pos = inputCube.edges[5].pos;
        newCube.edges[9].pos = inputCube.edges[8].pos;
        newCube.edges[5].pos = inputCube.edges[1].pos;
        newCube.edges[8].pos = inputCube.edges[9].pos;
        newCube.edges[1].ori = inputCube.edges[5].ori;
        newCube.edges[9].ori = inputCube.edges[8].ori;
        newCube.edges[5].ori = inputCube.edges[1].ori;
        newCube.edges[8].ori = inputCube.edges[9].ori;
    }
    else if (move == "F\'"){
        newCube.corners[0].pos = inputCube.corners[4].pos;
        newCube.corners[1].pos = inputCube.corners[0].pos;
        newCube.corners[5].pos = inputCube.corners[1].pos;
        newCube.corners[4].pos = inputCube.corners[5].pos;
        newCube.corners[0].ori = (inputCube.corners[4].ori + 1) % 3;
        newCube.corners[1].ori = (inputCube.corners[0].ori + 2) % 3;
        newCube.corners[5].ori = (inputCube.corners[1].ori + 1) % 3;
        newCube.corners[4].ori = (inputCube.corners[5].ori + 2) % 3;
        newCube.edges[1].pos = inputCube.edges[8].pos;
        newCube.edges[9].pos = inputCube.edges[1].pos;
        newCube.edges[5].pos = inputCube.edges[9].pos;
        newCube.edges[8].pos = inputCube.edges[5].pos;
        newCube.edges[1].ori = (inputCube.edges[8].ori + 1) % 2;
        newCube.edges[9].ori = (inputCube.edges[1].ori + 1) % 2;
        newCube.edges[5].ori = (inputCube.edges[9].ori + 1) % 2;
        newCube.edges[8].ori = (inputCube.edges[5].ori + 1) % 2;
    } 
    else if (move == "B"){ 
        newCube.corners[2].pos = inputCube.corners[3].pos;
        newCube.corners[3].pos = inputCube.corners[7].pos;
        newCube.corners[7].pos = inputCube.corners[6].pos;
        newCube.corners[6].pos = inputCube.corners[2].pos;
        newCube.corners[2].ori = (inputCube.corners[3].ori + 1) % 3;
        newCube.corners[3].ori = (inputCube.corners[7].ori + 2) % 3;
        newCube.corners[7].ori = (inputCube.corners[6].ori + 1) % 3;
        newCube.corners[6].ori = (inputCube.corners[2].ori + 2) % 3;
        newCube.edges[3].pos = inputCube.edges[11].pos;
        newCube.edges[11].pos = inputCube.edges[7].pos;
        newCube.edges[7].pos = inputCube.edges[10].pos;
        newCube.edges[10].pos = inputCube.edges[3].pos;
        newCube.edges[3].ori = (inputCube.edges[11].ori + 1) % 2;
        newCube.edges[11].ori = (inputCube.edges[7].ori + 1) % 2;
        newCube.edges[7].ori = (inputCube.edges[10].ori + 1) % 2;
        newCube.edges[10].ori = (inputCube.edges[3].ori + 1) % 2;
    }
    else if (move == "B2"){
        newCube.corners[2].pos = inputCube.corners[7].pos;
        newCube.corners[3].pos = inputCube.corners[6].pos;
        newCube.corners[7].pos = inputCube.corners[2].pos;
        newCube.corners[6].pos = inputCube.corners[3].pos;
        newCube.corners[2].ori = inputCube.corners[7].ori;
        newCube.corners[3].ori = inputCube.corners[6].ori;
        newCube.corners[7].ori = inputCube.corners[2].ori;
        newCube.corners[6].ori = inputCube.corners[3].ori;
        newCube.edges[3].pos = inputCube.edges[7].pos;
        newCube.edges[11].pos = inputCube.edges[10].pos;
        newCube.edges[7].pos = inputCube.edges[3].pos;
        newCube.edges[10].pos = inputCube.edges[11].pos;
        newCube.edges[3].ori = inputCube.edges[7].ori;
        newCube.edges[11].ori = inputCube.edges[10].ori;
        newCube.edges[7].ori = inputCube.edges[3].ori;
        newCube.edges[10].ori = inputCube.edges[11].ori;
    } 
    else if (move == "B\'"){
        newCube.corners[2].pos = inputCube.corners[6].pos;
        newCube.corners[3].pos = inputCube.corners[2].pos;
        newCube.corners[7].pos = inputCube.corners[3].pos;
        newCube.corners[6].pos = inputCube.corners[7].pos;
        newCube.corners[2].ori = (inputCube.corners[6].ori + 1) % 3;
        newCube.corners[3].ori = (inputCube.corners[2].ori + 2) % 3;
        newCube.corners[7].ori = (inputCube.corners[3].ori + 1) % 3;
        newCube.corners[6].ori = (inputCube.corners[7].ori + 2) % 3;
        newCube.edges[3].pos = inputCube.edges[10].pos;
        newCube.edges[10].pos = inputCube.edges[7].pos;
        newCube.edges[7].pos = inputCube.edges[11].pos;
        newCube.edges[11].pos = inputCube.edges[3].pos;
        newCube.edges[3].ori = (inputCube.edges[10].ori + 1) % 2;
        newCube.edges[10].ori = (inputCube.edges[7].ori + 1) % 2;
        newCube.edges[7].ori = (inputCube.edges[11].ori + 1) % 2;
        newCube.edges[11].ori = (inputCube.edges[3].ori + 1) % 2;
    } 
    else if (move == "R"){
        newCube.corners[0].pos = inputCube.corners[4].pos;
        newCube.corners[4].pos = inputCube.corners[7].pos;
        newCube.corners[7].pos = inputCube.corners[3].pos;
        newCube.corners[3].pos = inputCube.corners[0].pos;
        newCube.corners[0].ori = (inputCube.corners[4].ori + 2) % 3;
        newCube.corners[4].ori = (inputCube.corners[7].ori + 1) % 3;
        newCube.corners[7].ori = (inputCube.corners[3].ori + 2) % 3;
        newCube.corners[3].ori = (inputCube.corners[0].ori + 1) % 3;
        newCube.edges[0].pos = inputCube.edges[8].pos;
        newCube.edges[8].pos = inputCube.edges[4].pos;
        newCube.edges[4].pos = inputCube.edges[11].pos;
        newCube.edges[11].pos = inputCube.edges[0].pos;
        newCube.edges[0].ori = inputCube.edges[8].ori;
        newCube.edges[8].ori = inputCube.edges[4].ori;
        newCube.edges[4].ori = inputCube.edges[11].ori;
        newCube.edges[11].ori = inputCube.edges[0].ori;
    } 
    else if (move == "R2"){
        newCube.corners[0].pos = inputCube.corners[7].pos;
        newCube.corners[4].pos = inputCube.corners[3].pos;
        newCube.corners[7].pos = inputCube.corners[0].pos;
        newCube.corners[3].pos = inputCube.corners[4].pos;
        newCube.corners[0].ori = inputCube.corners[7].ori;
        newCube.corners[4].ori = inputCube.corners[3].ori;
        newCube.corners[7].ori = inputCube.corners[0].ori;
        newCube.corners[3].ori = inputCube.corners[4].ori;
        newCube.edges[0].pos = inputCube.edges[4].pos;
        newCube.edges[8].pos = inputCube.edges[11].pos;
        newCube.edges[4].pos = inputCube.edges[0].pos;
        newCube.edges[11].pos = inputCube.edges[8].pos;
        newCube.edges[0].ori = inputCube.edges[4].ori;
        newCube.edges[8].ori = inputCube.edges[11].ori;
        newCube.edges[4].ori = inputCube.edges[0].ori;
        newCube.edges[11].ori = inputCube.edges[8].ori;
    } 
    else if (move == "R\'"){
        newCube.corners[0].pos = inputCube.corners[3].pos;
        newCube.corners[4].pos = inputCube.corners[0].pos;
        newCube.corners[7].pos = inputCube.corners[4].pos;
        newCube.corners[3].pos = inputCube.corners[7].pos;
        newCube.corners[0].ori = (inputCube.corners[3].ori + 2) % 3;
        newCube.corners[4].ori = (inputCube.corners[0].ori + 1) % 3;
        newCube.corners[7].ori = (inputCube.corners[4].ori + 2) % 3;
        newCube.corners[3].ori = (inputCube.corners[7].ori + 1) % 3;
        newCube.edges[0].pos = inputCube.edges[11].pos;
        newCube.edges[8].pos = inputCube.edges[0].pos;
        newCube.edges[4].pos = inputCube.edges[8].pos;
        newCube.edges[11].pos = inputCube.edges[4].pos;
        newCube.edges[0].ori = inputCube.edges[11].ori;
        newCube.edges[8].ori = inputCube.edges[0].ori;
        newCube.edges[4].ori = inputCube.edges[8].ori;
        newCube.edges[11].ori = inputCube.edges[4].ori;
    } 
    else if (move == "L"){
        newCube.corners[1].pos = inputCube.corners[2].pos;
        newCube.corners[2].pos = inputCube.corners[6].pos;
        newCube.corners[6].pos = inputCube.corners[5].pos;
        newCube.corners[5].pos = inputCube.corners[1].pos;
        newCube.corners[1].ori = (inputCube.corners[2].ori + 1) % 3;
        newCube.corners[2].ori = (inputCube.corners[6].ori + 2) % 3;
        newCube.corners[6].ori = (inputCube.corners[5].ori + 1) % 3;
        newCube.corners[5].ori = (inputCube.corners[1].ori + 2) % 3;
        newCube.edges[2].pos = inputCube.edges[10].pos;
        newCube.edges[10].pos = inputCube.edges[6].pos;
        newCube.edges[6].pos = inputCube.edges[9].pos;
        newCube.edges[9].pos = inputCube.edges[2].pos;
        newCube.edges[2].ori = inputCube.edges[10].ori;
        newCube.edges[10].ori = inputCube.edges[6].ori;
        newCube.edges[6].ori = inputCube.edges[9].ori;
        newCube.edges[9].ori = inputCube.edges[2].ori;
    } 
    else if (move == "L2"){
        newCube.corners[1].pos = inputCube.corners[6].pos;
        newCube.corners[2].pos = inputCube.corners[5].pos;
        newCube.corners[6].pos = inputCube.corners[1].pos;
        newCube.corners[5].pos = inputCube.corners[2].pos;
        newCube.corners[1].ori = inputCube.corners[6].ori;
        newCube.corners[2].ori = inputCube.corners[5].ori;
        newCube.corners[6].ori = inputCube.corners[1].ori;
        newCube.corners[5].ori = inputCube.corners[2].ori;
        newCube.edges[2].pos = inputCube.edges[6].pos;
        newCube.edges[10].pos = inputCube.edges[9].pos;
        newCube.edges[6].pos = inputCube.edges[2].pos;
        newCube.edges[9].pos = inputCube.edges[10].pos;
        newCube.edges[2].ori = inputCube.edges[6].ori;
        newCube.edges[10].ori = inputCube.edges[9].ori;
        newCube.edges[6].ori = inputCube.edges[2].ori;
        newCube.edges[9].ori = inputCube.edges[10].ori;
    } 
    else if (move == "L\'"){
        newCube.corners[1].pos = inputCube.corners[5].pos;
        newCube.corners[2].pos = inputCube.corners[1].pos;
        newCube.corners[6].pos = inputCube.corners[2].pos;
        newCube.corners[5].pos = inputCube.corners[6].pos;
        newCube.corners[1].ori = (inputCube.corners[5].ori + 1) % 3;
        newCube.corners[2].ori = (inputCube.corners[1].ori + 2) % 3;
        newCube.corners[6].ori = (inputCube.corners[2].ori + 1) % 3;
        newCube.corners[5].ori = (inputCube.corners[6].ori + 2) % 3;
        newCube.edges[2].pos = inputCube.edges[9].pos;
        newCube.edges[10].pos = inputCube.edges[2].pos;
        newCube.edges[6].pos = inputCube.edges[10].pos;
        newCube.edges[9].pos = inputCube.edges[6].pos;
        newCube.edges[2].ori = inputCube.edges[9].ori;
        newCube.edges[10].ori = inputCube.edges[2].ori;
        newCube.edges[6].ori = inputCube.edges[10].ori;
        newCube.edges[9].ori = inputCube.edges[6].ori;
    } 
    else {std::cout<< "Fatal error in cubeCubie.cpp" << std::endl;}
    return newCube;
}

cubeCubie cubeCubie::severalMoves(const std::vector<std::string>& moves, const cubeCubie& inputCube) const {
    cubeCubie current = inputCube;
    for (const std::string& move : moves) {
        current = this->basicMove(move, current);
    }
    return current;
}

cubeCubie get_scrambled_state(std::vector<std::string> scramble){
    cubeCubie cube;
    cube.reset();
    cube = cube.severalMoves(scramble, cube);
    return cube;
}
