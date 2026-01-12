#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"


solveFaseTwo::solveFaseTwo(const faseTwo& toSolve) {
    this->state.co = toSolve.corners.get_pure_coord();
    this->state.eo = toSolve.edges.get_pure_coord();
    this->state.s = toSolve.slice.get_pure_coord();

    loadMoveTables();
    loadPruningTables();
}

bool solveFaseTwo::loadMoveTables() {
    return
        loadBinary(movesFoldername + cornerPermMoveTableFilename,
                   &cornerPermMove[0][0], 40320 * 10) &&
        loadBinary(movesFoldername + edgePermMoveTableFilename,
                   &edgePermMove[0][0], 40320 * 10) &&
        loadBinary(movesFoldername + UDSTwoTableFilename,
                   &udSliceMove[0][0], 24 * 10);
}

bool solveFaseTwo::loadPruningTables() {
    return
        loadBinary(pruningFoldername + pruningCPSFilename,
                   pruneCPS, 40320 * 24) &&
        loadBinary(pruningFoldername + pruningEPSFilename,
                   pruneEPS, 40320 * 24);
}

int solveFaseTwo::CPS_index(int co, int s) {
    return co * 23 + s;
}

int solveFaseTwo::EPS_index(int eo, int s) {
    return eo * 23 + s;
}

void solveFaseTwo::applyMove(solveFaseTwoState& st, int m) {
    st.co = cornerPermMove[st.co][m];
    st.eo = edgePermMove[st.eo][m];
    st.s  = udSliceMove[st.s][m];
}

int solveFaseTwo::heuristic(const solveFaseTwoState& st) {
    int h1 = pruneCPS[CPS_index(st.co, st.s)];
    int h2 = pruneEPS[EPS_index(st.eo, st.s)];
    return (h1 > h2) ? h1 : h2;
}

inline bool sameFace(int m1, int m2) {
    if (5 < m2 && m2 <= 9)
        return true;
    return (m1 / 3) == (m2 / 3);
}

int solveFaseTwo::dfs(solveFaseTwoState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<GOneMove>& path)
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

        solveFaseTwoState backup = st;
        applyMove(st, m);

        path.push_back(static_cast<GOneMove>(m));

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

std::vector<GOneMove> solveFaseTwo::solve() {
    int bound = heuristic(state);

    std::vector<GOneMove> path;

    while (true) {
        int t = dfs(state, 0, bound, -1, path);

        if (t == FOUND)
            return path;

        if (t >= INF)
            throw std::runtime_error("No solution found in phase 1");

        bound = t;
    }
}

std::string solveFaseTwo::solutionToString(const std::vector<GOneMove>& path) {
    std::string res;
    for (GOneMove m : path) {
        if (!res.empty()) res += " ";
        res += moveToString(static_cast<GOneMove>(m));
    }
    return res;
}
