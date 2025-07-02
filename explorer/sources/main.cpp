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
    cornerOrientCoord coordOne = cornerOrientCoord(scrambledCube);
    std::cout << "init pure coord " << coordOne.get_pure_coord() << std::endl;
    //--------------------------------------
    cornerOrientCoord::move_table_to_file();
    for (int i = 0; i < 18; i++){
        std::cout << "vamos arriba: " << move_coord_from_file(coordOne, i) << std::endl;
    }
    cornerOrientCoord::print_move_table();
}
