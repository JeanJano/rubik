#include "defs_explorer.hpp"

cornerPermCoordTwo::cornerPermCoordTwo() {
    for(int i = 0; i < N; ++i){
        explicitCoor[i] = i;
    }
    cornerPermCoordTwo::defineOrderDiag();
    cornerPermCoordTwo::defineNextOrderDiag();
}

//extract orientation corner coordinate from cubie representation
cornerPermCoordTwo::cornerPermCoordTwo(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.corners[i].pos;
    }
    // std::cout << "in Cperm const" << std::endl;
    // this->printExplicitCornPermCoord();
    cornerPermCoordTwo::defineOrderDiag();
    cornerPermCoordTwo::defineNextOrderDiag();
}


cornerPermCoordTwo cornerPermCoordTwo::move(const Move& move) const {
    cornerPermCoordTwo newCoord = *this;

    // std::cout << "in move" << std::endl;
    // newCoord.printExplicitCornPermCoord();
    switch (move) {
        case Move::U1:
            newCoord.explicitCoor[0] = explicitCoor[3];
            newCoord.explicitCoor[1] = explicitCoor[0];
            newCoord.explicitCoor[2] = explicitCoor[1];
            newCoord.explicitCoor[3] = explicitCoor[2];
            break;
        case Move::U2:
            newCoord.explicitCoor[0] = explicitCoor[2];
            newCoord.explicitCoor[1] = explicitCoor[3];
            newCoord.explicitCoor[2] = explicitCoor[0];
            newCoord.explicitCoor[3] = explicitCoor[1];
            break;
        case Move::U3:
            newCoord.explicitCoor[0] = explicitCoor[1];
            newCoord.explicitCoor[1] = explicitCoor[2];
            newCoord.explicitCoor[2] = explicitCoor[3];
            newCoord.explicitCoor[3] = explicitCoor[0];
            break;
        case Move::D1:
            newCoord.explicitCoor[4] = explicitCoor[5];
            newCoord.explicitCoor[5] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[7];
            newCoord.explicitCoor[7] = explicitCoor[4];
            break;
        case Move::D2:
            newCoord.explicitCoor[4] = explicitCoor[6];
            newCoord.explicitCoor[5] = explicitCoor[7];
            newCoord.explicitCoor[6] = explicitCoor[4];
            newCoord.explicitCoor[7] = explicitCoor[5];
            break;
        case Move::D3:
            newCoord.explicitCoor[4] = explicitCoor[7];
            newCoord.explicitCoor[5] = explicitCoor[4];
            newCoord.explicitCoor[6] = explicitCoor[5];
            newCoord.explicitCoor[7] = explicitCoor[6];
            break;
        case Move::F1:
            newCoord.explicitCoor[0] = explicitCoor[1];
            newCoord.explicitCoor[1] = explicitCoor[5];
            newCoord.explicitCoor[5] = explicitCoor[4];
            newCoord.explicitCoor[4] = explicitCoor[0];
            break;
        case Move::F2:
            newCoord.explicitCoor[0] = explicitCoor[5];
            newCoord.explicitCoor[1] = explicitCoor[4];
            newCoord.explicitCoor[5] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[1];
            break;
        case Move::F3:
            newCoord.explicitCoor[0] = explicitCoor[4];
            newCoord.explicitCoor[1] = explicitCoor[0];
            newCoord.explicitCoor[5] = explicitCoor[1];
            newCoord.explicitCoor[4] = explicitCoor[5];
            break;
        case Move::B1:
            newCoord.explicitCoor[2] = explicitCoor[3];
            newCoord.explicitCoor[3] = explicitCoor[7];
            newCoord.explicitCoor[7] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[2];
            break;
        case Move::B2:
            newCoord.explicitCoor[2] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[6];
            newCoord.explicitCoor[7] = explicitCoor[2];
            newCoord.explicitCoor[6] = explicitCoor[3];
            break;
        case Move::B3:
            newCoord.explicitCoor[2] = explicitCoor[6];
            newCoord.explicitCoor[3] = explicitCoor[2];
            newCoord.explicitCoor[7] = explicitCoor[3];
            newCoord.explicitCoor[6] = explicitCoor[7];
            break;
        case Move::R1:
            newCoord.explicitCoor[0] = explicitCoor[4];
            newCoord.explicitCoor[3] = explicitCoor[0];
            newCoord.explicitCoor[7] = explicitCoor[3];
            newCoord.explicitCoor[4] = explicitCoor[7];
            break;
        case Move::R2:
            newCoord.explicitCoor[0] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[4];
            newCoord.explicitCoor[7] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[3];
            break;
        case Move::R3:
            newCoord.explicitCoor[0] = explicitCoor[3];
            newCoord.explicitCoor[3] = explicitCoor[7];
            newCoord.explicitCoor[7] = explicitCoor[4];
            newCoord.explicitCoor[4] = explicitCoor[0];
            break;
        case Move::L1:
            newCoord.explicitCoor[1] = explicitCoor[2];
            newCoord.explicitCoor[2] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[5];
            newCoord.explicitCoor[5] = explicitCoor[1];
            break;
        case Move::L2:
            newCoord.explicitCoor[1] = explicitCoor[6];
            newCoord.explicitCoor[2] = explicitCoor[5];
            newCoord.explicitCoor[6] = explicitCoor[1];
            newCoord.explicitCoor[5] = explicitCoor[2];
            break;
        case Move::L3:
            newCoord.explicitCoor[1] = explicitCoor[5];
            newCoord.explicitCoor[2] = explicitCoor[1];
            newCoord.explicitCoor[6] = explicitCoor[2];
            newCoord.explicitCoor[5] = explicitCoor[6];
            break;
        default:
            std::cerr << "Fatal error in cornerPermCoordTwo::move: unsupported move." << std::endl;
            break;
    }
    newCoord.defineOrderDiag();
    newCoord.defineNextOrderDiag();
    // std::cout << "final: " << std::endl;
    // newCoord.printExplicitCornPermCoord();
    return newCoord;
}


uint16_t cornerPermCoordTwo::getPureCoord() const {


    uint16_t coord = 0;
    uint16_t factor = 7;

    for (int i = N - 1; i >= 1; --i) {
        int count = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (explicitCoor[j] > explicitCoor[i]) {
                ++count;
            }
        }
        coord += count * factorial(factor);
        factor--;
        // std::cout << "in get pure coord: i: " << i << " " << static_cast<int>(coord) << std::endl;
    }

    return coord;
}

cornerPermCoordTwo cornerPermCoordTwo::fromPureCoord(uint16_t coord) {
    cornerPermCoordTwo result;
    uint16_t temp = coord;

    for (int i = N - 1; i > 0; --i) {
        result.explicitCoor[i] = temp / factorial(i);
        temp = temp % factorial(i);
    }
    return result;
}

cornerPermCoordTwo cornerPermCoordTwo::nextExplicitCoord(){
    cornerPermCoordTwo next = cornerPermCoordTwo::fromNextOrderDiag();

    // std::cout << "next :" << std::endl;
    // next.printExplicitCornPermCoord();
    return next;
}

cornerPermCoordTwo cornerPermCoordTwo::fromNextOrderDiag() {
    cornerPermCoordTwo ret = *this;
    std::vector<int> avalaibleValues = {0,1,2,3,4,5,6,7};
        // print_first(avalaibleValues, 8);

        // std::cout << "vista de ret: antes " << N << std::endl;
        // ret.printExplicitCornPermCoord();
        // ret.printOrderDiagram();
        // ret.defineNextOrderDiag();
        // ret.printNextOrderDiagram();
    // for (int i = N - 1; i >= 0; --i){
    //     int diagIndex = i - 1;
    //     // std::cout << "dentro del for: " << " | i: " << i  << " | size: " << avalaibleValues.size() << " | diagrama(i): " << static_cast<int>(nextOrderDiagram[i]) << std::endl;
    //     int index = avalaibleValues.size() - 1 - nextOrderDiagram[diagIndex];
    //     // std::cout << "index calculado    " << index << std::endl;
        
    //     // print_first(avalaibleValues, 8);
    //     // ret.printExplicitCornPermCoord();
    //     ret.explicitCoor[i] = avalaibleValues[index];
    //     // ret.printExplicitCornPermCoord();
    //     avalaibleValues.erase(avalaibleValues.begin() + index); 
    // }
    for (int i = N - 1; i >= 0; --i) {
        int index;
        if (i == 0) {
            index = 0;
        } else {
            index = avalaibleValues.size() - 1 - nextOrderDiagram[i - 1];
        }

        ret.explicitCoor[i] = avalaibleValues[index];
        avalaibleValues.erase(avalaibleValues.begin() + index);
    }
        // std::cout << "vista de ret: despues" << std::endl;
        // ret.printExplicitCornPermCoord();
        ret.defineOrderDiag();
        ret.defineNextOrderDiag();
        // ret.printOrderDiagram();
        // ret.defineNextOrderDiag();
        // ret.printNextOrderDiagram();
    return ret;
}

void cornerPermCoordTwo::defineOrderDiag(){
    // std::cout << "Defining Order Diagram..." << std::endl;
    // this->printOrderDiagram();
    for (int i = N - 1; i >= 1; --i) {
        int count = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (explicitCoor[j] > explicitCoor[i]) {
                ++count;
            }
            // std::cout << "in define " << i << ' ' << j << std::endl;
        }
        // std::cout << "count "<< count << std::endl; 
        OrderDiagram[i - 1] = count;
    }
    // std::cout << "Defining Order Diagram...fin" << std::endl;
    // this->printOrderDiagram();
}

void cornerPermCoordTwo::oneStep(int BigIndex) {
    uint8_t index = static_cast<uint8_t>(BigIndex);
    // this->printNextOrderDiagram();
        // std::cout << "in oneStep: " << static_cast<int>(index) << " | " << static_cast<int>(nextOrderDiagram[index]) << std::endl;
    if (OrderDiagram[index] < (index + 1)){
        nextOrderDiagram[index] = OrderDiagram[index] + 1;
        // std::cout << "in oneStep2: " << static_cast<int>(index) << " | " << static_cast<int>(nextOrderDiagram[index]) << std::endl;
        return;
    }
    else if (OrderDiagram[index] >= (index + 1)) {
        // std::cout << "ep: " << static_cast<int>(index) << " | " << static_cast<int>(nextOrderDiagram[index]) << std::endl;
        nextOrderDiagram[index] = 0;
        oneStep(index + 1);
    }
}

void cornerPermCoordTwo::defineNextOrderDiag(){
    nextOrderDiagram = OrderDiagram;
    oneStep(0);
    // std::cout << "Defining Next Order Diagram..." << std::endl;
    // this->printNextOrderDiagram();
}

void cornerPermCoordTwo::printMoveTable(){
    cornerPermCoordTwo state;
    // state.printExplicitCornPermCoord();
    for (int i = 0; i < 40320; ++i){
    // for (int i = 0; i < 715; ++i){
        std::cout << state.getPureCoord() << " => ";

        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            // std::cout << moveToString(move) << std::endl;
            cornerPermCoordTwo next = state.move(move);
            // std::cout << "En printmovetable" << std::endl;
            // next.printNextOrderDiagram();
            // next.printExplicitCornPermCoord();
            std::cout << next.getPureCoord();
            if (m != 17) std::cout << " | ";
        }
        std::cout << std::endl;
        state = state.nextExplicitCoord();
        // state.printExplicitCornPermCoord();

    }
}


void cornerPermCoordTwo::moveTableToFile() {
    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + cornerPermTwoMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    cornerPermCoordTwo state;
    for (int i = 0; i < 40320; ++i) {
        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            cornerPermCoordTwo next = state.move(move);
            uint16_t nextCoord = next.getPureCoord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
    std::cout << "Corner Permutation all moves (to solve 2x2) move table done!" << std::endl;
}