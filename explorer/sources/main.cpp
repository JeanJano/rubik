#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

std::vector<Move> get_scramble(int ac, char** av) {
    if (ac != 2) {
        std::cout << UsageMessage << std::endl;
        return {};
    }

    try {
        std::vector<Move> scramble = parseMoves(av[1]);
        if (scramble.empty()) {
            std::cout << UsageMessage << std::endl;
            return {};
        }
        return scramble;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error parsing moves: " << e.what() << std::endl;
        return {};
    }
}



int main(int ac, char** av) {
    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return 1;
    cubeCubie scrambledCube = get_scrambled_state(scramble);
    cornerOrientCoord::moveTableToFile();
    edgeOrientCoord::moveTableToFile();
    UDSliceCoord::moveTableToFile();
    faseOne fase1 = faseOne(cornerOrientCoord(scrambledCube), edgeOrientCoord(scrambledCube), UDSliceCoord(scrambledCube));
    // faseOne::printNonZeroPruningValues(pruningCOSFilename, 611854, 611852);
    // faseOne::printNonZeroPruningValues(pruningEOSFilename, 100, 0);
    std::cout << fase1.solveFaseOne() << std::endl;
}
