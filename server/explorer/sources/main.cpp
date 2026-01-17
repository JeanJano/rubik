
#include "defs_explorer.hpp"

int main(int ac, char** av) {
    initOptions opt = init(ac, av);
    bool retCtrl = false;
    
    // auto start = std::chrono::high_resolution_clock::now();
    if (opt.init)
        retCtrl = install();
    else if (opt.solve3)
        retCtrl = solve3x3(opt.scramble);
    else if (opt.solve2)
        retCtrl = solve2x2(opt.scramble);
    
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "\n Execution time: " 
    //           << elapsed.count() << " seconds\n";
    return retCtrl;
}