#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"


solveFaseOne::solveFaseOne(const faseOne& toSolve) {
    this->state.co = toSolve.corners.get_pure_coord();
    this->state.eo = toSolve.edges.get_pure_coord();
    this->state.s = toSolve.slice.get_pure_coord();

    loadMoveTables();
    loadPruningTables();
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
    st.co = cornerOriMove[st.co][m];
    st.eo = edgeOriMove[st.eo][m];
    st.s  = udSliceMove[st.s][m];
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
                      std::vector<int>& path)
{
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

        path.push_back(m);

        int t = dfs(st, depth + 1, bound, m, path);

        if (t == FOUND)
            return FOUND;

        if (t < minNextBound)
            minNextBound = t;

        path.pop_back();
        st = backup;
    }

    return minNextBound;
}

std::vector<int> solveFaseOne::solve() {
    int bound = heuristic(state);

    std::vector<int> path;

    while (true) {
        int t = dfs(state, 0, bound, -1, path);

        if (t == FOUND)
            return path;

        if (t >= INF)
            throw std::runtime_error("No solution found in phase 1");

        bound = t;
    }
}

std::string solveFaseOne::solutionToString(const std::vector<int>& path) {
    std::string res;
    for (int m : path) {
        if (!res.empty()) res += " ";
        res += moveToString(static_cast<Move>(m));
    }
    return res;
}
