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
inline const std::string pruningFoldername = "pruning_tables";
inline const std::string pruningCOSFilename = "/PruningCOS.bin";
inline const std::string pruningEOSFilename = "/PruningEOS.bin";

// ------------------------init stuff---------------------------------

const std::string UsageMessage =
    "Insert a valid Rubik's cube scrambling in double quoutes:\n"
    "allowed movements:\n"
    "F, F', F2, R, R', R2, U, U', U2, B, B', B2, L, L', L2, D, D', D2";

// ------------------- Valid Move Strings -------------------

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

// ----------------------
enum class Facelet {
    U1 = 0, U2, U3, U4, U5, U6, U7, U8, U9,
    R1, R2, R3, R4, R5, R6, R7, R8, R9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9,
    D1, D2, D3, D4, D5, D6, D7, D8, D9,
    L1, L2, L3, L4, L5, L6, L7, L8, L9,
    B1, B2, B3, B4, B5, B6, B7, B8, B9
};

/**
 * Enum representing the 6 face colors of a Rubik's cube.
 */
enum class Color {
    U = 0, R, F, D, L, B
};
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

//------------------ move string to Move enum map ------------------
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
    F2, B2, R2,
    L2,
};

//------------------ definition of symetrie names ------------------
/*
(C)orner 120 deg along the urf, dlb axis
(Z) 90 deg over the UD axis
(Y) 180 deg over FB axis
(X) a reflection at the RL-slice plane.
// */
// enum class Symetry {
//     Z0C0Y0X0 = 0, Z0C1Y0X0, Z0C2Y0X0, Z0C0Y1X0, Z0C1Y1X0, Z0C2Y1X0,
//     Z0C0Y0X1, Z0C1Y0X1, Z0C2Y0X1, Z0C0Y1X1, Z0C1Y1X1, Z0C2Y1X1,
//     Z1C0Y0X0, Z1C1Y0X0, Z1C2Y0X0, Z1C0Y1X0, Z1C1Y1X0, Z1C2Y1X0,
//     Z1C0Y0X1, Z1C1Y0X1, Z1C2Y0X1, Z1C0Y1X1, Z1C1Y1X1, Z1C2Y1X1,
//     Z2C0Y0X0, Z2C1Y0X0, Z2C2Y0X0, Z2C0Y1X0, Z2C1Y1X0, Z2C2Y1X0,
//     Z2C0Y0X1, Z2C1Y0X1, Z2C2Y0X1, Z2C0Y1X1, Z2C1Y1X1, Z2C2Y1X1,
//     Z3C0Y0X0, Z3C1Y0X0, Z3C2Y0X0, Z3C0Y1X0, Z3C1Y1X0, Z3C2Y1X0,
//     Z3C0Y0X1, Z3C1Y0X1, Z3C2Y0X1, Z3C0Y1X1, Z3C1Y1X1, Z3C2Y1X1
// };

// //------------------ symmetry string to Symmetry enum map ------------------
// inline const std::map<std::string, Symmetry> string_to_symmetry = {

//     {"0000", Symmetry::Z0C0Y0X0}, {"0100", Symmetry::Z0C1Y0X0}, {"0200", Symmetry::Z0C2Y0X0},
//     {"0010", Symmetry::Z0C0Y1X0}, {"0110", Symmetry::Z0C1Y1X0}, {"0210", Symmetry::Z0C2Y1X0},
//     {"0001", Symmetry::Z0C0Y0X1}, {"0101", Symmetry::Z0C1Y0X1}, {"0201", Symmetry::Z0C2Y0X1},
//     {"0011", Symmetry::Z0C0Y1X1}, {"0111", Symmetry::Z0C1Y1X1}, {"0211", Symmetry::Z0C2Y1X1},
//     {"1000", Symmetry::Z1C0Y0X0}, {"1100", Symmetry::Z1C1Y0X0}, {"1200", Symmetry::Z1C2Y0X0},
//     {"1010", Symmetry::Z1C0Y1X0}, {"1110", Symmetry::Z1C1Y1X0}, {"1210", Symmetry::Z1C2Y1X0},
//     {"1001", Symmetry::Z1C0Y0X1}, {"1101", Symmetry::Z1C1Y0X1}, {"1201", Symmetry::Z1C2Y0X1},
//     {"1011", Symmetry::Z1C0Y1X1}, {"1111", Symmetry::Z1C1Y1X1}, {"1211", Symmetry::Z1C2Y1X1},
//     {"2000", Symmetry::Z2C0Y0X0}, {"2100", Symmetry::Z2C1Y0X0}, {"2200", Symmetry::Z2C2Y0X0},
//     {"2010", Symmetry::Z2C0Y1X0}, {"2110", Symmetry::Z2C1Y1X0}, {"2210", Symmetry::Z2C2Y1X0},
//     {"2001", Symmetry::Z2C0Y0X1}, {"2101", Symmetry::Z2C1Y0X1}, {"2201", Symmetry::Z2C2Y0X1},
//     {"2011", Symmetry::Z2C0Y1X1}, {"2111", Symmetry::Z2C1Y1X1}, {"2211", Symmetry::Z2C2Y1X1},
//     {"3000", Symmetry::Z3C0Y0X0}, {"3100", Symmetry::Z3C1Y0X0}, {"3200", Symmetry::Z3C2Y0X0},
//     {"3010", Symmetry::Z3C0Y1X0}, {"3110", Symmetry::Z3C1Y1X0}, {"3210", Symmetry::Z3C2Y1X0},
//     {"3001", Symmetry::Z3C0Y0X1}, {"3101", Symmetry::Z3C1Y0X1}, {"3201", Symmetry::Z3C2Y0X1},
//     {"3011", Symmetry::Z3C0Y1X1}, {"3111", Symmetry::Z3C1Y1X1}, {"3211", Symmetry::Z3C2Y1X1}
// };


// ------------------- Cube Representation -------------------

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

    // edgeOrientCoord symetry(const Symetrie& sym) const;
    // edgeOrientCoord symetryZURF();
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
    cornerOrientCoord corners;
    edgeOrientCoord edges;
    UDSliceCoord slice;
    std::tuple<int, int, int> COSstate;
    std::tuple<int, int, int> EOSstate;

    faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s);
    void showIndex();
    void DoPruningTables();
    bool fillTable(const std::string& filename);
    std::tuple<int, int, int> moveState(const std::string& filename, const std::tuple<int, int, int>& state, const Move& m);
    bool CreatePruning(const std::string& filename, std::size_t fileSize);
    bool writePruning(const std::string& filename, uint64_t index, uint8_t value);
    uint8_t readPruning(const std::string& filename, uint64_t index);
    uint64_t stateToIndex(const std::tuple<int, int, int>& state);
    uint64_t stateToIndex(const std::tuple<int, int>& state);
    static void printNonZeroPruningValues(const std::string& filename,  size_t upLimit, size_t downLimit);
    // int getHeuristic(int COSIndex, int EOSIndex);
    // std::string solveFaseOne();
    // std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> moveSolveState(const std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string>& solveState, const Move& m);
    // void printState(std::tuple<int, int, int> state);
    // void initDeepth();
    // void showSolveState(std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> solveState);
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



    solveFaseOne(const faseOne& toSolve);
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
                      std::vector<int>& path);
    std::vector<int> solve();
    static std::string solutionToString(const std::vector<int>& path);
};

struct cornerPermCoord{
    static constexpr int N = 8;
    std::array<uint8_t, N> explicitCoor;
    std::array<uint8_t, N - 1> OrderDiagram;
    std::array<uint8_t, N - 1> nextOrderDiagram;

    cornerPermCoord();
    cornerPermCoord(const cubeCubie& cube);
    void printExplicitCornPermCoord();
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
    static edgePermCoord from_pure_coord(unsigned int coord);
    unsigned int get_pure_coord() const;
    edgePermCoord nextExplicitCoord();
    static void moveTableToFile();
    void defineOrderDiag();
    void defineNextOrderDiag();
    edgePermCoord fromNextOrderDiag();
    void oneStep(int index);
    void printOrderDiagram() const;
    void printNextOrderDiagram() const;
};


uint16_t get_coord(const cornerOrientCoord& coord);
uint16_t get_coord(const edgeOrientCoord& coord);
uint16_t get_coord(const UDSliceCoord& coord);
uint16_t get_coord(uint16_t coord);
Move get_move(const std::string& moveStr);
Move get_move(int moveIndex);
Move get_move(Move move);

template <typename CoordType, typename MoveType>
uint16_t fase_one_coord_from_file(CoordType coordInput, MoveType moveInput, const std::string& filename) {
    // std::cout << "en focff " << movesFoldername + filename << std::endl;
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

template <typename T>
bool loadBinary(const std::string& filename, T* buffer, size_t count) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;

    in.read(reinterpret_cast<char*>(buffer), count * sizeof(T));
    return in.good();
}

//-------------------nedded to see the cubie representation--------
std::string edge_to_string(Edge e);
std::string corner_to_string(Corner c);

#endif