#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s), state(c.get_pure_coord(), e.get_pure_coord(), s.get_pure_coord()) {
        }

void faseOne::pruningTableToFile(){
    std::queue<long int> BFS;
    BFS.push(0);
    if(faseOne::createPruningOne(pruningTableFilename, N)){

    }
    else
        std::cout << "Error creating fase one pruning table" << std::endl;
}

long int faseOne::stateToIndex(){
        return (std::get<2>(state) + (std::get<1>(state) * 495L) + (std::get<0>(state) * 495 * 2048));
}

long int stateToIndex(int cornerCoord, int edgeCoord,, int UDSliceCoord) {
        return (UDSliceCoord + (edgeCoord * 495L) + (cornerCoord * 495 * 2048));
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

bool faseOne::writePruningOne(std::size_t index, uint8_t value) {
    if (index >= N) {
        std::cerr << "Error: Index out of bounds: " << index << std::endl;
        return false;
    }
    std::fstream file(pruningTableFilename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << pruningTableFilename << std::endl;
        return false;
    }
    file.seekp(index);
    if (!file) {
        std::cerr << "Error: Failed to seek to index: " << index << std::endl;
        return false;
    }
    file.put(static_cast<char>(value));
    if (!file) {
        std::cerr << "Error: Failed to write at index: " << index << std::endl;
        return false;
    }
    file.close();
    return true;
}

uint8_t faseOne::readPruningOne(std::size_t index) {
    std::ifstream file(pruningTableFilename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << pruningTableFilename << std::endl;
        return 255;
    }
    if (index >= N) {
        std::cerr << "Error: Index out of bounds: " << index << std::endl;
        return 255;
    }
    file.seekg(index);
    if (!file) {
        std::cerr << "Error: Failed to seek to index: " << index << std::endl;
        return 255;
    }
    char byte;
    file.get(byte);
    if (!file) {
        std::cerr << "Error: Failed to read byte at index: " << index << std::endl;
        return 255;
    }
    return static_cast<uint8_t>(static_cast<unsigned char>(byte));
}