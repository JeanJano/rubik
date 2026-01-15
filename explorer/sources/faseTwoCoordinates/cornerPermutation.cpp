
#include "defs_explorer.hpp"

cornerPermCoord::cornerPermCoord() {
    for(int i = 0; i < N; ++i){
        explicitCoor[i] = i;
    }
    cornerPermCoord::defineOrderDiag();
    cornerPermCoord::defineNextOrderDiag();
}

//extract orientation corner coordinate from cubie representation
cornerPermCoord::cornerPermCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.corners[i].pos;
    }
    // std::cout << "in Cperm const" << std::endl;
    // this->printExplicitCornPermCoord();
    cornerPermCoord::defineOrderDiag();
    cornerPermCoord::defineNextOrderDiag();
}


cornerPermCoord cornerPermCoord::move(const GOneMove& move) const {
    cornerPermCoord newCoord = *this;

    // std::cout << "in move" << std::endl;
    // newCoord.printExplicitCornPermCoord();
    switch (move) {
        case GOneMove::U1:
            newCoord.explicitCoor[0] = explicitCoor[3];
            newCoord.explicitCoor[1] = explicitCoor[0];
            newCoord.explicitCoor[2] = explicitCoor[1];
            newCoord.explicitCoor[3] = explicitCoor[2];
            break;
        case GOneMove::U2:
            newCoord.explicitCoor[0] = explicitCoor[2];
            newCoord.explicitCoor[1] = explicitCoor[3];
            newCoord.explicitCoor[2] = explicitCoor[0];
            newCoord.explicitCoor[3] = explicitCoor[1];
            break;
        case GOneMove::U3:
            newCoord.explicitCoor[0] = explicitCoor[1];
            newCoord.explicitCoor[1] = explicitCoor[2];
            newCoord.explicitCoor[2] = explicitCoor[3];
            newCoord.explicitCoor[3] = explicitCoor[0];
            break;
        case GOneMove::D1:
            newCoord.explicitCoor[4] = explicitCoor[5];
            newCoord.explicitCoor[5] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[7];
            newCoord.explicitCoor[7] = explicitCoor[4];
            break;
        case GOneMove::D2:
            newCoord.explicitCoor[4] = explicitCoor[6];
            newCoord.explicitCoor[5] = explicitCoor[7];
            newCoord.explicitCoor[6] = explicitCoor[4];
            newCoord.explicitCoor[7] = explicitCoor[5];
            break;
        case GOneMove::D3:
            newCoord.explicitCoor[4] = explicitCoor[7];
            newCoord.explicitCoor[5] = explicitCoor[4];
            newCoord.explicitCoor[6] = explicitCoor[5];
            newCoord.explicitCoor[7] = explicitCoor[6];
            break;
        case GOneMove::F2:
            newCoord.explicitCoor[0] = explicitCoor[5];
            newCoord.explicitCoor[1] = explicitCoor[4];
            newCoord.explicitCoor[5] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[1];
            break;
        case GOneMove::B2:
            newCoord.explicitCoor[2] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[6];
            newCoord.explicitCoor[7] = explicitCoor[2];
            newCoord.explicitCoor[6] = explicitCoor[3];
            break;
        case GOneMove::R2:
            newCoord.explicitCoor[0] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[4];
            newCoord.explicitCoor[7] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[3];
            break;
        case GOneMove::L2:
            newCoord.explicitCoor[1] = explicitCoor[6];
            newCoord.explicitCoor[2] = explicitCoor[5];
            newCoord.explicitCoor[6] = explicitCoor[1];
            newCoord.explicitCoor[5] = explicitCoor[2];
            break;
        default:
            std::cerr << "Fatal error in cornerPermCoord::move: unsupported move." << std::endl;
            break;
    }
    newCoord.defineOrderDiag();
    newCoord.defineNextOrderDiag();
    // std::cout << "final: " << std::endl;
    // newCoord.printExplicitCornPermCoord();
    return newCoord;
}


uint16_t cornerPermCoord::get_pure_coord() const {


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

cornerPermCoord cornerPermCoord::from_pure_coord(uint16_t coord) {
    cornerPermCoord result;
    uint16_t temp = coord;

    for (int i = N - 1; i > 0; --i) {
        result.explicitCoor[i] = temp / factorial(i);
        temp = temp % factorial(i);
    }
    return result;
}

cornerPermCoord cornerPermCoord::nextExplicitCoord(){
    cornerPermCoord next = cornerPermCoord::fromNextOrderDiag();

    // std::cout << "next :" << std::endl;
    // next.printExplicitCornPermCoord();
    return next;
}

cornerPermCoord cornerPermCoord::fromNextOrderDiag() {
    cornerPermCoord ret = *this;
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

void cornerPermCoord::defineOrderDiag(){
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

void cornerPermCoord::oneStep(int BigIndex) {
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

void cornerPermCoord::defineNextOrderDiag(){
    nextOrderDiagram = OrderDiagram;
    oneStep(0);
    // std::cout << "Defining Next Order Diagram..." << std::endl;
    // this->printNextOrderDiagram();
}

void cornerPermCoord::printMoveTable(){
    cornerPermCoord state;
    // state.printExplicitCornPermCoord();
    for (int i = 0; i < 40320; ++i){
    // for (int i = 0; i < 715; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 10; ++m) {
            GOneMove move = static_cast<GOneMove>(m);
            // std::cout << moveToString(move) << std::endl;
            cornerPermCoord next = state.move(move);
            // std::cout << "En printmovetable" << std::endl;
            // next.printNextOrderDiagram();
            // next.printExplicitCornPermCoord();
            std::cout << next.get_pure_coord();
            if (m != 9) std::cout << " | ";
        }
        std::cout << std::endl;
        state = state.nextExplicitCoord();
        // state.printExplicitCornPermCoord();

    }
}


void cornerPermCoord::moveTableToFile() {
    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + cornerPermMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    cornerPermCoord state;
    for (int i = 0; i < 40320; ++i) {
        for (int m = 0; m < 10; ++m) {
            GOneMove move = static_cast<GOneMove>(m);
            cornerPermCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
    std::cout << "Corner Permutation move table done!" << std::endl;
}
