#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOneCoord::faseOneCoord(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s) {}