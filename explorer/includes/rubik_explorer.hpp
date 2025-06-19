#ifndef RUBIK_EXPLORER
# define RUBIK_EXPLORER

#include "defs_explorer.hpp"
# include <unordered_set>
# include <string>
# include <iostream>
# include <vector>
# include <sstream>

//parser.cpp
bool isValidMove(const std::string& move);
std::vector<std::string> parseMoves(const std::string& input);

// scrambler.cpp
Cube get_scrambled_state(std::vector<std::string> scramble);

// utils.cpp
void print_cube_state(Cube cube);
#endif