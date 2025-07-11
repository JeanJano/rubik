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

    //--------------------------------------
    cornerOrientCoord coordOne = cornerOrientCoord(scrambledCube);
    std::cout << "init pure coord corn " << coordOne.get_pure_coord() << std::endl;
    coordOne.print_explicit_corn_ori_coord2();
    cornerOrientCoord::move_table_to_file();
    for (int i = 0; i < 18; i++){
        uint16_t pure = fase_one_coord_from_file(coordOne, i, cornerOriMoveTableFilename);
        std::cout << "vamos arriba corners: " << pure << std::endl;
        cornerOrientCoord exp = cornerOrientCoord::from_pure_coord(pure);
        exp.print_explicit_corn_ori_coord2();

    }
    cornerOrientCoord::print_move_table();
    // //--------------------------------------
    edgeOrientCoord coordTwo = edgeOrientCoord(scrambledCube);
    std::cout << "init pure coord edge " << coordTwo.get_pure_coord() << std::endl;
    coordTwo.print_explicit_edge_ori_coord2();
    edgeOrientCoord::move_table_to_file();
    for (int i = 0; i < 18; i++){
        uint16_t pure = fase_one_coord_from_file(coordTwo, i, edgeOriMoveTableFilename);
        std::cout << "vamos arriba edges: " << pure << std::endl;
        edgeOrientCoord exp = edgeOrientCoord::from_pure_coord(pure);
        exp.print_explicit_edge_ori_coord2();
    }
    edgeOrientCoord::print_move_table();
    //-------------------------------------
    UDSliceCoord coordThree = UDSliceCoord(scrambledCube);
    std::cout << "init pure coord udslice " << coordThree.get_pure_coord() << std::endl;
    coordThree.print_explicit_udslice_ori_coord2();
    UDSliceCoord::move_table_to_file();
    for (int i = 0; i < 18; ++i){
        uint16_t pure = fase_one_coord_from_file(coordThree, i, UDSliceMoveTableFilename);
        std::cout << "vamos arriba udslice: " << pure << std::endl;
        UDSliceCoord exp = UDSliceCoord::from_pure_coord(pure);
        exp.print_explicit_udslice_ori_coord2();
    }
    //-------------------------------------
    UDSliceCoord::print_move_table();
}
