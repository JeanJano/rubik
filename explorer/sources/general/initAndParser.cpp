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

bool allTablesExist() {
    namespace fs = std::filesystem;

    const fs::path pruningDir = pruningFoldername;
    const fs::path moveDir    = movesFoldername;

 
    if (!fs::exists(pruningDir) || !fs::is_directory(pruningDir))
        return false;

    if (!fs::exists(moveDir) || !fs::is_directory(moveDir))
        return false;

    const std::vector<std::string> pruningTables = {
        pruningCOSFilename,
        pruningCPSFilename,
        pruningEOSFilename,
        pruningEPSFilename,
        pruningCOFilename,
        pruningCPFilename,
    };

    const std::vector<std::string> moveTables = {
        cornerOriMoveTableFilename,
        edgeOriMoveTableFilename,
        UDSliceMoveTableFilename,
        cornerPermMoveTableFilename,
        cornerPermTwoMoveTableFilename,
        edgePermMoveTableFilename,
        UDSTwoTableFilename
    };

    for (const auto& file : pruningTables) {
        const fs::path curr = pruningFoldername + file;
        if (!fs::exists(curr))
            return false;
    }

    for (const auto& file : moveTables) {
        const fs::path curr = movesFoldername + file;
        if (!fs::exists(curr))
            return false;
    }

    return true;
}

std::vector<Move> getScramble(char* av) {
    try {
        std::vector<Move> scramble = parseMoves(av);

        return scramble;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error parsing moves: " << e.what() << std::endl;
        return {};
    }
}

initOptions init(int ac, char** av){
    initOptions opt;

    if (ac == 1 || ac > 3){
        std::cout << UsageMessage << std::endl;
    }
    std::string arg1 = av[1];
        if (arg1 == "-i") {
            if(ac > 2){
                std::cout << UsageMessage << std::endl;
            }
            opt.init = true;
        }
        else if (arg1 == "-2") {
            if(allTablesExist()){
                opt.scramble = getScramble(av[2]);
                if (opt.scramble.empty()) {
                    std::cout << UsageMessage << std::endl;
                }
                else
                    opt.solve2 = true;
            }
            else std::cout << "please install with the command ./explorer_rubik -i" << std::endl;
        }
        else {
            if(ac > 2){
                std::cout << UsageMessage << std::endl;
                return opt;
            }
            if(allTablesExist()){
                opt.scramble = getScramble(av[1]);
                if (opt.scramble.empty()) {
                    std::cout << UsageMessage << std::endl;
                }
                else
                    opt.solve3 = true;
            }
            else std::cout << "please install with the command ./explorer_rubik -i" << std::endl;
        }
    return opt;
}