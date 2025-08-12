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
    faseOne coordOne = faseOne(cornerOrientCoord(scrambledCube), edgeOrientCoord(scrambledCube), UDSliceCoord(scrambledCube));
    // std::cout << "coords: " << coordOne.corners.get_pure_coord() << " | " << coordOne.edges.get_pure_coord() << " | " << coordOne.slice.get_pure_coord() << std::endl;
    std::cout << coordOne.stateToIndex() << std::endl;
    // cornerOrientCoord::moveTableToFile();
    // edgeOrientCoord::moveTableToFile();
    // UDSliceCoord::moveTableToFile();
    // faseOne::pruningTableToFile();
    // faseOne::printNonZeroPruningValues();
    // std::cout << coordOne.solveFaseOne() << std::endl;

}
