
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


cornerOrientCoord cornerOrientCoord::move(const Move& move) const {
    cornerOrientCoord newCoord = *this;

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
            newCoord.explicitCoor[0] = (explicitCoor[1] + 1) % 3;
            newCoord.explicitCoor[1] = (explicitCoor[5] + 2) % 3;
            newCoord.explicitCoor[5] = (explicitCoor[4] + 1) % 3;
            newCoord.explicitCoor[4] = (explicitCoor[0] + 2) % 3;
            break;
        case Move::F2:
            newCoord.explicitCoor[0] = explicitCoor[5];
            newCoord.explicitCoor[1] = explicitCoor[4];
            newCoord.explicitCoor[5] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[1];
            break;
        case Move::F3:
            newCoord.explicitCoor[0] = (explicitCoor[4] + 1) % 3;
            newCoord.explicitCoor[1] = (explicitCoor[0] + 2) % 3;
            newCoord.explicitCoor[5] = (explicitCoor[1] + 1) % 3;
            newCoord.explicitCoor[4] = (explicitCoor[5] + 2) % 3;
            break;
        case Move::B1:
            newCoord.explicitCoor[2] = (explicitCoor[3] + 1) % 3;
            newCoord.explicitCoor[3] = (explicitCoor[7] + 2) % 3;
            newCoord.explicitCoor[7] = (explicitCoor[6] + 1) % 3;
            newCoord.explicitCoor[6] = (explicitCoor[2] + 2) % 3;
            break;
        case Move::B2:
            newCoord.explicitCoor[2] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[6];
            newCoord.explicitCoor[7] = explicitCoor[2];
            newCoord.explicitCoor[6] = explicitCoor[3];
            break;
        case Move::B3:
            newCoord.explicitCoor[2] = (explicitCoor[6] + 1) % 3;
            newCoord.explicitCoor[3] = (explicitCoor[2] + 2) % 3;
            newCoord.explicitCoor[7] = (explicitCoor[3] + 1) % 3;
            newCoord.explicitCoor[6] = (explicitCoor[7] + 2) % 3;
            break;
        case Move::R1:
            newCoord.explicitCoor[0] = (explicitCoor[4] + 2) % 3;
            newCoord.explicitCoor[3] = (explicitCoor[0] + 1) % 3;
            newCoord.explicitCoor[7] = (explicitCoor[3] + 2) % 3;
            newCoord.explicitCoor[4] = (explicitCoor[7] + 1) % 3;
            break;
        case Move::R2:
            newCoord.explicitCoor[0] = explicitCoor[7];
            newCoord.explicitCoor[3] = explicitCoor[4];
            newCoord.explicitCoor[7] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[3];
            break;
        case Move::R3:
            newCoord.explicitCoor[0] = (explicitCoor[3] + 2) % 3;
            newCoord.explicitCoor[3] = (explicitCoor[7] + 1) % 3;
            newCoord.explicitCoor[7] = (explicitCoor[4] + 2) % 3;
            newCoord.explicitCoor[4] = (explicitCoor[0] + 1) % 3;
            break;
        case Move::L1:
            newCoord.explicitCoor[1] = (explicitCoor[2] + 1) % 3;
            newCoord.explicitCoor[2] = (explicitCoor[6] + 2) % 3;
            newCoord.explicitCoor[6] = (explicitCoor[5] + 1) % 3;
            newCoord.explicitCoor[5] = (explicitCoor[1] + 2) % 3;
            break;
        case Move::L2:
            newCoord.explicitCoor[1] = explicitCoor[6];
            newCoord.explicitCoor[2] = explicitCoor[5];
            newCoord.explicitCoor[6] = explicitCoor[1];
            newCoord.explicitCoor[5] = explicitCoor[2];
            break;
        case Move::L3:
            newCoord.explicitCoor[1] = (explicitCoor[5] + 1) % 3;
            newCoord.explicitCoor[2] = (explicitCoor[1] + 2) % 3;
            newCoord.explicitCoor[6] = (explicitCoor[2] + 1) % 3;
            newCoord.explicitCoor[5] = (explicitCoor[6] + 2) % 3;
            break;
        default:
            std::cerr << "Fatal error in cornerOrientCoord::move: unsupported move." << std::endl;
            break;
    }
    return newCoord;
}

uint16_t cornerOrientCoord::get_pure_coord() const {
    uint16_t coord = 0;
    //check the counter
    for (int i = 0; i < 7; ++i) {
        coord = coord * 3 + static_cast<uint16_t>(this->explicitCoor[i]);
    }
    return coord;
}

cornerOrientCoord cornerOrientCoord::nextExplicitCoord(){
    cornerOrientCoord next = *this;
    for (int i = N - 2; i >= 0; --i) {
        if (++next.explicitCoor[i] < 3) {
            break;
        } else {
            next.explicitCoor[i] = 0;
        }
    }
    int sum = 0;
    for (int i = 0; i < N - 1; ++i) {
        sum += next.explicitCoor[i];
    }
    next.explicitCoor[N - 1] = (3 - (sum % 3)) % 3;
    return next;
}

void cornerOrientCoord::print_move_table(){
    cornerOrientCoord state;
    for (int i = 0; i < 2187; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            cornerOrientCoord next = state.move(move);
            std::cout << next.get_pure_coord();
            if (m != 17) std::cout << " | ";
        }

        std::cout << std::endl;
        state = state.nextExplicitCoord();
    }
}

cornerOrientCoord cornerOrientCoord::from_pure_coord(uint16_t coord) {
    cornerOrientCoord result;
    int sum = 0;
    for (int i = N - 2; i >= 0; --i) {
        result.explicitCoor[i] = coord % 3;
        sum += result.explicitCoor[i];
        coord /= 3;
    }
    result.explicitCoor[N - 1] = (3 - (sum % 3)) % 3;
    return result;
}

void cornerOrientCoord::moveTableToFile() {
    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + cornerOriMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    cornerOrientCoord state;
    for (int i = 0; i < 2187; ++i) {
        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            cornerOrientCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
}
