#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"


solveFaseOne::solveFaseOne(const faseOne& toSolve) {
    this->state.co = toSolve.corners.get_pure_coord();
    this->state.eo = toSolve.edges.get_pure_coord();
    this->state.s = toSolve.slice.get_pure_coord();

    if (!loadMoveTables())
    throw std::runtime_error("Error loading move tables");

    if (!loadPruningTables())
    throw std::runtime_error("Error loading pruning tables");

    // std::cout << cornerOriMove[0][0] << std::endl;
    // std::cout << cornerOriMove[0][1] << std::endl;
    // std::cout << edgeOriMove[0][0] << std::endl;
    // std::cout << udSliceMove[0][0] << std::endl;

    // std::cout << int(pruneCOS[0]) << std::endl;
    // std::cout << int(pruneEOS[0]) << std::endl;


}

bool solveFaseOne::loadMoveTables() {
    return
        loadBinary(movesFoldername + cornerOriMoveTableFilename,
                   &cornerOriMove[0][0], 2187 * 18) &&
        loadBinary(movesFoldername + edgeOriMoveTableFilename,
                   &edgeOriMove[0][0], 2048 * 18) &&
        loadBinary(movesFoldername + UDSliceMoveTableFilename,
                   &udSliceMove[0][0], 495 * 18);
}

bool solveFaseOne::loadPruningTables() {
    return
        loadBinary(pruningFoldername + pruningCOSFilename,
                   pruneCOS, 2187 * 495) &&
        loadBinary(pruningFoldername + pruningEOSFilename,
                   pruneEOS, 2048 * 495);
}

int solveFaseOne::COS_index(int co, int s) {
    return co * 495 + s;
}

int solveFaseOne::EOS_index(int eo, int s) {
    return eo * 495 + s;
}

void solveFaseOne::applyMove(solveFaseOneState& st, int m) {
    // std::cout << " in apply move state A [" << st.co << " " << st.eo << " " << st.s << "]" << std::endl;
    st.co = cornerOriMove[st.co][m];
    st.eo = edgeOriMove[st.eo][m];
    st.s  = udSliceMove[st.s][m];
    // std::cout << " in apply move state B [" << st.co << " " << st.eo << " " << st.s << "]" << std::endl;
}

int solveFaseOne::heuristic(const solveFaseOneState& st) {
    int h1 = pruneCOS[COS_index(st.co, st.s)];
    int h2 = pruneEOS[EOS_index(st.eo, st.s)];
    return (h1 > h2) ? h1 : h2;
}

inline bool sameFace(int m1, int m2) {
    return (m1 / 3) == (m2 / 3);
}

int solveFaseOne::dfs(solveFaseOneState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<Move>& path)
{
    // std::cout << " state [" << st.co << " " << st.eo << " " << st.s << "] \n depth: "<< depth << "\n bound: " << bound << "\nlastMove: " << lastMove << "\npath size: " << path.size() << std::endl;
    int h = heuristic(st);
    int f = depth + h;

    if (f > bound)
        return f;

    if (h == 0)
        return FOUND;

    int minNextBound = INF;

    for (int m = 0; m < 18; ++m) {

        if (lastMove != -1 && sameFace(m, lastMove))
            continue;

        solveFaseOneState backup = st;
        applyMove(st, m);

        path.push_back(static_cast<Move>(m));

        int t = dfs(st, depth + 1, bound, m, path);
        // std::cout << " bound " << bound << "m " << m << "  " << path.size() << " t " << t << std::endl;

        if (t == FOUND)
            return FOUND;

        if (t < minNextBound)
            minNextBound = t;

        path.pop_back();
        st = backup;
    }

    return minNextBound;
}

std::vector<Move> solveFaseOne::solve() {
    int bound = heuristic(state);

    std::vector<Move> path;

    while (true) {
        int t = dfs(state, 0, bound, -1, path);

        if (t == FOUND)
            return path;

        if (t >= INF)
            throw std::runtime_error("No solution found in phase 1");

        bound = t;
    }
}

std::string solveFaseOne::solutionToString(const std::vector<Move>& path) {
    std::string res;
    for (Move m : path) {
        // std::cout << "move: " << moveToString(static_cast<Move>(m)) << std::endl;
        if (!res.empty()) res += " ";
        res += moveToString(static_cast<Move>(m));
    }
    return res;
}
