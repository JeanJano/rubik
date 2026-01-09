#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"

// void faseOne::initDeepth() {
//     faseOne current = *this;

//     std::get<2>(current.COSstate) = faseOne::readPruning(pruningCOSFilename, faseOne::stateToIndex(current.COSstate));
//     std::get<2>(current.EOSstate) = faseOne::readPruning(pruningEOSFilename, faseOne::stateToIndex(current.EOSstate));
// }

int faseOne::getHeuristic(int COSIndex, int EOSIndex){
    uint8_t cosHeuristic = faseOne::readPruning(pruningCOSFilename, COSIndex);
    uint8_t eosHeuristic = faseOne::readPruning(pruningEOSFilename, EOSIndex);
    std::cout << "COSIndex : " << COSIndex << std::to_string(cosHeuristic) << " EOSIndex : " << EOSIndex << std::to_string(eosHeuristic) << std::endl;
    return std::max(cosHeuristic, eosHeuristic);
}

std::string faseOne::solveFaseOne(){
    namespace fs = std::filesystem;
    // faseOne toSolve = *this;
    std::string ret = "solve|||";
    
    // int limit = faseOne::getHeuristic(faseOne::stateToIndex(toSolve.COSstate),
    //                                  faseOne::stateToIndex(toSolve.EOSstate));
    //                                  return std::to_string(limit);
    // while (ret.empty()){
    //     //COSstate, EOSstate, heuristic, stepsDone, movesDone
    //     std::queue<std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string>> IDA;
    //     std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> startState = 
    //     std::make_tuple(std::make_tuple(std::get<0>(toSolve.COSstate),std::get<1>(toSolve.COSstate)),
    //                     std::make_tuple(std::get<0>(toSolve.EOSstate),std::get<1>(toSolve.EOSstate)),
    //                     faseOne::getHeuristic(faseOne::stateToIndex(toSolve.COSstate),
    //                                           faseOne::stateToIndex(toSolve.EOSstate)),
    //                     0,
    //                     "");
    //     IDA.push(startState);
    //     int auxlimit = std::numeric_limits<int>::max();
    //     while(!IDA.empty()){
    //         auto currentState = IDA.front();
    //         if (std::get<2>(currentState) == 0){
    //             ret = std::get<4>(currentState);
    //             break;
    //         }
    //         for(int i = 0; i < 18; ++i){
    //             std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> newState = faseOne::moveSolveState(currentState, static_cast<Move>(i));
    //             int newLimitCandid = std::get<2>(newState) + std::get<3>(newState);
    //             if (newLimitCandid > limit)
    //             {
    //                 if (newLimitCandid <= auxlimit) auxlimit = newLimitCandid;
    //             }
    //             else {
    //                 IDA.push(newState);
    //             }
    //         }
    //         IDA.pop();
    //     }
    //     limit = auxlimit;
    // }
    return ret;
}

std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> faseOne::moveSolveState(const std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string>& solveState, const Move& m) {
    std::tuple<std::tuple<int, int> , std::tuple<int, int>, int, int, std::string> result = solveState;

    std::get<0>(std::get<0>(result)) = fase_one_coord_from_file(std::get<0>(std::get<0>(solveState)), m, UDSliceMoveTableFilename);
    std::get<1>(std::get<0>(result)) = fase_one_coord_from_file(std::get<1>(std::get<0>(solveState)), m, cornerOriMoveTableFilename);
    std::get<0>(std::get<1>(result)) = std::get<0>(std::get<0>(result));
    std::get<1>(std::get<1>(result)) = fase_one_coord_from_file(std::get<1>(std::get<0>(solveState)), m, edgeOriMoveTableFilename);
    std::get<2>(result) = faseOne::getHeuristic(faseOne::stateToIndex(std::get<0>(result)), faseOne::stateToIndex(std::get<1>(result)));
    std::get<3>(result)++;
    if (std::get<4>(result).empty()){std::get<4>(result) += moveToString(m);}
    else{std::get<4>(result) += (" " + moveToString(m));}
    return result;
}