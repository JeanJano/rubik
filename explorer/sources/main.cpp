#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

std::vector<std::string> get_scramble(int ac, char** av) {
    if (ac != 2) {
        std::cout << UsageMessage << std::endl;
        return {};
    }

    try {
        std::vector<std::string> scramble = parseMoves(av[1]);
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
    std::vector<std::string> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return 1;
    cubeCubie scrambledCube = get_scrambled_state(scramble);
    cornerOrientCoord coordOne = cornerOrientCoord(scrambledCube);
    std::cout<< "avant" << std::endl;
    coordOne.print_explicit_corn_ori_coord();
    coordOne = coordOne.cornOriMove("D2");
    coordOne = coordOne.cornOriMove("L'");
    coordOne = coordOne.cornOriMove("R");
    coordOne = coordOne.cornOriMove("U");
    coordOne = coordOne.cornOriMove("L2");
    coordOne = coordOne.cornOriMove("D'");
    coordOne = coordOne.cornOriMove("B2");
    coordOne = coordOne.cornOriMove("R'");
    coordOne = coordOne.cornOriMove("F");
    std::cout<< "apres" << std::endl;
    coordOne.print_explicit_corn_ori_coord();
}
