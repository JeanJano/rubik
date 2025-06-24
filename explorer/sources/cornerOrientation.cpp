#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

cornerOrientCoord::cornerOrientCoord() {
    explicitCoor.fill(0);
}

//extract orientation corner coordinate from cubie representation
cornerOrientCoord::cornerOrientCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.corners[i].ori;
    }
}

void cornerOrientCoord::print_explicit_corn_ori_coord() const {
    std::cout << "Corner Orientation (explicit): ";
    for (int i = 0; i < N; ++i) {
        std::cout << static_cast<int>(explicitCoor[i]) << " ";
    }
    std::cout << std::endl;
}

cornerOrientCoord cornerOrientCoord::cornOriMove(const std::string& move) {
    cornerOrientCoord newCoord = *this;
    if (move == "U"){
        newCoord.explicitCoor[0] = explicitCoor[3];
        newCoord.explicitCoor[1] = explicitCoor[0];
        newCoord.explicitCoor[2] = explicitCoor[1];
        newCoord.explicitCoor[3] = explicitCoor[2];
    }
    else if (move == "U2"){
        newCoord.explicitCoor[0] = explicitCoor[2];
        newCoord.explicitCoor[1] = explicitCoor[3];
        newCoord.explicitCoor[2] = explicitCoor[0];
        newCoord.explicitCoor[3] = explicitCoor[1];
    }
    else if (move == "U\'"){
        newCoord.explicitCoor[0] = explicitCoor[1];
        newCoord.explicitCoor[1] = explicitCoor[2];
        newCoord.explicitCoor[2] = explicitCoor[3];
        newCoord.explicitCoor[3] = explicitCoor[0];
    }
    else if (move == "D"){
        newCoord.explicitCoor[4] = explicitCoor[5];
        newCoord.explicitCoor[5] = explicitCoor[6];
        newCoord.explicitCoor[6] = explicitCoor[7];
        newCoord.explicitCoor[7] = explicitCoor[4];
    }
    else if (move == "D2"){
        newCoord.explicitCoor[4] = explicitCoor[6];
        newCoord.explicitCoor[5] = explicitCoor[7];
        newCoord.explicitCoor[6] = explicitCoor[4];
        newCoord.explicitCoor[7] = explicitCoor[5];
    }
    else if (move == "D\'"){
        newCoord.explicitCoor[4] = explicitCoor[7];
        newCoord.explicitCoor[5] = explicitCoor[4];
        newCoord.explicitCoor[6] = explicitCoor[5];
        newCoord.explicitCoor[7] = explicitCoor[6];
    }
    else if (move == "F"){
        newCoord.explicitCoor[0] = (explicitCoor[1] + 1) % 3;
        newCoord.explicitCoor[1] = (explicitCoor[5] + 2) % 3;
        newCoord.explicitCoor[5] = (explicitCoor[4] + 1) % 3;
        newCoord.explicitCoor[4] = (explicitCoor[0] + 2) % 3;
    }
    else if (move == "F2"){
        newCoord.explicitCoor[0] = explicitCoor[5];
        newCoord.explicitCoor[1] = explicitCoor[4];
        newCoord.explicitCoor[5] = explicitCoor[0];
        newCoord.explicitCoor[4] = explicitCoor[1];
    }
    else if (move == "F\'"){
        newCoord.explicitCoor[0] = (explicitCoor[4] + 1) % 3;
        newCoord.explicitCoor[1] = (explicitCoor[0] + 2) % 3;
        newCoord.explicitCoor[5] = (explicitCoor[1] + 1) % 3;
        newCoord.explicitCoor[4] = (explicitCoor[5] + 2) % 3;
    }
    else if (move == "B"){
        newCoord.explicitCoor[2] = (explicitCoor[3] + 1) % 3;
        newCoord.explicitCoor[3] = (explicitCoor[7] + 2) % 3;
        newCoord.explicitCoor[7] = (explicitCoor[6] + 1) % 3;
        newCoord.explicitCoor[6] = (explicitCoor[2] + 2) % 3;
    }
    else if (move == "B2"){
        newCoord.explicitCoor[2] = explicitCoor[7];
        newCoord.explicitCoor[3] = explicitCoor[6];
        newCoord.explicitCoor[7] = explicitCoor[2];
        newCoord.explicitCoor[6] = explicitCoor[3];
    }
    else if (move == "B\'"){
        newCoord.explicitCoor[2] = (explicitCoor[6] + 1) % 3;
        newCoord.explicitCoor[3] = (explicitCoor[2] + 2) % 3;
        newCoord.explicitCoor[7] = (explicitCoor[3] + 1) % 3;
        newCoord.explicitCoor[6] = (explicitCoor[7] + 2) % 3;
    }
    else if (move == "R"){
        newCoord.explicitCoor[0] = (explicitCoor[4] + 2) % 3;
        newCoord.explicitCoor[3] = (explicitCoor[0] + 1) % 3;
        newCoord.explicitCoor[7] = (explicitCoor[3] + 2) % 3;
        newCoord.explicitCoor[4] = (explicitCoor[7] + 1) % 3;
    }
    else if (move == "R2"){
        newCoord.explicitCoor[0] = explicitCoor[7];
        newCoord.explicitCoor[3] = explicitCoor[4];
        newCoord.explicitCoor[7] = explicitCoor[0];
        newCoord.explicitCoor[4] = explicitCoor[3];
    }
    else if (move == "R\'"){
        newCoord.explicitCoor[0] = (explicitCoor[3] + 2) % 3;
        newCoord.explicitCoor[3] = (explicitCoor[7] + 1) % 3;
        newCoord.explicitCoor[7] = (explicitCoor[4] + 2) % 3;
        newCoord.explicitCoor[4] = (explicitCoor[0] + 1) % 3;
    }
    else if (move == "L"){
        newCoord.explicitCoor[1] = (explicitCoor[2] + 1) % 3;
        newCoord.explicitCoor[2] = (explicitCoor[6] + 2) % 3;
        newCoord.explicitCoor[6] = (explicitCoor[5] + 1) % 3;
        newCoord.explicitCoor[5] = (explicitCoor[1] + 2) % 3;
    }
    else if (move == "L2"){
        newCoord.explicitCoor[1] = explicitCoor[6];
        newCoord.explicitCoor[2] = explicitCoor[5];
        newCoord.explicitCoor[6] = explicitCoor[1];
        newCoord.explicitCoor[5] = explicitCoor[2];
    }
    else if (move == "L\'"){
        newCoord.explicitCoor[1] = (explicitCoor[5] + 1) % 3;
        newCoord.explicitCoor[2] = (explicitCoor[1] + 2) % 3;
        newCoord.explicitCoor[6] = (explicitCoor[2] + 1) % 3;
        newCoord.explicitCoor[5] = (explicitCoor[6] + 2) % 3;
    }
    else {std::cout<< "Fatal error in cornerOrientation.cpp" << std::endl;}
    return newCoord;
}