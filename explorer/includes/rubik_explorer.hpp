#ifndef RUBIK_EXPLORER
# define RUBIK_EXPLORER

# include <unordered_set>
# include <string>
# include <iostream>
# include <vector>
#include <sstream>

bool isValidMove(const std::string& move);
std::vector<std::string> parseMoves(const std::string& input);

#endif