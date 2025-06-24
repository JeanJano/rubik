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
    coordOne.print_explicit_corn_ori_coord();
}
