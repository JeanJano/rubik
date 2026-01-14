#include "defs_explorer.hpp"

std::vector<Move> get_scramble(int ac, char** av) {
    if (ac != 2) {
        std::cout << UsageMessage << std::endl;
        return {};
    }

    try {
        std::vector<Move> scramble = parseMoves(av[1]);
        if (scramble.empty()) {
            std::cout << UsageMessage << std::endl;
            return {};
        }
        return scramble;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error parsing moves: " << e.what() << std::endl;
        return {};
    }
}

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
    int lastOfFirst = static_cast<int>(solvedFaseOne.back());
    int firstOfLast = static_cast<int>(GOneToRealMove(solvedFaseTwo.front()))
    if (lastOfFirst / 3 == firstOfLast / 3){
        
    }
    for (auto GOne: solvedFaseTwo){
        fin.push_back(GOneToRealMove(GOne));
    }
    return solveFaseOne::solutionToString(fin);
}


bool solve3x3 (int ac, char** av){
    auto start = std::chrono::high_resolution_clock::now();


    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return false;
    cubeCubie cube = get_scrambled_state(scramble);

    solveFaseOne solver = solveFaseOne(cube);
    std::vector<Move> first = solver.solve();
    std::cout << solver.solutionToString(first) << std::endl;

    cube = cube.severalMoves(first, cube);

    solveFaseTwo solver2 = solveFaseTwo(cube);
    std::vector<GOneMove> second = solver2.solve();
    std::cout << solver2.solutionToString(second) << std::endl;
     std::cout << getFinalString(first, second) << std::endl;



    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\n\n\nTiempo de ejecucion: "
              << elapsed.count()
              << " segundos\n";
    return true;
}

bool install (){
    auto start = std::chrono::high_resolution_clock::now();
    if (!ensureDirectoryExists(pruningFoldername))
        return false;
    cornerOrientCoord::moveTableToFile();
    edgeOrientCoord::moveTableToFile();
    UDSliceCoord::moveTableToFile();
    cornerPermCoord::moveTableToFile();
    edgePermCoord::moveTableToFile();
    UDSTwoCoord::moveTableToFile();
    faseOne::DoPruningTables();
    faseTwo::DoPruningTables();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\n Execution time: "
              << elapsed.count()
              << " segundos\n";
    return true;
}