
#include "defs_explorer.hpp"

// faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
//         : corners(c), edges(e), slice(s), COSstate(s.get_pure_coord(), c.get_pure_coord(), 0),
//         EOSstate(s.get_pure_coord(), e.get_pure_coord(), 0) {
// }

void faseOne::DoPruningTables(){
    namespace fs = std::filesystem;
    if (!fs::exists(pruningFoldername + pruningCOSFilename)) {
        if (!faseOne::CreatePruning(pruningCOSFilename, NC)) {
            std::cout << "Error creating COS pruning table" << std::endl;
            return;
        }
    }
    if (!fs::exists(pruningFoldername + pruningEOSFilename)) {
        if (!faseOne::CreatePruning(pruningEOSFilename, NE)) {
            std::cout << "Error creating EOS pruning table" << std::endl;
            return;
        }
    }
    if(true){
    // if(faseOne::readPruning(pruningCOSFilename, 1) != 0){
        if (!faseOne::fillTable(pruningCOSFilename)) {
            std::cout << "Error filling fase one COS pruning table" << std::endl;
            return;
        } 
    }
    if(true){
    // if(faseOne::readPruning(pruningEOSFilename, 1) != 0){
        if (!faseOne::fillTable(pruningEOSFilename)) {
            std::cout << "Error filling fase one EOS pruning table" << std::endl;
            return;
        }
    }
}

bool faseOne::fillTable(const std::string& filename) {
    // if (filename == pruningCOSFilename) std::cout << "im in COS" << std::endl;
    // else if (filename == pruningEOSFilename) std::cout << "im in EOS" << std::endl;
    std::queue<std::tuple<int, int, int>> BFS;
    std::tuple<int,int,int> initState = std::make_tuple(0,0,0);
    BFS.push(initState);
    // int p =0;
    // while(!BFS.empty() && p < 21){
    while(!BFS.empty()){
        auto currentState = BFS.front();
            // std::cout << "acotando fillTable BFS.front " << std::get<0>(currentState) << " " << std::get<1>(currentState) << " " << std::get<2>(currentState) << " index: " << static_cast<int>(faseOne::stateToIndex(currentState)) << std::endl;
            for (int i = 0; i < 18; ++i) {
                std::tuple<int, int, int> nextState = faseOne::moveState(filename, currentState, static_cast<Move>(i));
                // std::cout << "acotando fillTable nextstate " << std::get<0>(nextState) << " " << std::get<1>(nextState) << " " << std::get<2>(nextState) << " index: "  << static_cast<int>(faseOne::stateToIndex(nextState)) << std::endl;
                uint64_t nextStateIndex = faseOne::stateToIndex(nextState);

                if (nextStateIndex != 0 && faseOne::readPruning(filename, nextStateIndex) == 0) {
                    faseOne::writePruning(filename, nextStateIndex, std::get<2>(nextState));
                    BFS.push(nextState);
                }
            }
        BFS.pop();
        // p++;  
    }
    if (filename == pruningCOSFilename) std::cout << "fase one pruning table(corner orientation + slide) created!" << std::endl;
    else if (filename == pruningEOSFilename) std::cout << "fase one pruning table(edge orientation + slide) created!" << std::endl;
    return true;
}

std::tuple<int, int, int> faseOne::moveState(const std::string& filename, const std::tuple<int, int, int>& state, const Move& m) {
    std::tuple<int, int, int> result = state;
    if(filename == pruningCOSFilename){
    int UDSlice = fase_one_coord_from_file(std::get<0>(state), m, UDSliceMoveTableFilename);
    int corners = fase_one_coord_from_file(std::get<1>(state), m, cornerOriMoveTableFilename);
    std::get<0>(result) = UDSlice;
    std::get<1>(result) = corners;
    std::get<2>(result)++;
    }
    else if (filename == pruningEOSFilename){
    int UDSlice = fase_one_coord_from_file(std::get<0>(state), m, UDSliceMoveTableFilename);
    int edges = fase_one_coord_from_file(std::get<1>(state), m, edgeOriMoveTableFilename);
    std::get<0>(result) = UDSlice;
    std::get<1>(result) = edges;
    std::get<2>(result)++;
    }
    else{
        std::cerr << "Error: Unknown pruning table filename." << std::endl;
    }
    return result;
}

bool faseOne::CreatePruning(const std::string& filename, std::size_t fileSize) {
    std::string filepath = pruningFoldername + filename;

    std::ofstream file(filepath, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error: " << filename << " cannot be created \n";
        return false;
    }
    file.seekp(fileSize - 1);
    if (!file) {
        std::cerr << "Error fixing file size.\n";
        return false;
    }
    char zero = 0;
    file.write(&zero, 1);
    if (!file) {
        std::cerr << "Error fixing file size\n";
        return false;
    }
    file.close();
    if (!file) {
        std::cerr << "Error closing file.\n";
        return false;
    }
    return true;
}

bool faseOne::writePruning(const std::string& filename, uint64_t index, uint8_t value) {
    uint64_t n = 0;
    std::string filepath = pruningFoldername + filename;
    if (filename == pruningCOSFilename){
        n = NC;
    }
    else if (filename == pruningEOSFilename){
        n = NE;
    }
    if (index >= n) {
        std::cerr << "Error: Index out of bounds1: " << index << std::endl;
        return false;
    }
    std::fstream file(filepath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << filepath << std::endl;
        return false;
    }
    file.seekg(index);
    if (!file) {
        std::cerr << "Error: Failed to seek for read at index: " << index << std::endl;
        return false;
    }
    char current;
    file.get(current);
    if (!file) {
        std::cerr << "Error: Failed to read at index: " << index << std::endl;
        return false;
    }
    if (index != 0 && static_cast<uint8_t>(current) != 0) {
        return false;
    }
    if (index == 0 && value > 0){
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

uint8_t faseOne::readPruning(const std::string& filename, uint64_t index) {
    std::string filepath = pruningFoldername + filename;
    uint64_t n = 0;
    if (filename == pruningCOSFilename){
        n = NC;
    }
    else if (filename == pruningEOSFilename){
        n = NE;
    }
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << filename << std::endl;
        return 255;
    }
    if (index >= n) {
        std::cerr << "Error: Index out of bounds2: " << index << std::endl;
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

uint64_t faseOne::stateToIndex(const std::tuple<int, int, int>& state){
        return (std::get<0>(state) + (std::get<1>(state) * 495));
}

uint64_t faseOne::stateToIndex(const std::tuple<int, int>& state){
        return (std::get<0>(state) + (std::get<1>(state) * 495));
}

// void faseOne::showIndex(){
//     faseOne current = *this;

//     std::cout << "COS: | "<< faseOne::stateToIndex(current.COSstate) << " | EOS: | " << faseOne::stateToIndex(current.EOSstate) << std::endl;
// }

void faseOne::printNonZeroPruningValues(const std::string& filename, size_t upLimit, size_t downLimit) {
    std::ifstream file(pruningFoldername + filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << filename << std::endl;
        return;
    }
    std::cout << "titulo: " << filename << std::endl;
    // El tamaño del archivo debe ser N bytes
    for (std::size_t index = downLimit; index < upLimit; ++index) {
        char byte;
        file.seekg(index);
        if (!file) {
            std::cerr << "Error: Failed to seek to index: " << index << std::endl;
            return;
        }
        file.get(byte);
        if (!file) {
            std::cerr << "Error: Failed to read at index: " << index << std::endl;
            return;
        }

        uint8_t value = static_cast<uint8_t>(static_cast<unsigned char>(byte));
        if (index == 0 || value != 0) {
            std::cout << "Index: " << index << ", Value: " << static_cast<int>(value) << std::endl;
        }
    }
    file.close();
}