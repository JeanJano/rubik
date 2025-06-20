#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

Cube_cubie get_scrambled_state(std::vector<std::string> scramble){
    Cube_cubie cubo;
    cubo.reset();

    cubo = cubo.severalMoves(scramble, cubo);
    return cubo;
}