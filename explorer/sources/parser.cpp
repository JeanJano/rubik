#include "defs_explorer.hpp"
#include "rubik_explorer.hpp"

bool isValidMove(const std::string& move){
    return validRubikMoves.count(move) > 0;
}

std::vector<std::string> parseMoves(const std::string& input){
    std::vector<std::string> moves;
    std::istringstream iss(input);
    std::string move;

    while (iss >> move) {
        if (!isValidMove(move)) {
            std::cerr << "Invalid move detected: " << move << std::endl;
            throw std::invalid_argument(UsageMessage);
        }
        moves.push_back(move);
    }
    return moves;
}