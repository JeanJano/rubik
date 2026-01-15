#ifndef RUBIK_DEFS_HPP
# define RUBIK_DEFS_HPP
# include <array>
# include <string>
# include <ostream>
# include <unordered_set>
# include <iostream>
# include <vector>
# include <sstream>
# include <fstream>
# include <map>
# include <tuple>
# include <queue>
# include <filesystem>
# include <limits>
# include <chrono>


//------------------tables names----------------------------------
inline const std::string movesFoldername = "move_tables";
inline const std::string cornerOriMoveTableFilename = "/cornerOriMoves.bin";
inline const std::string edgeOriMoveTableFilename = "/edgeOriMoves.bin";
inline const std::string UDSliceMoveTableFilename = "/UDSliceMoves.bin";
inline const std::string cornerPermMoveTableFilename = "/cornerPerMoves.bin";
inline const std::string edgePermMoveTableFilename = "/edgePerMoves.bin";
inline const std::string UDSTwoTableFilename = "/UDSTwoMoves.bin";
inline const std::string pruningFoldername = "pruning_tables";
inline const std::string pruningCOSFilename = "/PruningCOS.bin";
inline const std::string pruningEOSFilename = "/PruningEOS.bin";
inline const std::string pruningCPSFilename = "/PruningCPS.bin";
inline const std::string pruningEPSFilename = "/PruningEPS.bin";

// ------------------- Moves -------------------

/**
 * Enum for the 18 basic face moves in the face-turn metric (quarter turns).
 */
enum class Move {
    U1 = 0, U2, U3,  // U, U2, U'
    D1, D2, D3,
    F1, F2, F3,
    B1, B2, B3,
    R1, R2, R3,
    L1, L2, L3
};

inline const std::map<std::string, Move> string_to_move = {
    {"U", Move::U1}, {"U'", Move::U3}, {"U2", Move::U2},
    {"D", Move::D1}, {"D'", Move::D3}, {"D2", Move::D2},
    {"F", Move::F1}, {"F'", Move::F3}, {"F2", Move::F2},
    {"B", Move::B1}, {"B'", Move::B3}, {"B2", Move::B2},
    {"R", Move::R1}, {"R'", Move::R3}, {"R2", Move::R2},
    {"L", Move::L1}, {"L'", Move::L3}, {"L2", Move::L2}
};

enum class GOneMove {
    U1 = 0, U2, U3,  // U, U2, U'
    D1, D2, D3,
    F2, B2, R2, L2    
};

inline const std::map<std::string, GOneMove> stringToGOneMove = {
    {"U", GOneMove::U1}, {"U'", GOneMove::U3}, {"U2", GOneMove::U2},
    {"D", GOneMove::D1}, {"D'", GOneMove::D3}, {"D2", GOneMove::D2},
    {"F2", GOneMove::F2},
    {"B2", GOneMove::B2},
    {"R2", GOneMove::R2},
    {"L2", GOneMove::L2}
};

// ------------------------Instalation & Parsing---------------------------------
const std::string UsageMessage =
    "Insert a valid Rubik's cube scrambling in double quoutes:\n"
    "allowed movements:\n"
    "F, F', F2, R, R', R2, U, U', U2, B, B', B2, L, L', L2, D, D', D2\n\n"
    "Flags: \n"
    "-i \n"
    "Calcule and install the move and pruning tables\n\n"
    "-2 \n"
    "Solve scramble as 2x2 cube";


/**
 * Set of valid string representations of moves for scrambler.
 */
inline const std::unordered_set<std::string> validRubikMoves = {
    "U", "U'", "U2",
    "R", "R'", "R2",
    "F", "F'", "F2",
    "D", "D'", "D2",
    "L", "L'", "L2",
    "B", "B'", "B2"
};

struct initOptions {
    bool init = false;
    bool solve2 = false;
    bool solve3 = false;
    std::vector<Move> scramble;
};

initOptions init(int ac, char** av);




// ------------------- Cube Representation -------------------

/**
 * Enum for the 8 corner cubies.
 * Each corner has 3 facelets: for example, URF = Up-Right-Front.
 */
enum class Corner {
    URF = 0, UFL, ULB, UBR, DFR, DLF, DBL, DRB
};

inline const char* corner_names[] = {
    "URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB"
};

/**
 * Enum for the 12 edge cubies.
 * Each edge has 2 facelets: for example, UR = Up-Right.
 */
enum class Edge {
    UR = 0, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR
};

inline const char* edge_names[] = {
    "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR"
};

/**
 * Structure representing a corner cubie by its position and orientation.
 * - `pos` is the index (0–7) of which corner is in the current slot.
 * - `ori` is the orientation (0, 1, or 2).
 */
struct CornerCubie {
    uint8_t pos; // which corner is here
    uint8_t ori; // orientation: 0, 1, 2
};

/**
 * Structure representing an edge cubie by its position and orientation.
 * - `pos` is the index (0–11) of which edge is in the current slot.
 * - `ori` is the orientation (0 or 1).
 */
struct EdgeCubie {
    uint8_t pos; // which edge is here
    uint8_t ori; // orientation: 0 or 1
};

/**
 * A full cube state with all 8 corners and 12 edges.
 */

struct cubeCubie {
    std::array<CornerCubie, 8> corners;
    std::array<EdgeCubie, 12> edges;

    void reset();
    cubeCubie basicMove(Move move, const cubeCubie& inputCube) const;
    cubeCubie severalMoves(const std::vector<Move>& moves, const cubeCubie& inputCube) const;
};

struct cornerOrientCoord{
    static constexpr int N = 8;
    std::array<uint8_t, N> explicitCoor;

    cornerOrientCoord();
    cornerOrientCoord(const cubeCubie& cube);
    void print_explicit_corn_ori_coord() const;
    void print_explicit_corn_ori_coord2() const;
    cornerOrientCoord move(const Move& move) const;
    static void print_move_table();
    static cornerOrientCoord from_pure_coord(uint16_t coord);
    uint16_t get_pure_coord() const;
    cornerOrientCoord nextExplicitCoord();
    static void moveTableToFile();
};

struct edgeOrientCoord{
    static constexpr int N = 12;
    std::array<uint8_t, N> explicitCoor;

    edgeOrientCoord();
    edgeOrientCoord(const cubeCubie& cube);
    void print_explicit_edge_ori_coord() const;
    void print_explicit_edge_ori_coord2() const;
    edgeOrientCoord move(const Move& move) const;
    static void print_move_table();
    static edgeOrientCoord from_pure_coord(uint16_t coord);
    uint16_t get_pure_coord() const;
    edgeOrientCoord nextExplicitCoord();
    static void moveTableToFile();
};


struct UDSliceCoord{
    static constexpr int N = 12;
    std::array<uint8_t, N> explicitCoor;

    UDSliceCoord();
    UDSliceCoord(const cubeCubie& cube);
    void print_explicit_udslice_ori_coord() const;
    void print_explicit_udslice_ori_coord2() const;
    UDSliceCoord move(const Move& move) const;
    static void print_move_table();
    static UDSliceCoord from_pure_coord(const uint16_t& coord);
    uint16_t get_pure_coord() const;
    UDSliceCoord nextExplicitCoord();
    UDSliceCoord nextExplicitCoord(int index, int count);
    static void moveTableToFile();
};


struct faseOne{
    static constexpr int NE = 495 * 2048;
    static constexpr int NC = 495 * 2187;
    // cornerOrientCoord corners;
    // edgeOrientCoord edges;
    // UDSliceCoord slice;
    // std::tuple<int, int, int> COSstate;
    // std::tuple<int, int, int> EOSstate;

    // faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s);
    // void showIndex();
    static void DoPruningTables();
    static bool fillTable(const std::string& filename);
    static std::tuple<int, int, int> moveState(const std::string& filename, const std::tuple<int, int, int>& state, const Move& m);
    static bool CreatePruning(const std::string& filename, std::size_t fileSize);
    static bool writePruning(const std::string& filename, uint64_t index, uint8_t value);
    static uint8_t readPruning(const std::string& filename, uint64_t index);
    static uint64_t stateToIndex(const std::tuple<int, int, int>& state);
    static uint64_t stateToIndex(const std::tuple<int, int>& state);
    static void printNonZeroPruningValues(const std::string& filename,  size_t upLimit, size_t downLimit);
};

struct solveFaseOneState {
    int co;
    int eo; 
    int s; 
};

struct solveFaseOne {
    solveFaseOneState state;
    uint16_t cornerOriMove[2187][18];
    uint16_t edgeOriMove[2048][18];
    uint16_t udSliceMove[495][18];
    uint8_t pruneCOS[2187 * 495];
    uint8_t pruneEOS[2048 * 495];
    static constexpr int FOUND = -1;
    static constexpr int INF = 10000000;

    solveFaseOne(const cubeCubie& cube);
    bool loadMoveTables();
    bool loadPruningTables();
    int COS_index(int co, int s);
    int EOS_index(int eo, int s);
    void applyMove(solveFaseOneState& st, int m);
    int heuristic(const solveFaseOneState& st);
    int dfs(solveFaseOneState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<Move>& path);
    std::vector<Move> solve();
    static std::string solutionToString(const std::vector<Move>& path);
};

struct cornerPermCoord{
    static constexpr int N = 8;
    std::array<uint8_t, N> explicitCoor;
    std::array<uint8_t, N - 1> OrderDiagram;
    std::array<uint8_t, N - 1> nextOrderDiagram;

    cornerPermCoord();
    cornerPermCoord(const cubeCubie& cube);
    void printExplicitCornPermCoord() const;
    void printExplicitCornPermCoord2();
    cornerPermCoord move(const GOneMove& move) const;
    static void printMoveTable();
    static cornerPermCoord from_pure_coord(uint16_t coord);
    uint16_t get_pure_coord() const;
    cornerPermCoord nextExplicitCoord();
    static void moveTableToFile();
    void defineOrderDiag();
    void defineNextOrderDiag();
    cornerPermCoord fromNextOrderDiag();
    void oneStep(int index);
    void printOrderDiagram() const;
    void printNextOrderDiagram() const;
};

struct edgePermCoord{
    static constexpr int N = 8;
    std::array<uint8_t, N> explicitCoor;
    std::array<uint8_t, N - 1> OrderDiagram;
    std::array<uint8_t, N - 1> nextOrderDiagram;

    edgePermCoord();
    edgePermCoord(const cubeCubie& cube);
    void printExplicitEdgePermCoord();
    void printExplicitEdgePermCoord2();
    edgePermCoord move(const GOneMove& move) const;
    static void printMoveTable();
    static edgePermCoord from_pure_coord(uint16_t coord);
    uint16_t get_pure_coord() const;
    edgePermCoord nextExplicitCoord();
    static void moveTableToFile();
    void defineOrderDiag();
    void defineNextOrderDiag();
    edgePermCoord fromNextOrderDiag();
    void oneStep(int index);
    void printOrderDiagram() const;
    void printNextOrderDiagram() const;
};

struct UDSTwoCoord{
    static constexpr int N = 4;
    std::array<uint8_t, N> explicitCoor;
    std::array<uint8_t, N - 1> OrderDiagram;
    std::array<uint8_t, N - 1> nextOrderDiagram;

    UDSTwoCoord();
    UDSTwoCoord(const cubeCubie& cube);
    void printExplicitUDSTPermCoord();
    void printExplicitUDSTPermCoord2();
    UDSTwoCoord move(const GOneMove& move) const;
    static void printMoveTable();
    static UDSTwoCoord from_pure_coord(uint16_t coord);
    uint16_t get_pure_coord() const;
    UDSTwoCoord nextExplicitCoord();
    static void moveTableToFile();
    void defineOrderDiag();
    void defineNextOrderDiag();
    UDSTwoCoord fromNextOrderDiag();
    void oneStep(int index);
    void printOrderDiagram() const;
    void printNextOrderDiagram() const;
};


struct faseTwo{
    static constexpr int N = 40320 * 24;
    // cornerPermCoord corners;
    // edgePermCoord edges;
    // UDSTwoCoord slice;
    // std::tuple<int, int, int> CPSstate;
    // std::tuple<int, int, int> EPSstate;

    // faseTwo(const cornerPermCoord& c, const edgePermCoord& e, const UDSTwoCoord& s);
    // void showIndex();
    static void DoPruningTables();
    static bool fillTable(const std::string& filename);
    static std::tuple<int, int, int> moveState(const std::string& filename, const std::tuple<int, int, int>& state, const GOneMove& m);
    static bool CreatePruning(const std::string& filename, std::size_t fileSize);
    static bool writePruning(const std::string& filename, uint64_t index, uint8_t value);
    static uint8_t readPruning(const std::string& filename, uint64_t index);
    static uint64_t stateToIndex(const std::tuple<int, int, int>& state);
    static uint64_t stateToIndex(const std::tuple<int, int>& state);
    static void printNonZeroPruningValues(const std::string& filename,  size_t upLimit, size_t downLimit);
};

struct solveFaseTwoState {
    int cp;
    int ep; 
    int s; 
};

struct solveFaseTwo {
    solveFaseTwoState state;
    uint16_t cornerPermMove[40320][10];
    uint16_t edgePermMove[40320][10];
    uint16_t udSliceMove[24][10];
    uint8_t pruneCPS[40320 * 24];
    uint8_t pruneEPS[40320 * 24];
    static constexpr int FOUND = -1;
    static constexpr int INF = 10000000;



    solveFaseTwo(const cubeCubie& cube);
    bool loadMoveTables();
    bool loadPruningTables();
    int CPS_index(int cp, int s);
    int EPS_index(int ep, int s);
    void applyMove(solveFaseTwoState& st, int m);
    int heuristic(const solveFaseTwoState& st);
    int dfs(solveFaseTwoState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<GOneMove>& path);
    std::vector<GOneMove> solve();
    static std::string solutionToString(const std::vector<GOneMove>& path);
};


uint16_t get_coord(const cornerOrientCoord& coord);
uint16_t get_coord(const edgeOrientCoord& coord);
uint16_t get_coord(const UDSliceCoord& coord);
uint16_t get_coord(const cornerPermCoord& coord);
uint16_t get_coord(const edgePermCoord& coord);
uint16_t get_coord(const UDSTwoCoord& coord);
uint16_t get_coord(uint16_t coord);
Move get_move(const std::string& moveStr);
Move get_move(int moveIndex);
Move get_move(Move move);
GOneMove getGOneMove(const std::string& moveStr);
GOneMove getGOneMove(int moveIndex);
GOneMove getGOneMove(GOneMove move);

template <typename CoordType, typename MoveType>
uint16_t fase_one_coord_from_file(CoordType coordInput, MoveType moveInput, const std::string& filename) {
    std::ifstream in(movesFoldername + filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error: could not open move table file for reading." << std::endl;
        return 0;
    }

    uint16_t pureCoord = get_coord(coordInput);
    Move move = get_move(moveInput);

    std::streampos pos = static_cast<std::streampos>(pureCoord) * 18 * sizeof(uint16_t)
                       + static_cast<int>(move) * sizeof(uint16_t);
    in.seekg(pos);

    uint16_t result;
    in.read(reinterpret_cast<char*>(&result), sizeof(uint16_t));
    in.close();

    return result;
}


template <typename CoordType, typename MoveType>
uint16_t fase_two_coord_from_file(CoordType coordInput, MoveType moveInput, const std::string& filename) {
    std::ifstream in(movesFoldername + filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error: could not open move table file for reading." << std::endl;
        return 0;
    }

    uint16_t pureCoord = get_coord(coordInput);
    GOneMove move = getGOneMove(moveInput);

    std::streampos pos = static_cast<std::streampos>(pureCoord) * 10 * sizeof(uint16_t)
                       + static_cast<int>(move) * sizeof(uint16_t);
    in.seekg(pos);

    uint16_t result;
    in.read(reinterpret_cast<char*>(&result), sizeof(uint16_t));
    in.close();

    return result;
}


template <typename T>
bool loadBinary(const std::string& filename, T* buffer, size_t count) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;

    in.read(reinterpret_cast<char*>(buffer), count * sizeof(T));
    return in.good();
}




///////////////////////////////

//parser.cpp
bool isValidMove(const std::string& move);
// std::vector<std::string> parseMoves(const std::string& input);
std::vector<Move> parseMoves(const std::string& input);
// cubeCubie.cpp
cubeCubie getScrambledState(const std::vector<Move>& scramble);
// utils.cpp
void print_cubie_state(const cubeCubie& cube);
void print_scramble(const std::vector<Move>& scramble);
std::string moveToString(Move move);
//faseOne.cpp


std::string moveToString(GOneMove move);

uint16_t factorial(uint16_t n);
std::vector<Move> getScramble(char* av);
bool ensureDirectoryExists(const std::string& path);
bool solve3x3(const std::vector<Move>& scramble);
bool solve2x2(const std::vector<Move>& scramble);
bool install ();
std::string getFinalString(const std::vector<Move>& solvedFaseOne, const std::vector<GOneMove>& solvedFaseTwo);
Move GOneToRealMove(const GOneMove& m);
bool allTablesExist(); 
#endif