#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

faseOne::faseOne(const cornerOrientCoord& c, const edgeOrientCoord& e, const UDSliceCoord& s)
        : corners(c), edges(e), slice(s), state(c.get_pure_coord(), e.get_pure_coord(), s.get_pure_coord()) {
        }

void faseOne::pruningTableToFile(){
        faseOne initState{cornerOrientCoord(), edgeOrientCoord(), UDSliceCoord()};

}

long long int faseOne::stateToIndex(){
        return (std::get<2>(state) + (std::get<1>(state) * 495LL) + (std::get<0>(state) * 495 * 2048));
}

faseOne faseOne::moveState(const Move& m) {
    cornerOrientCoord corner = this->corners.move(m);
    edgeOrientCoord edge = this->edges.move(m);
    UDSliceCoord slice = this->slice.move(m);
    faseOne newCoord{corner, edge, slice};
    return newCoord;
}

