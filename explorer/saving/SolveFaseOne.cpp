#include "rubik_explorer.hpp"
#include "defs_explorer.hpp"


// void faseOne::initDeepth() {
//     // std::cout << "in initdeepth: " <<  std::get<2>(this->COSstate) << "   " << std::get<2>(this->EOSstate) << std::endl;
//     std::get<2>(this->COSstate) = faseOne::readPruning(pruningCOSFilename, faseOne::stateToIndex(this->COSstate));
//     std::get<2>(this->EOSstate) = faseOne::readPruning(pruningEOSFilename, faseOne::stateToIndex(this->EOSstate));
// }

// int faseOne::getHeuristic(int COSIndex, int EOSIndex){
//     // std::cout << "Getting heuristic for COSIndex: " << COSIndex << " EOSIndex: " << EOSIndex << std::endl;
//     uint8_t cosHeuristic = faseOne::readPruning(pruningCOSFilename, COSIndex);
//     uint8_t eosHeuristic = faseOne::readPruning(pruningEOSFilename, EOSIndex);
//     // std::cout << "COSIndex : " << COSIndex << " h = " << std::to_string(cosHeuristic) << " EOSIndex : " << EOSIndex << " h = " << std::to_string(eosHeuristic) << std::endl;
//     return std::max(cosHeuristic, eosHeuristic);
// }

// std::string faseOne::solveFaseOne(){
//     // namespace fs = std::filesystem;
//     faseOne toSolve = *this;
//     std::string ret = "";
    
//     int limit = faseOne::getHeuristic(faseOne::stateToIndex(toSolve.COSstate),
//                                      faseOne::stateToIndex(toSolve.EOSstate));
//     // int ctrl = 0; 
//     while (ret.empty()){
//     // while (ret.empty() && ctrl < 2){

//         std::cout << "Rastreando limite: " << limit << std::endl;
        
        
//         //COSstate, EOSstate, heuristic, stepsDone, movesDone
//         std::queue<std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string>> IDA;
//         std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> startState = 
//         std::make_tuple(std::make_tuple(std::get<0>(toSolve.COSstate),std::get<1>(toSolve.COSstate)),
//                         std::make_tuple(std::get<0>(toSolve.EOSstate),std::get<1>(toSolve.EOSstate)),
//                         faseOne::getHeuristic(faseOne::stateToIndex(toSolve.COSstate),
//                                               faseOne::stateToIndex(toSolve.EOSstate)),
//                         0,
//                         "");
//         IDA.push(startState);
//         int auxlimit = std::numeric_limits<int>::max();
//         while(!IDA.empty()){
//             auto currentState = IDA.front();
//             if (std::get<2>(currentState) == 0){
//                 ret = std::get<4>(currentState);
//                 break;
//             }
//             // std::cout << "Rastreando current:!!!!!!!!! limite:"  << limit << std::endl;
//             // faseOne::showSolveState(currentState);
//             for(int i = 0; i < 18; ++i){
//                 std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> newState = faseOne::moveSolveState(currentState, static_cast<Move>(i));
//                 // if (std::get<2>(newState) == 0){
//                 //     ret = std::get<4>(currentState);
//                 //     break;
//                 // }
//                 int newLimitCandid = std::get<2>(newState) + std::get<3>(newState);
//                 if (newLimitCandid > limit)
//                 {   
//                     if (newLimitCandid <= auxlimit) auxlimit = newLimitCandid;
//                     // std::cout << " limite cambiado: " << auxlimit << std::endl;
//                 }
//                 else {
//                     IDA.push(newState);
//                 }
//             }
//             IDA.pop();
//         }
//         limit = auxlimit;
//         // std::cout << "Nuevo limite: " << limit << std::endl;
//         // ctrl++;
//     }
//     return ret;
// }

// std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> faseOne::moveSolveState(const std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string>& solveState, const Move& m) {
//     std::tuple<std::tuple<int, int> , std::tuple<int, int>, int, int, std::string> result = solveState;

//     // std::cout << "Rastreando result: " << std::endl;
//     // faseOne::showSolveState(result);
//     std::get<0>(std::get<0>(result)) = fase_one_coord_from_file(std::get<0>(std::get<0>(solveState)), m, UDSliceMoveTableFilename);
//     std::get<1>(std::get<0>(result)) = fase_one_coord_from_file(std::get<1>(std::get<0>(solveState)), m, cornerOriMoveTableFilename);
//     std::get<0>(std::get<1>(result)) = fase_one_coord_from_file(std::get<0>(std::get<1>(solveState)), m, UDSliceMoveTableFilename);
//     std::get<1>(std::get<1>(result)) = fase_one_coord_from_file(std::get<1>(std::get<1>(solveState)), m, edgeOriMoveTableFilename);
//     std::get<2>(result) = faseOne::getHeuristic(faseOne::stateToIndex(std::get<0>(result)), faseOne::stateToIndex(std::get<1>(result)));
//     std::get<3>(result)++;
//     if (std::get<4>(result).empty()){std::get<4>(result) += moveToString(m);}
//     else{std::get<4>(result) += (" " + moveToString(m));}
//     // std::cout << "Rastreando result fin: \n" << std::endl;
//     // faseOne::showSolveState(result);
//     return result;
// }

// void faseOne::printState(std::tuple<int, int, int> state){
//     std::cout << std::get<0>(state) << " " << std::get<1>(state) << " " << std::get<2>(state) << " " << std::endl;
// }

// void faseOne::showSolveState(std::tuple<std::tuple<int, int>, std::tuple<int, int>, int, int, std::string> solveState){
//     std::cout << "COS: " << std::get<0>(std::get<0>(solveState)) << " " << std::get<1>(std::get<0>(solveState)) << std::endl;
//     std::cout << "EOS: " << std::get<0>(std::get<1>(solveState)) << " " << std::get<1>(std::get<1>(solveState)) << std::endl;
//     std::cout << "Heuristic: " << std::get<2>(solveState) << std::endl;
//     std::cout << "Steps done: " << std::get<3>(solveState) << std::endl;
//     std::cout << "Moves done: " << std::get<4>(solveState) << std::endl;
// }

solveFaseOne::solveFaseOne(const faseOne& toSolve) {
    this->state.co = toSolve.corners.get_pure_coord();
    this->state.eo = toSolve.edges.get_pure_coord();
    this->state.s = toSolve.slice.get_pure_coord();
}