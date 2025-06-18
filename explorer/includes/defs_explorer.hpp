#ifndef DEFS_RUBIK_EXPLORER_HPP
# define DEFS_RUBIK_EXPLORER_HPP

# include <unordered_set>
# include <string>

inline const std::unordered_set<std::string> validRubikMoves = {
    "F", "F'", "F2", "R", "R'", "R2", "U", "U'", "U2",
    "B", "B'", "B2", "L", "L'", "L2", "D", "D'", "D2"
};

const std::string UsageMessage =
    "Insert a valid Rubik's cube scrambling in double quoutes:\n"
    "allowed movements:\n"
    "F, F', F2, R, R', R2, U, U', U2, B, B', B2, L, L', L2, D, D', D2";

#endif