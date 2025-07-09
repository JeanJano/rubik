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
    std::vector<Move> scramble = get_scramble(ac, av);
    if (scramble.empty())
        return 1;
    cubeCubie scrambledCube = get_scrambled_state(scramble);

    // cornerOrientCoord coordOne = cornerOrientCoord(scrambledCube);
    // std::cout << "init pure coord " << coordOne.get_pure_coord() << std::endl;
    // //--------------------------------------
    // cornerOrientCoord::move_table_to_file();
    // for (int i = 0; i < 18; i++){
    //     std::cout << "vamos arriba: " << corn_ori_coord_from_file(coordOne, i) << std::endl;
    // }
    // cornerOrientCoord::print_move_table();

    
    // edgeOrientCoord coordTwo = edgeOrientCoord(scrambledCube);
    // coordTwo.print_explicit_edge_ori_coord();
    // std::cout << "init pure coord " << coordTwo.get_pure_coord() << std::endl;
    // //--------------------------------------
    // edgeOrientCoord::move_table_to_file();
    // for (int i = 0; i < 18; i++){
    //     int pure = edge_ori_coord_from_file(coordTwo, i);
    //     std::cout << "vamos arriba: "<< i << "|" << pure  << std::endl;
    //     edgeOrientCoord result = edgeOrientCoord::from_pure_coord(pure);
    //     std::cout << "vamos arriba 2: " << std::endl;
    //     result.print_explicit_edge_ori_coord2();
    // }
    // edgeOrientCoord::print_move_table();

    UDSliceCoord coordThree = UDSliceCoord(scrambledCube);
    coordThree.print_explicit_udslice_ori_coord();
    for (int i = 0; i < 500; ++i){
        coordThree = coordThree.nextExplicitCoord();
        coordThree.print_explicit_udslice_ori_coord();
    }
}
