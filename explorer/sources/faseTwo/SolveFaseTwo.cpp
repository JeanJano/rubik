#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

void printState(int c,int e ,int s){
    std::cout << "state: [" << c << ", " << e << ", " << s << "]" << std::endl;
}

solveFaseTwo::solveFaseTwo(const faseTwo& toSolve) {
    this->state.cp = toSolve.corners.get_pure_coord();
    this->state.ep = toSolve.edges.get_pure_coord();
    this->state.s = toSolve.slice.get_pure_coord();

    // std::cout << "in solveFaseTwo: " << std::endl;
    // printState(this->state.cp, this->state.ep, this->state.s);
    loadMoveTables();
    loadPruningTables();
    // std::cout << "in solveFaseTwo: " << std::endl;
    // std::cout << static_cast<int>(pruneEPS[512*24 + 1]) << std::endl;
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

int solveFaseTwo::CPS_index(int cp, int s) {
    return cp * 24 + s;
}

int solveFaseTwo::EPS_index(int ep, int s) {
    return ep * 24 + s;
}

void solveFaseTwo::applyMove(solveFaseTwoState& st, int m) {
    st.cp = cornerPermMove[st.cp][m];
    st.ep = edgePermMove[st.ep][m];
    st.s  = udSliceMove[st.s][m];
}

int solveFaseTwo::heuristic(const solveFaseTwoState& st) {
    int h1 = pruneCPS[CPS_index(st.cp, st.s)];
    int h2 = pruneEPS[EPS_index(st.ep, st.s)];
    return (h1 > h2) ? h1 : h2;
}

// inline bool sameFace(int m1, int m2) {
//     if (5 < m2 && m2 <= 9)
//         return true;
//     return (m1 / 3) == (m2 / 3);
// }


inline int faceOf(int m) {
    if (m <= 2) return 0; // U
    if (m <= 5) return 1; // D
    return m;             // L2 R2 F2 B2
}

inline bool sameFace(int m1, int m2) {
    return faceOf(m1) == faceOf(m2);
}


int solveFaseTwo::dfs(solveFaseTwoState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<GOneMove>& path)
{
    // if (depth == 5) return FOUND;
    int h = heuristic(st);
    int f = depth + h;

    if (f > bound)
        return f;

    if (h == 0)
        return FOUND;

    int minNextBound = INF;

        // std::cout << "\n\n----------\ninit state [" << st.cp << " " << st.ep << " " << st.s << "] \nheuristic : " << h  << "\ndepth: "<< depth << "\nbound: " << bound << "\nlastMove: " << moveToString(static_cast<GOneMove>(lastMove)) << "\npath: " << solveFaseTwo::solutionToString(path) << std::endl;
    for (int m = 0; m < 10; ++m) {

        if (lastMove != -1 && sameFace(m, lastMove))
            continue;

        solveFaseTwoState backup = st;
        applyMove(st, m);

        path.push_back(static_cast<GOneMove>(m));
        
        int t = dfs(st, depth + 1, bound, m, path);
        // std::cout << "\n\nmove done: " << m << "  middle state [" << st.cp << " " << st.ep << " " << st.s << "] \nheuristic : " << heuristic(st)  << "\ndepth: "<< depth + 1 << "\nbound: " << bound << "\nlastMove: " << moveToString(static_cast<GOneMove>(lastMove)) << "\npath: " << solveFaseTwo::solutionToString(path) << "\nt: " << t << std::endl;

        if (t == FOUND)
            return FOUND;

        if (t < minNextBound)
            minNextBound = t;

        path.pop_back();
        st = backup;
    }
        // std::cout << "apres backup ret*************************" << std::endl;

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
