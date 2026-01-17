
#include "defs_explorer.hpp"

solveTwoByTwo::solveTwoByTwo(const cubeCubie& cube){
    this->state.co = cornerOrientCoord(cube).getPureCoord();
    this->state.cp = cornerPermCoordTwo(cube).getPureCoord();

    if (!loadMoveTables())
        throw std::runtime_error("Error loading move tables");

    if (!loadPruningTables())
        throw std::runtime_error("Error loading pruning tables");

}

bool solveTwoByTwo::loadMoveTables() {
    return
        loadBinary(movesFoldername + cornerOriMoveTableFilename,
                   &cornerOriMove[0][0], 2187 * 18) &&
        loadBinary(movesFoldername + cornerPermTwoMoveTableFilename,
                   &cornerPermMove[0][0], 40320 * 18);
}

bool solveTwoByTwo::loadPruningTables() {
    return
        loadBinary(pruningFoldername + pruningCOFilename,
                   pruneCO, 2187) &&
        loadBinary(pruningFoldername + pruningCPFilename,
                   pruneCP, 40320);
}

void solveTwoByTwo::applyMove(solveTwoByTwoState& st, int m) {
    st.co = cornerOriMove[st.co][m];
    st.cp = cornerPermMove[st.cp][m];
}

int solveTwoByTwo::heuristic(const solveTwoByTwoState& st) {
    int h1 = pruneCO[st.co];
    int h2 = pruneCP[st.cp];
    return (h1 > h2) ? h1 : h2;
}


inline int faceOf(int m) {
    if (m <= 2) return 0; // U
    if (m <= 5) return 1; // D
    return m;             // L2 R2 F2 B2
}

inline bool sameFace(int m1, int m2) {
    return faceOf(m1) == faceOf(m2);
}


int solveTwoByTwo::dfs(solveTwoByTwoState& st,
                      int depth,
                      int bound,
                      int lastMove,
                      std::vector<Move>& path)
{
    // if (depth == 5) return FOUND;
    int h = heuristic(st);
    int f = depth + h;

    if (f > bound)
        return f;

    if (h == 0)
        return FOUND;

    int minNextBound = INF;

        // std::cout << "\n\n----------\ninit state [" << st.cp << " " << st.ep << " " << st.s << "] \nheuristic : " << h  << "\ndepth: "<< depth << "\nbound: " << bound << "\nlastMove: " << moveToString(static_cast<Move>(lastMove)) << "\npath: " << solveTwoByTwo::solutionToString(path) << std::endl;
    for (int m = 0; m < 18; ++m) {

        if (lastMove != -1 && sameFace(m, lastMove))
            continue;

        solveTwoByTwoState backup = st;
        applyMove(st, m);

        path.push_back(static_cast<Move>(m));
        
        int t = dfs(st, depth + 1, bound, m, path);
        // std::cout << "\n\nmove done: " << m << "  middle state [" << st.cp << " " << st.ep << " " << st.s << "] \nheuristic : " << heuristic(st)  << "\ndepth: "<< depth + 1 << "\nbound: " << bound << "\nlastMove: " << moveToString(static_cast<Move>(lastMove)) << "\npath: " << solveTwoByTwo::solutionToString(path) << "\nt: " << t << std::endl;

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

std::vector<Move> solveTwoByTwo::solve() {
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

std::string solveTwoByTwo::solutionToString(const std::vector<Move>& path) {
    // std::cout << "aca 2" << std::endl;
    std::string res;
    for (Move m : path) {
        if (!res.empty()) res += " ";
        res += moveToString(static_cast<Move>(m));
    }
    return res;
}
