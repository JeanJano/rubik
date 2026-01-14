#include "defs_explorer.hpp"


Move stringToMove(const std::string& moveStr) {
    if (moveStr == "U")  return Move::U1;
    if (moveStr == "U2") return Move::U2;
    if (moveStr == "U\'") return Move::U3;
    if (moveStr == "R")  return Move::R1;
    if (moveStr == "R2") return Move::R2;
    if (moveStr == "R\'") return Move::R3;
    if (moveStr == "F")  return Move::F1;
    if (moveStr == "F2") return Move::F2;
    if (moveStr == "F\'") return Move::F3;
    if (moveStr == "D")  return Move::D1;
    if (moveStr == "D2") return Move::D2;
    if (moveStr == "D\'") return Move::D3;
    if (moveStr == "L")  return Move::L1;
    if (moveStr == "L2") return Move::L2;
    if (moveStr == "L\'") return Move::L3;
    if (moveStr == "B")  return Move::B1;
    if (moveStr == "B2") return Move::B2;
    if (moveStr == "B\'") return Move::B3;
    throw std::invalid_argument("Invalid move: " + moveStr);
}


bool isValidMove(const std::string& move){
    return validRubikMoves.count(move) > 0;
}

std::vector<Move> parseMoves(const std::string& input) {
    std::vector<Move> moves;
    std::istringstream iss(input);
    std::string moveStr;

    while (iss >> moveStr) {
        if (!isValidMove(moveStr)) {
            std::cerr << "Invalid move detected: " << moveStr << std::endl;
            throw std::invalid_argument(UsageMessage);
        }
        moves.push_back(stringToMove(moveStr));
    }

    return moves;
}

// std::vector<std::string> parseMoves(const std::string& input){
//     std::vector<std::string> moves;
//     std::istringstream iss(input);
//     std::string move;

//     while (iss >> move) {
//         if (!isValidMove(move)) {
//             std::cerr << "Invalid move detected: " << move << std::endl;
//             throw std::invalid_argument(UsageMessage);
//         }
//         moves.push_back(move);
//     }
//     return moves;
// }
