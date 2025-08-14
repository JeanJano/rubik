#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s), state(c.get_pure_coord(), e.get_pure_coord(), s.get_pure_coord()) {
        }

// void faseOne::pruningTableToFile(){
//     std::queue<std::tuple<int,int,int,int>> BFS;
//     std::tuple<int,int,int,int> initState = std::make_tuple(0,0,0,0);
//     BFS.push(initState);
//     if(faseOne::createPruningOne(pruningTableFilename, N)){
//         while(!BFS.empty()){
//             long int CurrIndex = stateToIndex(std::get<0>(BFS.front()), std::get<1>(BFS.front()) ,std::get<2>(BFS.front()));
//             if(faseOne::writePruningOne(CurrIndex, std::get<3>(BFS.front()))){
//                 for (int i = 0; i < 18; ++i){
//                     std::tuple<int,int,int,int> nextState = faseOne::moveState(BFS.front(), static_cast<Move>(i));
//                     BFS.push(nextState);
//                 }
//             }
//             BFS.pop();
//         }
//     }
//     else
//         std::cout << "Error creating fase one pruning table" << std::endl;
// }

#include <random>

int randomMove() {
    static std::random_device rd;   // Semilla
    static std::mt19937 gen(rd());  // Motor Mersenne Twister
    static std::uniform_int_distribution<> distrib(0, 17); // Rango inclusivo
    return distrib(gen);
}

std::string faseOne::solveFaseOne(){
    std::tuple<int,int,int> currentState = state;
    uint64_t currentIndex = faseOne::stateToIndex();
    int currDepth = faseOne::readPruningOne(currentIndex);
    std::string solution = "";
    int sure = 0;
    while (currentIndex != 0) {
        std::tuple<int,int,int> candidateState = currentState;
        int candidateDepth = currDepth;
        uint64_t candidateIndex = currentIndex;
        int move = 19;
        for(int i = 0; i < 18; ++i) {
            std::tuple<int,int,int> nextState = faseOne::moveState(currentState, static_cast<Move>(i));
            uint64_t nextStateIndex = faseOne::stateToIndex(std::get<0>(nextState), std::get<1>(nextState), std::get<2>(nextState));
            int nextStateDepth = faseOne::readPruningOne(nextStateIndex);
            if (nextStateDepth < candidateDepth ){
                candidateState = nextState;
                candidateDepth = nextStateDepth;
                candidateIndex = nextStateIndex;
                move = i;
            }
        }
        if (move == 19){
            std::cout << "error in move solveFaseOne" << std::endl;
            currentState = faseOne::moveState(currentState, static_cast<Move>(sure));
            currentIndex = faseOne::stateToIndex(std::get<0>(currentState), std::get<1>(currentState), std::get<2>(currentState));
            currDepth = faseOne::readPruningOne(currentIndex);
            solution += " " + moveToString(static_cast<Move>(sure));
            sure = randomMove();
            // std::cout  << solution << std::endl;

        }
        else{
            solution += " " + moveToString(static_cast<Move>(move));
            currentState = candidateState;
            currentIndex = candidateIndex;
            currDepth = candidateDepth;
        }
    }
    return solution;
}

// void faseOne::pruningTableToFile(){
//     using namespace std::chrono;

//     auto start = steady_clock::now();

//     std::queue<std::tuple<int,int,int,int>> BFS;
//     std::tuple<int,int,int,int> initState = std::make_tuple(0,0,0,0);
//     BFS.push(initState);
//     if(faseOne::createPruningOne(pruningTableFilename, N)){
//         while(!BFS.empty()){
//             long long int CurrIndex = stateToIndex(std::get<0>(BFS.front()), std::get<1>(BFS.front()), std::get<2>(BFS.front()));
//             if(faseOne::writePruningOne(CurrIndex, std::get<3>(BFS.front()))){
//                 for (int i = 0; i < 18; ++i){
//                     std::tuple<int,int,int,int> nextState = faseOne::moveState(BFS.front(), static_cast<Move>(i));
//                     BFS.push(nextState);
//                 }
//             }
//             BFS.pop();
//         }
//     }
//     else {
//         std::cout << "Error creating fase one pruning table" << std::endl;
//         return;
//     }

//     auto end = steady_clock::now();
//     auto duration = duration_cast<seconds>(end - start).count();

//     int hours = duration / 3600;
//     int minutes = (duration % 3600) / 60;
//     int seconds = duration % 60;

//     std::cout << "Execution time: "
//               << std::setw(2) << std::setfill('0') << hours << ":"
//               << std::setw(2) << std::setfill('0') << minutes << ":"
//               << std::setw(2) << std::setfill('0') << seconds << std::endl;
// }


void faseOne::pruningTableToFile() {
    using namespace std::chrono;

    auto start = steady_clock::now();

    if (!faseOne::createPruningOne(pruningTableFilename, N)) {
        std::cout << "Error creating fase one pruning table" << std::endl;
        return;
    }

    std::vector<std::tuple<int, int, int, int>> currentLayer;
    std::vector<std::tuple<int, int, int, int>> nextLayer;
    
    // El estado inicial debe ser manejado de forma especial
    std::tuple<int, int, int, int> initState = std::make_tuple(0, 0, 0, 0);
    currentLayer.push_back(initState);

    // Escribir el estado inicial en la tabla
    faseOne::writePruningOne(stateToIndex(0, 0, 0), 0);
    
    uint64_t statesProcessed = 1; // Ya procesamos el estado inicial

    int currentDepth = 0;
    while (!currentLayer.empty()) {
        std::cout << "Processing depth " << currentDepth << " with " << currentLayer.size() << " states." << std::endl;

        nextLayer.clear();
        for (const auto& currentState : currentLayer) {
            for (int i = 0; i < 18; ++i) {
                std::tuple<int, int, int, int> nextState = faseOne::moveState(currentState, static_cast<Move>(i));
                uint64_t nextStateIndex = stateToIndex(std::get<0>(nextState), std::get<1>(nextState), std::get<2>(nextState));

                if (nextStateIndex != 0 && faseOne::readPruningOne(nextStateIndex) == 0) {
                    faseOne::writePruningOne(nextStateIndex, static_cast<uint8_t>(currentDepth + 1));
                    nextLayer.push_back(nextState);
                }
            }
        }
        
        // Actualizamos el contador de estados procesados y el porcentaje
        statesProcessed += nextLayer.size();
        double progressPercentage = (static_cast<double>(statesProcessed) / N) * 100.0;
        
        std::cout << "Current Progress: " << std::fixed << std::setprecision(2) << progressPercentage << "% ("
                  << statesProcessed << " / " << N << " states)" << std::endl;

        currentLayer = nextLayer;
        currentDepth++;
    }

    auto end = steady_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();

    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    std::cout << "\nExecution time: "
              << std::setw(2) << std::setfill('0') << hours << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"
              << std::setw(2) << std::setfill('0') << seconds << std::endl;
}


uint64_t faseOne::stateToIndex(){
        return (std::get<2>(state) + (std::get<1>(state) * 495ULL) + (std::get<0>(state) * 495ULL * 2048));
}

uint64_t faseOne::stateToIndex(int cornerCoord, int edgeCoord, int UDSliceCoord) {
        // return (UDSliceCoord + (edgeCoord * 495LL) + (cornerCoord * 495 * 2048));
        uint64_t res = UDSliceCoord + (edgeCoord * 495ULL) + (cornerCoord * 495ULL * 2048);
        if (res > N){
            std::cout << "putain! " << cornerCoord << " | " << edgeCoord << " | " << UDSliceCoord << std::endl;
            std::cout << res << std::endl;
        }
        return res;
}

//
std::tuple<int, int, int> faseOne::moveState(std::tuple<int, int, int> state, const Move& m) {
    int corners = fase_one_coord_from_file(std::get<0>(state), m, cornerOriMoveTableFilename);
    int edges = fase_one_coord_from_file(std::get<1>(state), m, edgeOriMoveTableFilename);
    int UDSlice = fase_one_coord_from_file(std::get<2>(state), m, UDSliceMoveTableFilename);
    std::tuple<int, int, int> result = std::make_tuple(corners, edges, UDSlice);
    return result;
}

//To create pruning table
std::tuple<int, int, int, int> faseOne::moveState(std::tuple<int, int, int, int> state, const Move& m) {
    int corners = fase_one_coord_from_file(std::get<0>(state), m, cornerOriMoveTableFilename);
    int edges = fase_one_coord_from_file(std::get<1>(state), m, edgeOriMoveTableFilename);
    int UDSlice = fase_one_coord_from_file(std::get<2>(state), m, UDSliceMoveTableFilename);
    int depth = std::get<3>(state) + 1;
    std::tuple<int, int, int, int > result = std::make_tuple(corners, edges, UDSlice, depth);
    return result;
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
    std::cout << "fase one table file created!" << std::endl;
    return true;
}

bool faseOne::writePruningOne(uint64_t index, uint8_t value) {
    if (index >= N) {
        std::cerr << "Error: Index out of bounds1: " << index << std::endl;
        return false;
    }
    std::fstream file(pruningTableFilename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << pruningTableFilename << std::endl;
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

uint8_t faseOne::readPruningOne(uint64_t index) {
    std::ifstream file(pruningTableFilename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << pruningTableFilename << std::endl;
        return 255;
    }
    if (index >= N) {
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


//USE WISELY
void faseOne::printNonZeroPruningValues() {
    std::ifstream file(pruningTableFilename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file: " << pruningTableFilename << std::endl;
        return;
    }

    // El tamaño del archivo debe ser N bytes
    for (std::size_t index = 0; index < N; ++index) {
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
        if (value != 0) {
            std::cout << "Index: " << index << ", Value: " << static_cast<int>(value) << std::endl;
        }
    }
    file.close();
}