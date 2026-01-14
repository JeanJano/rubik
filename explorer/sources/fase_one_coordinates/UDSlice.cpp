
#include "defs_explorer.hpp"

UDSliceCoord::UDSliceCoord() {
    explicitCoor.fill(0);
    for (int i = N - 4; i < N; ++i) {
        explicitCoor[i] = 1;  // Cambia los últimos 4 a unos
    }
}

//extract orientation UDSlice coordinate from cubie representation
UDSliceCoord::UDSliceCoord(const cubeCubie& cube) {
    for (int i = 0; i < N; ++i) {
        explicitCoor[i] = (N-4 <= cube.edges[i].pos && cube.edges[i].pos < N)? 1 : 0;
    }
}

UDSliceCoord UDSliceCoord::move(const Move& move) const {
    UDSliceCoord newCoord = *this;

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
            std::cerr << "Fatal error in UDSliceCoord::move: unsupported move." << std::endl;
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

uint16_t UDSliceCoord::get_pure_coord() const {
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

UDSliceCoord UDSliceCoord::nextExplicitCoord(int index, int count){
    UDSliceCoord coord = *this;
    UDSliceCoord next = coord;

    for (int i = index; i < N; ++i){
        if (coord.explicitCoor[i] == 0)
            ;
        else if (coord.explicitCoor[i] == 1 && i > index){
            int curr = count;
            next.explicitCoor[i] = 0;
            next.explicitCoor[i - 1] = 1;
            if (i - 1 == index)
                return next;
            else {
                for (int j = i - 2; j >= 0; --j){
                    if (curr > 0){
                        next.explicitCoor[j] = 1;
                        --curr;
                    }
                    else if (curr == 0){
                        next.explicitCoor[j] = 0;
                    }
                }
                return next;
            }
        }
        else if (coord.explicitCoor[i] == 1 && i == index){
            return (next.nextExplicitCoord(i + 1, count + 1));
        }
    }
    return next;
}

UDSliceCoord UDSliceCoord::nextExplicitCoord(){
    UDSliceCoord next = *this;
    return next.nextExplicitCoord(0,0);
}

void UDSliceCoord::print_move_table(){
    UDSliceCoord state;
    for (int i = 0; i < 495; ++i){
        std::cout << state.get_pure_coord() << " => ";

        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            UDSliceCoord next = state.move(move);
            std::cout << next.get_pure_coord();
            if (m != 17) std::cout << " | ";
        }

        std::cout << std::endl;
        state = state.nextExplicitCoord();
    }
}

UDSliceCoord UDSliceCoord::from_pure_coord(const uint16_t& coord) {
    if (coord > 494) {
        throw std::invalid_argument("coord must be between 0 y 494. received value: ");
    }
    UDSliceCoord result;
    int curr = coord;
    int ones = 3;
    for (int i = N - 1; i >= 0; --i){
        if (ones < 0){
            result.explicitCoor[i] = 0;
        }
        else if (ones >= 0 && binomial(i, ones) > curr){
            result.explicitCoor[i] = 1;
            --ones;
        }
        else if (ones >= 0 && binomial(i, ones) < curr){
            result.explicitCoor[i] = 0;
            curr -= binomial(i, ones);
        }
        else if (ones >= 0 && binomial(i, ones) == curr){
            result.explicitCoor[i] = 0;
            curr -= binomial(i, ones);
            --i;
            result.explicitCoor[i] = 1;
            --ones;
        }
    }
    return result;
}

void UDSliceCoord::moveTableToFile() {
    std::error_code ec;
    if (!std::filesystem::exists(movesFoldername)) {
        if (!std::filesystem::create_directories(movesFoldername, ec)) {
            std::cerr << "Error: no se pudo crear la carpeta '" << movesFoldername << "': " << ec.message() << std::endl;
            return;
        }
    }

    std::string filepath = movesFoldername + UDSliceMoveTableFilename;
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura: " << filepath << std::endl;
        return;
    }

    UDSliceCoord state;
    for (int i = 0; i < 495; ++i) {
        for (int m = 0; m < 18; ++m) {
            Move move = static_cast<Move>(m);
            UDSliceCoord next = state.move(move);
            uint16_t nextCoord = next.get_pure_coord();
            out.write(reinterpret_cast<const char*>(&nextCoord), sizeof(uint16_t));
        }
        state = state.nextExplicitCoord();
    }

    out.close();
}
