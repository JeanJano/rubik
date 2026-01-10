cornerPermCoord::cornerPermCoord() {
    explicitCoor.fill(0);
    OrderDiagram.fill(0);
}

//extract orientation corner coordinate from cubie representation
cornerPermCoord::cornerPermCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.corners[i].pos;
    }
    cornerPermCoord::defineOrderDiag();
}


cornerPermCoord cornerPermCoord::move(const GOneMove& move) const {
    cornerPermCoord newCoord = *this;

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
    cornerPermCoord::defineNextOrderDiag();
    cornerPermCoord next = cornerPermCoord::fromNextOrderDiag();
    return next;
}

cornerPermCoord cornerPermCoord::fromNextOrderDiag() {
    cornerPermCoord ret;
    std::vector<int> avalaibleValues = {0,1,2,3,4,5,6,7};
    for (int i = N - 1; i > 0: --i){
        index = avalaibleValues.size() - nextOrderDiagram[i]
        ret.explicitCoor[i] = avalaibleValues[index];
        avalaibleValues.erase(avalaibleValues.begin() + index); 
    }
    return ret;
}

void cornerPermCoord::defineOrderDiag(){
    for (int i = N - 1; i >= 1; --i) {
        int count = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (explicitCoor[j] > explicitCoor[i]) {
                ++count;
            }
        }
        OrderDiagram[i - 1] = count;
    }
}

void cornerPermCoord::defineNextOrderDiag(){
    oneStep(0);
}

void oneStep(int index) {
    if (OrderDiagram[index] < (index + 1)){
        OrderDiagram[index]++;
        if(OrderDiagram[index] == N - 1) //revisar limites
            return;
    }
    else if {
        OrderDiagram[index] = 0;
        oneStep(index + 1)
    }
}

void cornerPermCoord::print_move_table(){
    cornerPermCoord state;
    for (int i = 0; i < 2187; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 10; ++m) {
            Move move = static_cast<GOneMove>(m);
            cornerPermCoord next = state.move(move);
            std::cout << next.get_pure_coord();
            if (m != 17) std::cout << " | ";
        }

        std::cout << std::endl;
        state = state.nextExplicitCoord();
    }
}



void cornerPermCoord::moveTableToFile() {
    // std::error_code ec;
    // if (!std::filesystem::exists(movesFoldername)) {
    //     if (!std::filesystem::create_directories(movesFoldername, ec)) {
    //         std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
    //         return;
    //     }
    // }

    // std::string filepath = movesFoldername + cornerOriMoveTableFilename;
    // std::ofstream out(filepath, std::ios::binary);
    // if (!out) {
    //     std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
    //     return;
    // }

    // cornerPermCoord state;
    // for (int i = 0; i < 2187; ++i) {
    //     for (int m = 0; m < 18; ++m) {
    //         Move move = static_cast<Move>(m);
    //         cornerPermCoord next = state.move(move);
    //         uint16_t nextCoord = next.get_pure_coord();
    //         out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
    //     }
    //     state = state.nextExplicitCoord();
    // }

    // out.close();
}

inline uint16_t factorial(uint6_t n){
    return (n <= 1) ? 1 : n * factorial(n - 1);
}