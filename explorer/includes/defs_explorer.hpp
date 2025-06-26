#ifndef RUBIK_DEFS_HPP
# define RUBIK_DEFS_HPP
# include <array>
# include <string>
# include <ostream>
# include <unordered_set>
# include <iostream>
# include <vector>
# include <sstream>

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

// ------------------- Cube Pieces (Corners and Edges) -------------------

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
    R1, R2, R3,
    F1, F2, F3,
    D1, D2, D3,
    L1, L2, L3,
    B1, B2, B3
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
    cubeCubie basicMove(const std::string& move, const cubeCubie& inputCube) const;
    cubeCubie severalMoves(const std::vector<std::string>& moves, const cubeCubie& inputCube) const;
};

struct cornerOrientCoord{
    static constexpr int N = 8;
    std::array<uint8_t, N> explicitCoor;

    cornerOrientCoord();
    cornerOrientCoord(const cubeCubie& cube);
    void print_explicit_corn_ori_coord() const;
    cornerOrientCoord move(const std::string& move);
    static void create_move_table();
    uint16_t get_pure_coord();
    cornerOrientCoord nextExplicitCoord();
};

//-------------------nedded to see the cubie representation--------
std::string edge_to_string(Edge e);
std::string corner_to_string(Corner c);

#endif