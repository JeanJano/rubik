#include "defs_explorer.hpp"



bool ensureDirectoryExists(const std::string& path) {
    namespace fs = std::filesystem;

    try {
        if (fs::exists(path)) {
            return fs::is_directory(path);
        } else {
            return fs::create_directories(path);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}


std::string getFinalString(const std::vector<Move>& solvedFaseOne, const std::vector<GOneMove>& solvedFaseTwo){
    std::vector<Move> fin = solvedFaseOne;
    std::vector<GOneMove> aux = solvedFaseTwo;
    if (!fin.empty() && !aux.empty()) {
        int lastOfFirst = static_cast<int>(fin.back());
        int firstOfLast = static_cast<int>(GOneToRealMove(aux.front()));

        if (lastOfFirst / 3 == firstOfLast / 3) {
            fin.pop_back();
            aux.erase(aux.begin());

            if (lastOfFirst % 3 == 0 && firstOfLast % 3 == 0)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3 + 1));
            else if (lastOfFirst % 3 == 0 && firstOfLast % 3 == 1)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3 + 2));
            else if (lastOfFirst % 3 == 1 && firstOfLast % 3 == 0)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3 + 2));
            else if (lastOfFirst % 3 == 1 && firstOfLast % 3 == 2)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3));
            else if (lastOfFirst % 3 == 2 && firstOfLast % 3 == 1)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3));
            else if (lastOfFirst % 3 == 2 && firstOfLast % 3 == 2)
                fin.push_back(static_cast<Move>((lastOfFirst / 3) * 3 + 1));
        }
    }
    for (auto GOne: aux){
        fin.push_back(GOneToRealMove(GOne));
    }
    return solveFaseOne::solutionToString(fin);
}

bool install (){
    if (!ensureDirectoryExists(pruningFoldername))
        return false;

    cornerOrientCoord::moveTableToFile();
    edgeOrientCoord::moveTableToFile();
    UDSliceCoord::moveTableToFile();
    cornerPermCoord::moveTableToFile();
    edgePermCoord::moveTableToFile();
    UDSTwoCoord::moveTableToFile();
    cornerPermCoordTwo::moveTableToFile();
    faseOne::DoPruningTables();
    faseTwo::DoPruningTables();
    twoByTwo::DoPruningTables();
    
    return true;
}

bool solve3x3 (const std::vector<Move>& scramble){
    cubeCubie cube = getScrambledState(scramble);

    solveFaseOne solver = solveFaseOne(cube);
    std::vector<Move> first = solver.solve();

    cube = cube.severalMoves(first, cube);

    solveFaseTwo solver2 = solveFaseTwo(cube);
    std::vector<GOneMove> second = solver2.solve();
    std::cout << getFinalString(first, second) << std::endl;

    return true;
}

bool solve2x2(const std::vector<Move>& scramble){
    // (void)scramble;
    cubeCubie cube = getScrambledState(scramble);

    // cornerPermCoordTwo::printMoveTable();
    // twoByTwo::printNonZeroPruningValues(cornerPermTwoMoveTableFilename,100,0);
    solveTwoByTwo solver = solveTwoByTwo(cube);
    // (void)solver;
    std::vector<Move> sol = solver.solve();

    std::cout << solveFaseOne::solutionToString(sol) << std::endl;

    return true;
}