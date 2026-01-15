
#include "defs_explorer.hpp"

// void printState(const std::tuple<int,int,int>& state){
//     std::cout << std::get<0>(state) << " | " << std::get<1>(state) << " | " << std::get<2>(state) << std::endl;}

// faseTwo::faseTwo(const cornerPermCoord& c, const edgePermCoord& e, const UDSTwoCoord& s)
//         : corners(c), edges(e), slice(s), CPSstate(s.getPureCoord(), c.getPureCoord(), 0),
//         EPSstate(s.getPureCoord(), e.getPureCoord(), 0) {
// }

void faseTwo::DoPruningTables(){
    namespace fs = std::filesystem;
    if (!fs::exists(pruningFoldername + pruningCPSFilename)) {
        if (!faseTwo::CreatePruning(pruningCPSFilename, N)) {
            std::cout << "Error creating CPS pruning table" << std::endl;
            return;
        }
    }
    if (!fs::exists(pruningFoldername + pruningEPSFilename)) {
        if (!faseTwo::CreatePruning(pruningEPSFilename, N)) {
            std::cout << "Error creating EPS pruning table" << std::endl;
            return;
        }
    }
    if (!faseTwo::fillTable(pruningCPSFilename)) {
        std::cout << "Error filling fase one CPS pruning table" << std::endl;
        return;
    } 
    if (!faseTwo::fillTable(pruningEPSFilename)) {
        std::cout << "Error filling fase one EPS pruning table" << std::endl;
        return;
    }
}

bool faseTwo::fillTable(const std::string& filename) {
    // if (filename == pruningCPSFilename) std::cout << "im in CPS" << std::endl;
    // else if (filename == pruningEPSFilename) {std::cout << "im in EPS" << std::endl;}
    std::queue<std::tuple<int, int, int>> BFS;
    std::tuple<int,int,int> initState = std::make_tuple(0,0,0);
    BFS.push(initState);
    // int p = 0;
    // while(!BFS.empty() && p < 11){
    while(!BFS.empty()){
        auto currentState = BFS.front();
            // std::cout << "acotando fillTable BFS.front " << std::get<0>(currentState) << " " << std::get<1>(currentState) << " " << std::get<2>(currentState) << " index: " << static_cast<int>(faseTwo::stateToIndex(currentState)) << std::endl;
            for (int i = 0; i < 10; ++i) {
                std::tuple<int, int, int> nextState = faseTwo::moveState(filename, currentState, static_cast<GOneMove>(i));
                uint64_t nextStateIndex = faseTwo::stateToIndex(nextState);
                // std::cout << "viendo fillTable BFS.front " << std::get<0>(nextState) << " " << std::get<1>(nextState) << " " << std::get<2>(nextState) << " index: " << nextStateIndex << std::endl;
                // if (faseTwo::readPruning(filename, nextStateIndex) == 255)
                // {
                //     std::cout << "acotando fillTable BFS.front " << std::get<0>(currentState) << " " << std::get<1>(currentState) << " " << std::get<2>(currentState) << " index: " << static_cast<int>(faseTwo::stateToIndex(currentState)) << std::endl;
                //     std::cout << "acotando fillTable nextstate " << std::get<0>(nextState) << " " << std::get<1>(nextState) << " " << std::get<2>(nextState) << " index: "  << static_cast<int>(faseTwo::stateToIndex(nextState)) << " read: " << static_cast<int>(faseTwo::readPruning(filename, nextStateIndex)) << std::endl;
                //     break;
                // }
                if (nextStateIndex != 0 && faseTwo::readPruning(filename, nextStateIndex) == 0) {
                    faseTwo::writePruning(filename, nextStateIndex, std::get<2>(nextState));
                    BFS.push(nextState);
                }
            }
        BFS.pop();
        // p++;  
        // std::cout << "p " << BFS.size() << std::endl;  
    }
    if (filename == pruningCPSFilename) std::cout << "fase two pruning table(corner permutation + slide) created!" << std::endl;
    else if (filename == pruningEPSFilename) std::cout << "fase two pruning table(edge permutation + slide) created!" << std::endl;
    return true;
}

std::tuple<int, int, int> faseTwo::moveState(const std::string& filename, const std::tuple<int, int, int>& state, const GOneMove& m) {
    std::tuple<int, int, int> result = state;
    if(filename == pruningCPSFilename){
    int UDSlice = fase_two_coord_from_file(std::get<0>(state), m, UDSTwoTableFilename);
    int corners = fase_two_coord_from_file(std::get<1>(state), m, cornerPermMoveTableFilename);
    std::get<0>(result) = UDSlice;
    std::get<1>(result) = corners;
    std::get<2>(result)++;
    }
    else if (filename == pruningEPSFilename){
    int UDSlice = fase_two_coord_from_file(std::get<0>(state), m, UDSTwoTableFilename);
    int edges = fase_two_coord_from_file(std::get<1>(state), m, edgePermMoveTableFilename);
    std::get<0>(result) = UDSlice;
    std::get<1>(result) = edges;
    std::get<2>(result)++;
    }
    else{
        std::cerr << "Error: Unknown pruning table filename." << std::endl;
    }
    return result;
}

bool faseTwo::CreatePruning(const std::string& filename, std::size_t fileSize) {
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

bool faseTwo::writePruning(const std::string& filename, uint64_t index, uint8_t value) {
    std::string filepath = pruningFoldername + filename;
    if (index >= N) {
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

uint8_t faseTwo::readPruning(const std::string& filename, uint64_t index) {
    std::string filepath = pruningFoldername + filename;
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << filename << std::endl;
        return 255;
    }
    if (index > N) {
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

uint64_t faseTwo::stateToIndex(const std::tuple<int, int, int>& state){
        return (std::get<0>(state) + (std::get<1>(state) * 24));
}

uint64_t faseTwo::stateToIndex(const std::tuple<int, int>& state){
        return (std::get<0>(state) + (std::get<1>(state) * 24));
}

// void faseTwo::showIndex(){
//     faseTwo current = *this;

//     std::cout << "CPS: | "<< faseTwo::stateToIndex(current.CPSstate) << " | EPS: | " << faseTwo::stateToIndex(current.EPSstate) << std::endl;
// }

void faseTwo::printNonZeroPruningValues(const std::string& filename, size_t upLimit, size_t downLimit) {
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