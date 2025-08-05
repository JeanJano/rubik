#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s), state(c.get_pure_coord(), e.get_pure_coord(), s.get_pure_coord()) {
        }

void faseOne::pruningTableToFile(){
    faseOne initState{cornerOrientCoord(), edgeOrientCoord(), UDSliceCoord()};
    faseOne::createPruningOne("pruning_table_fase_one.bin", N);
}

long long int faseOne::stateToIndex(){
        return (std::get<2>(state) + (std::get<1>(state) * 495LL) + (std::get<0>(state) * 495 * 2048));
}

faseOne faseOne::moveState(const Move& m) {
    cornerOrientCoord corner = this->corners.move(m);
    edgeOrientCoord edge = this->edges.move(m);
    UDSliceCoord slice = this->slice.move(m);
    faseOne newCoord{corner, edge, slice};
    return newCoord;
}

bool faseOne::createPruningOne(const std::string& filename, std::size_t fileSize) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error: " << filename << " cannot be created \n";
        return false;
    }

    file.seekp(fileSize - 1);
    if (!file) {
        std::cerr << "Error fixing file size.\n";
        return false;
    }

    file.write("", 1);
    if (!file) {
        std::cerr << "Error fixin file size\n";
        return false;
    }

    file.close();
    if (!file) {
        std::cerr << "Error closing file.\n";
        return false;
    }
    std::cout << "fase one table file created!" << std::endl;
    return true;
}