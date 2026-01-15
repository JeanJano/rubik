
#include "defs_explorer.hpp"

edgePermCoord::edgePermCoord() {
    for(int i = 0; i < N; ++i){
        explicitCoor[i] = i;
    }
    edgePermCoord::defineOrderDiag();
    edgePermCoord::defineNextOrderDiag();
}

//extract orientation corner coordinate from cubie representation
edgePermCoord::edgePermCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.edges[i].pos;
    }
    // std::cout << "in Eperm const" << std::endl;
    // this->printExplicitEdgePermCoord();
    edgePermCoord::defineOrderDiag();
    edgePermCoord::defineNextOrderDiag();
}


edgePermCoord edgePermCoord::move(const GOneMove& move) const {
    edgePermCoord newCoord = *this;

    // std::cout << "in GOneMove" << std::endl;
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
            newCoord.explicitCoor[1] = explicitCoor[5];
            newCoord.explicitCoor[5] = explicitCoor[1];
            break;
        case GOneMove::B2:
            newCoord.explicitCoor[3] = explicitCoor[7];
            newCoord.explicitCoor[7] = explicitCoor[3];
            break;
        case GOneMove::R2:
            newCoord.explicitCoor[0] = explicitCoor[4];
            newCoord.explicitCoor[4] = explicitCoor[0];
            break;
        case GOneMove::L2:
            newCoord.explicitCoor[2] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[2];
            break;
        default:
            std::cerr << "Fatal error in edgePermCoord::GOneMove: unsupported GOneMove." << std::endl;
            break;
    }
    newCoord.defineOrderDiag();
    newCoord.defineNextOrderDiag();
    // std::cout << "final: " << std::endl;
    // newCoord.printExplicitCornPermCoord();
    return newCoord;
}


uint16_t edgePermCoord::get_pure_coord() const {


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
    }
    // std::cout << "pure coord: " << coord << std::endl;
    return coord;
}

edgePermCoord edgePermCoord::from_pure_coord(uint16_t coord) {
    edgePermCoord result;
    uint16_t temp = coord;

    for (int i = N - 1; i > 0; --i) {
        result.explicitCoor[i] = temp / factorial(i);
        temp = temp % factorial(i);
    }
    return result;
}

edgePermCoord edgePermCoord::nextExplicitCoord(){
    edgePermCoord next = edgePermCoord::fromNextOrderDiag();

    // std::cout << "next :" << std::endl;
    // next.printExplicitEdgePermCoord();
    return next;
}

edgePermCoord edgePermCoord::fromNextOrderDiag() {
    edgePermCoord ret = *this;
    std::vector<int> avalaibleValues = {0,1,2,3,4,5,6,7};
        // print_first(avalaibleValues, 8);

        // std::cout << "vista de ret: antes " << N << std::endl;
        // ret.printExplicitEdgePermCoord();
        // ret.printOrderDiagram();
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
        ret.defineOrderDiag();
        ret.defineNextOrderDiag();
        // std::cout << "vista de ret: despues" << std::endl;
        // ret.printExplicitEdgePermCoord();
        // ret.printOrderDiagram();
        // ret.printNextOrderDiagram();
    return ret;
}

void edgePermCoord::defineOrderDiag(){
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

void edgePermCoord::oneStep(int BigIndex) {
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

void edgePermCoord::defineNextOrderDiag(){
    nextOrderDiagram = OrderDiagram;
    oneStep(0);
    // std::cout << "Defining Next Order Diagram..." << std::endl;
    // this->printNextOrderDiagram();
}

void edgePermCoord::printMoveTable(){
    edgePermCoord state;
    for (int i = 0; i < 40320; ++i){
    // for (int i = 0; i < 515; ++i){
        // std::cout << "empezando  " << std::endl;
        // state.printExplicitEdgePermCoord();
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 10; ++m) {
            GOneMove move = static_cast<GOneMove>(m);
            // std::cout << GOneMoveToString(move) << std::endl;
            edgePermCoord next = state.move(move);
            // std::cout << "En printGOneMovetable" << std::endl;
            // next.printNextOrderDiagram();
            // next.printExplicitCornPermCoord();
            std::cout << next.get_pure_coord();
            if (m != 9) std::cout << " | ";
        }
        std::cout << std::endl;
        state = state.nextExplicitCoord();
        // std::cout << "terminando  " << std::endl;
        // state.printExplicitEdgePermCoord();

    }
}


void edgePermCoord::moveTableToFile() {
    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + edgePermMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    edgePermCoord state;
    for (int i = 0; i < 40320; ++i) {
        for (int m = 0; m < 10; ++m) {
            GOneMove move = static_cast<GOneMove>(m);
            edgePermCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
    std::cout << "Edge permutation move table done!" << std::endl;
}