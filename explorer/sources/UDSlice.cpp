#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

UDSliceOrientCoord::UDSliceOrientCoord() {
    explicitCoor.fill(0);
    for (int i = N - 4; i < N; ++i) {
        explicitCoor[i] = 1;  // Cambia los últimos 4 a unos
    }
}

//extract orientation UDSlice coordinate from cubie representation
UDSliceOrientCoord::UDSliceOrientCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = (N-4 <= cube.edges[i] && cube.edges[i] < N)? 1 : 0;
    }
}

UDSliceOrientCoord UDSliceOrientCoord::move(Move move) {
    UDSliceOrientCoord newCoord = *this;

    switch (move) {
        case Move::U1:
            newCoord.explicitCoor[0] = (explicitCoor[3] == 1)? 1 : 0;
            newCoord.explicitCoor[1] = (explicitCoor[0] == 1)? 1 : 0;
            newCoord.explicitCoor[2] = (explicitCoor[1] == 1)? 1 : 0;
            newCoord.explicitCoor[3] = (explicitCoor[2] == 1)? 1 : 0;
            break;
        case Move::U2:
            newCoord.explicitCoor[0] = (explicitCoor[2] == 1)? 1 : 0;
            newCoord.explicitCoor[1] = (explicitCoor[3] == 1)? 1 : 0;
            newCoord.explicitCoor[2] = (explicitCoor[0] == 1)? 1 : 0;
            newCoord.explicitCoor[3] = (explicitCoor[1] == 1)? 1 : 0;
            break;
        case Move::U3:
            newCoord.explicitCoor[0] = (explicitCoor[1] == 1)? 1 : 0;
            newCoord.explicitCoor[1] = (explicitCoor[2] == 1)? 1 : 0;
            newCoord.explicitCoor[2] = (explicitCoor[3] == 1)? 1 : 0;
            newCoord.explicitCoor[3] = (explicitCoor[0] == 1)? 1 : 0;
            break;
        case Move::D1:
            newCoord.explicitCoor[4] = (explicitCoor[5] == 1)? 1 : 0;;
            newCoord.explicitCoor[5] = (explicitCoor[6] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[7] == 1)? 1 : 0;;
            newCoord.explicitCoor[7] = (explicitCoor[4] == 1)? 1 : 0;;
            break;
        case Move::D2:
            newCoord.explicitCoor[4] = (explicitCoor[6] == 1)? 1 : 0;;
            newCoord.explicitCoor[5] = (explicitCoor[7] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[4] == 1)? 1 : 0;;
            newCoord.explicitCoor[7] = (explicitCoor[5] == 1)? 1 : 0;;
            break;
        case Move::D3:
            newCoord.explicitCoor[4] = (explicitCoor[7] == 1)? 1 : 0;;
            newCoord.explicitCoor[5] = (explicitCoor[4] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[5] == 1)? 1 : 0;;
            newCoord.explicitCoor[7] = (explicitCoor[6] == 1)? 1 : 0;;
            break;
        case Move::F1:
            newCoord.explicitCoor[1] = (explicitCoor[9] == 1)? 1 : 0;
            newCoord.explicitCoor[9] = (explicitCoor[5] == 1)? 1 : 0;
            newCoord.explicitCoor[5] = (explicitCoor[8] == 1)? 1 : 0;
            newCoord.explicitCoor[8] = (explicitCoor[1] == 1)? 1 : 0;
            break;
        case Move::F2:
            newCoord.explicitCoor[1] = (explicitCoor[5] == 1)? 1 : 0;;
            newCoord.explicitCoor[9] = (explicitCoor[8] == 1)? 1 : 0;;
            newCoord.explicitCoor[5] = (explicitCoor[1] == 1)? 1 : 0;;
            newCoord.explicitCoor[8] = (explicitCoor[9] == 1)? 1 : 0;;
            break;
        case Move::F3:
            newCoord.explicitCoor[1] = (explicitCoor[8] == 1)? 1 : 0;
            newCoord.explicitCoor[9] = (explicitCoor[1] == 1)? 1 : 0;
            newCoord.explicitCoor[5] = (explicitCoor[9] == 1)? 1 : 0;
            newCoord.explicitCoor[8] = (explicitCoor[5] == 1)? 1 : 0;
            break;
        case Move::B1:
            newCoord.explicitCoor[3] = (explicitCoor[11] == 1)? 1 : 0;
            newCoord.explicitCoor[11] = (explicitCoor[7] == 1)? 1 : 0;
            newCoord.explicitCoor[7] = (explicitCoor[10] == 1)? 1 : 0;
            newCoord.explicitCoor[10] = (explicitCoor[3] == 1)? 1 : 0;
            break;
        case Move::B2:
            newCoord.explicitCoor[3] = (explicitCoor[7] == 1)? 1 : 0;;
            newCoord.explicitCoor[11] = (explicitCoor[10] == 1)? 1 : 0;;
            newCoord.explicitCoor[7] = (explicitCoor[3] == 1)? 1 : 0;;
            newCoord.explicitCoor[10] = (explicitCoor[11] == 1)? 1 : 0;;
            break;
        case Move::B3:
            newCoord.explicitCoor[3] = (explicitCoor[10] == 1)? 1 : 0;;
            newCoord.explicitCoor[11] = (explicitCoor[3] == 1)? 1 : 0;;
            newCoord.explicitCoor[7] = (explicitCoor[11] == 1)? 1 : 0;;
            newCoord.explicitCoor[10] = (explicitCoor[7] == 1)? 1 : 0;;
            break;
        case Move::R1:
            newCoord.explicitCoor[0] = (explicitCoor[8] == 1)? 1 : 0;;
            newCoord.explicitCoor[8] = (explicitCoor[4] == 1)? 1 : 0;;
            newCoord.explicitCoor[4] = (explicitCoor[11] == 1)? 1 : 0;;
            newCoord.explicitCoor[11] = (explicitCoor[0] == 1)? 1 : 0;;
            break;
        case Move::R2:
            newCoord.explicitCoor[0] = (explicitCoor[4] == 1)? 1 : 0;;
            newCoord.explicitCoor[8] = (explicitCoor[11] == 1)? 1 : 0;;
            newCoord.explicitCoor[4] = (explicitCoor[0] == 1)? 1 : 0;;
            newCoord.explicitCoor[11] = (explicitCoor[8] == 1)? 1 : 0;;
            break;
        case Move::R3:
            newCoord.explicitCoor[0] = (explicitCoor[11] == 1)? 1 : 0;;
            newCoord.explicitCoor[8] = (explicitCoor[0] == 1)? 1 : 0;;
            newCoord.explicitCoor[4] = (explicitCoor[8] == 1)? 1 : 0;;
            newCoord.explicitCoor[11] = (explicitCoor[4] == 1)? 1 : 0;;
            break;
        case Move::L1:
            newCoord.explicitCoor[2] = (explicitCoor[10] == 1)? 1 : 0;;
            newCoord.explicitCoor[10] = (explicitCoor[6] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[9] == 1)? 1 : 0;;
            newCoord.explicitCoor[9] = (explicitCoor[2] == 1)? 1 : 0;;
            break;
        case Move::L2:
            newCoord.explicitCoor[2] = (explicitCoor[6] == 1)? 1 : 0;;
            newCoord.explicitCoor[10] = (explicitCoor[9] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[2] == 1)? 1 : 0;;
            newCoord.explicitCoor[9] = (explicitCoor[10] == 1)? 1 : 0;;
            break;
        case Move::L3:
            newCoord.explicitCoor[2] = (explicitCoor[9] == 1)? 1 : 0;;
            newCoord.explicitCoor[10] = (explicitCoor[2] == 1)? 1 : 0;;
            newCoord.explicitCoor[6] = (explicitCoor[10] == 1)? 1 : 0;;
            newCoord.explicitCoor[9] = (explicitCoor[6] == 1)? 1 : 0;;
            break;
        default:
            std::cerr << "Fatal error in UDSliceOrientCoord::move: unsupported move." << std::endl;
            break;
    }
    return newCoord;
}

int binomial(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    int res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

uint16_t UDSliceOrientCoord::get_pure_coord() const {
    int coord = 0;
    int k = -1;

    for (int i = 0; i < N; ++i) {
        if (explicitCoor[i] == 1) {
            k++;
        } else {
            coord += binomial(i, k);
        }
    }

    return coord;
}

UDSliceOrientCoord UDSliceOrientCoord::nextExplicitCoord(){
    UDSliceOrientCoord next = *this;
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

void UDSliceOrientCoord::print_move_table(){
    UDSliceOrientCoord state;
    for (int i = 0; i < 2048; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            UDSliceOrientCoord next = state.move(move);
            std::cout << next.get_pure_coord();
            if (m != 17) std::cout << " | ";
        }

        std::cout << std::endl;
        state = state.nextExplicitCoord();
    }
}

UDSliceOrientCoord UDSliceOrientCoord::from_pure_coord(uint16_t coord) {
    UDSliceOrientCoord result;
    int sum = 0;
    for (int i = N - 2; i >= 0; --i) {
        result.explicitCoor[i] = coord % 2;
        sum += result.explicitCoor[i];
        coord /= 2;
    }
    result.explicitCoor[N - 1] = (2 - (sum % 2)) % 2;
    return result;
}

void UDSliceOrientCoord::move_table_to_file() {
    const std::string folder = "move_tables";

    // Crear la carpeta si no existe
    std::error_code ec; // para no lanzar excepciones
    if (!std::filesystem::exists(folder)) {
        if (!std::filesystem::create_directories(folder, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << folder << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = folder + "/UDSliceOriMoves.bin";
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    UDSliceOrientCoord state;
    for (int i = 0; i < 2048; ++i) {
        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            UDSliceOrientCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
}