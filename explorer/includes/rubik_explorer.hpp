#ifndef RUBIK_EXPLORER
# define RUBIK_EXPLORER

#include "defs_explorer.hpp"

//parser.cpp
bool isValidMove(const std::string& move);
// std::vector<std::string> parseMoves(const std::string& input);
std::vector<Move> parseMoves(const std::string& input);
// cubeCubie.cpp
cubeCubie get_scrambled_state(const std::vector<Move>& scramble);
// utils.cpp
void print_cubie_state(const cubeCubie& cube);
void print_scramble(const std::vector<Move>& scramble);
std::string moveToString(Move move);
//faseOne.cpp


std::string moveToString(GOneMove move);

uint16_t factorial(uint16_t n);
unsigned int factorialInt(unsigned int n);

#endif