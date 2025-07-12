#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s), state(c.get_pure_coord(), e.get_pure_coord(), s.get_pure_coord()) {
        }

void faseOne::pruningTableToFile(){
        faseOne initState(cornerOrientCoord(), edgeOrientCoord(), UDSliceCoord());
        // std::vector <std::tuple<int,int>> visibleTable;
        // std::queue<std::tuple<int,int,int>> bfs;
        // int depth = 0;
        std::cout << "aca" << initState.stateToIndex() << std::endl;
}

int faseOne::stateToIndex(){
        return (this.state[0] + (this.state[1] * 2187) + (this.state[2] * 2187 * 2048));
}