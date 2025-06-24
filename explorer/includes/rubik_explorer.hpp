#ifndef RUBIK_EXPLORER
# define RUBIK_EXPLORER

#include "defs_explorer.hpp"

//parser.cpp
bool isValidMove(const std::string& move);
std::vector<std::string> parseMoves(const std::string& input);
// cubeCubie.cpp
cubeCubie get_scrambled_state(std::vector<std::string> scramble);
// utils.cpp
void print_cubie_state(const cubeCubie& cube);
void print_scramble(const std::vector<std::string>& scramble);
//corner_orientation.cpp

#endif