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

bool solve3x3 (int ac, char** av){
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return false;
    cubeCubie scrambledCube = get_scrambled_state(scramble);
    faseOne fase1 = faseOne(cornerOrientCoord(scrambledCube), edgeOrientCoord(scrambledCube), UDSliceCoord(scrambledCube));
    solveFaseOne solver = solveFaseOne(fase1);
    std::vector<Move> first = solver.solve();
    std::cout << solver.solutionToString(first) << std::endl;

    scrambledCube = scrambledCube.severalMoves(first, scrambledCube);
    faseTwo fase2 = faseTwo(cornerPermCoord(scrambledCube), edgePermCoord(scrambledCube), UDSTwoCoord(scrambledCube));
    solveFaseTwo solver2 = solveFaseTwo(fase2);
    std::vector<GOneMove> second = solver2.solve();
    std::cout << solver2.solutionToString(second) << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\n\n\nTiempo de ejecucion: "
              << elapsed.count()
              << " segundos\n";
    return true;
}

bool install (int ac, char** av){
    auto start = std::chrono::high_resolution_clock::now();
    if (!ensureDirectoryExists(pruningFoldername))
        return false;
    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return false;
    cubeCubie scrambledCube = get_scrambled_state(scramble);
    cornerOrientCoord::moveTableToFile();
    edgeOrientCoord::moveTableToFile();
    UDSliceCoord::moveTableToFile();
    cornerPermCoord::moveTableToFile();
    edgePermCoord::moveTableToFile();
    UDSTwoCoord::moveTableToFile();

    faseOne fase1 = faseOne(cornerOrientCoord(scrambledCube), edgeOrientCoord(scrambledCube), UDSliceCoord(scrambledCube));
    fase1.DoPruningTables();

    faseTwo fase2 = faseTwo(cornerPermCoord(scrambledCube), edgePermCoord(scrambledCube), UDSTwoCoord(scrambledCube));
    fase2.DoPruningTables();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\n\n\nTiempo de ejecucion: "
              << elapsed.count()
              << " segundos\n";
    return true;
}