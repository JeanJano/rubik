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


//------------------tables names----------------------------------
inline const std::string movesFoldername = "move_tables";
inline const std::string cornerOriMoveTableFilename = "/cornerOriMoves.bin";
inline const std::string edgeOriMoveTableFilename = "/edgeOriMoves.bin";
inline const std::string UDSliceMoveTableFilename = "/UDSliceMoves.bin";
inline const std::string pruningTableFilename = "PruningTableFaseOne.bin";

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
    static constexpr long long int N = 495L * 2048 * 2187;
    cornerOrientCoord corners;
    edgeOrientCoord edges;
    UDSliceCoord slice;
    std::tuple<int, int, int> state;

    faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s);
    static void pruningTableToFile();
    static void seePruningTable(int limitDepth);
    faseOne moveState(const Move& m);
    long int stateToIndex();
    long int stateToIndex(int cornerCoord, int edgeCoord,, int UDSliceCoord);
    static bool createPruningOne(const std::string& filename, std::size_t fileSize);
    static bool writePruningOne(std::size_t index, uint8_t value);
    static uint8_t readPruningOne(std::size_t index);
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


//-------------------nedded to see the cubie representation--------
std::string edge_to_string(Edge e);
std::string corner_to_string(Corner c);

#endif