#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        std::cout << UsageMessage << std::endl;
        return 1;
    }

    try {
        std::vector<std::string> moves = parseMoves(av[1]);

        std::cout << "Moves parsed successfully:\n";
        for (const auto& m : moves) {
            std::cout << m << " ";
        }
        std::cout << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error parsing moves: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
