#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

edgeOrientCoord::edgeOrientCoord() {
    explicitCoor.fill(0);
}

//extract orientation edge coordinate from cubie representation
edgeOrientCoord::edgeOrientCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = cube.edges[i].ori;
    }
}

edgeOrientCoord edgeOrientCoord::move(Move move) {
    edgeOrientCoord newCoord = *this;

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
            newCoord.explicitCoor[1] = (explicitCoor[9] + 1) % 2;
            newCoord.explicitCoor[9] = (explicitCoor[5] + 1) % 2;
            newCoord.explicitCoor[5] = (explicitCoor[8] + 1) % 2;
            newCoord.explicitCoor[8] = (explicitCoor[1] + 1) % 2;
            break;
        case Move::F2:
            newCoord.explicitCoor[1] = explicitCoor[5];
            newCoord.explicitCoor[9] = explicitCoor[8];
            newCoord.explicitCoor[5] = explicitCoor[1];
            newCoord.explicitCoor[8] = explicitCoor[9];
            break;
        case Move::F3:
            newCoord.explicitCoor[1] = (explicitCoor[8] + 1) % 2;
            newCoord.explicitCoor[9] = (explicitCoor[1] + 1) % 2;
            newCoord.explicitCoor[5] = (explicitCoor[9] + 1) % 2;
            newCoord.explicitCoor[8] = (explicitCoor[5] + 1) % 2;
            break;
        case Move::B1:
            newCoord.explicitCoor[3] = (explicitCoor[11] + 1) % 2;
            newCoord.explicitCoor[11] = (explicitCoor[7] + 1) % 2;
            newCoord.explicitCoor[7] = (explicitCoor[10] + 1) % 2;
            newCoord.explicitCoor[10] = (explicitCoor[3] + 1) % 2;
            break;
        case Move::B2:
            newCoord.explicitCoor[3] = explicitCoor[7];
            newCoord.explicitCoor[11] = explicitCoor[10];
            newCoord.explicitCoor[7] = explicitCoor[3];
            newCoord.explicitCoor[10] = explicitCoor[11];
            break;
        case Move::B3:
            newCoord.explicitCoor[3] = (explicitCoor[10] + 1) % 2;
            newCoord.explicitCoor[11] = (explicitCoor[3] + 1) % 2;
            newCoord.explicitCoor[7] = (explicitCoor[11] + 1) % 2;
            newCoord.explicitCoor[10] = (explicitCoor[7] + 1) % 2;
            break;
        case Move::R1:
            newCoord.explicitCoor[0] = explicitCoor[8];
            newCoord.explicitCoor[8] = explicitCoor[4];
            newCoord.explicitCoor[4] = explicitCoor[11];
            newCoord.explicitCoor[11] = explicitCoor[0];
            break;
        case Move::R2:
            newCoord.explicitCoor[0] = explicitCoor[4];
            newCoord.explicitCoor[8] = explicitCoor[11];
            newCoord.explicitCoor[4] = explicitCoor[0];
            newCoord.explicitCoor[11] = explicitCoor[8];
            break;
        case Move::R3:
            newCoord.explicitCoor[0] = explicitCoor[11];
            newCoord.explicitCoor[8] = explicitCoor[0];
            newCoord.explicitCoor[4] = explicitCoor[8];
            newCoord.explicitCoor[11] = explicitCoor[4];
            break;
        case Move::L1:
            newCoord.explicitCoor[2] = explicitCoor[10];
            newCoord.explicitCoor[10] = explicitCoor[6];
            newCoord.explicitCoor[6] = explicitCoor[9];
            newCoord.explicitCoor[9] = explicitCoor[2];
            break;
        case Move::L2:
            newCoord.explicitCoor[2] = explicitCoor[6];
            newCoord.explicitCoor[10] = explicitCoor[9];
            newCoord.explicitCoor[6] = explicitCoor[2];
            newCoord.explicitCoor[9] = explicitCoor[10];
            break;
        case Move::L3:
            newCoord.explicitCoor[2] = explicitCoor[9];
            newCoord.explicitCoor[10] = explicitCoor[2];
            newCoord.explicitCoor[6] = explicitCoor[10];
            newCoord.explicitCoor[9] = explicitCoor[6];
            break;
        default:
            std::cerr << "Fatal error in edgeOrientCoord::move: unsupported move." << std::endl;
            break;
    }
    return newCoord;
}

uint16_t edgeOrientCoord::get_pure_coord() const {
    uint16_t coord = 0;
    for (int i = 0; i < N - 1; ++i) {
        coord = coord * 2 + static_cast<uint16_t>(this->explicitCoor[i]);
    }
    return coord;
}

edgeOrientCoord edgeOrientCoord::nextExplicitCoord(){
    edgeOrientCoord next = *this;
    for (int i = N - 2; i >= 0; --i) {
        if (++next.explicitCoor[i] < 2) {
            break;
        } else {
            next.explicitCoor[i] = 0;
        }
    }
    int sum = 0;
    for (int i = 0; i < N - 1; ++i) {
        sum += next.explicitCoor[i];
    }
    next.explicitCoor[N - 1] = (2 - (sum % 2)) % 2;
    return next;
}

void edgeOrientCoord::print_move_table(){
    edgeOrientCoord state;
    for (int i = 0; i < 2048; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            edgeOrientCoord next = state.move(move);
            std::cout << next.get_pure_coord();
            if (m != 17) std::cout << " | ";
        }

        std::cout << std::endl;
        state = state.nextExplicitCoord();
    }
}

edgeOrientCoord edgeOrientCoord::from_pure_coord(uint16_t coord) {
    edgeOrientCoord result;
    int sum = 0;
    for (int i = N - 2; i >= 0; --i) {
        result.explicitCoor[i] = coord % 2;
        sum += result.explicitCoor[i];
        coord /= 2;
    }
    result.explicitCoor[N - 1] = (2 - (sum % 2)) % 2;
    return result;
}

void edgeOrientCoord::move_table_to_file() {

    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + edgeOriMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    edgeOrientCoord state;
    for (int i = 0; i < 2048; ++i) {
        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            edgeOrientCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
}