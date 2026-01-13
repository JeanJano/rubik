#include "rubik_explorer.hpp"
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



int main(int ac, char** av) {
    auto start = std::chrono::high_resolution_clock::now();




    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return 1;
    cubeCubie scrambledCube = get_scrambled_state(scramble);
    // std::cout << "aca 1" << std::endl;
    // print_cubie_state(scrambledCube);
    // cornerOrientCoord::moveTableToFile();
    // edgeOrientCoord::moveTableToFile();
    // UDSliceCoord::moveTableToFile();
    // cornerPermCoord::moveTableToFile();
    // edgePermCoord::moveTableToFile();
    // UDSTwoCoord::moveTableToFile();

    faseOne fase1 = faseOne(cornerOrientCoord(scrambledCube), edgeOrientCoord(scrambledCube), UDSliceCoord(scrambledCube));
    solveFaseOne solver = solveFaseOne(fase1);
    std::vector<Move> first = solver.solve();
    std::cout << solver.solutionToString(first) << std::endl;
    scrambledCube = scrambledCube.severalMoves(first, scrambledCube);


    faseTwo fase2 = faseTwo(cornerPermCoord(scrambledCube), edgePermCoord(scrambledCube), UDSTwoCoord(scrambledCube));
    // fase2.DoPruningTables();
    // (void)fase2;
    // faseTwo::printNonZeroPruningValues(pruningCPSFilename, 17120 ,17110);
    // faseTwo::printNonZeroPruningValues(pruningEPSFilename, 12290 ,12280);

    // cornerPermCoord::printMoveTable();
    // edgePermCoord::printMoveTable();
    // UDSTwoCoord::printMoveTable();



    solveFaseTwo solver2 = solveFaseTwo(fase2);
    // (void)solver2;
    std::vector<GOneMove> second = solver2.solve();
    std::cout << solver2.solutionToString(second) << std::endl;
    // fase2.DoPruningTables();
    // edgePermCoord::printMoveTable();
    // cornerPermCoord::printMoveTable();
    // UDSTwoCoord::printMoveTable();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\n\n\nTiempo de ejecucion: "
              << elapsed.count()
              << " segundos\n";
}
