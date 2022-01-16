#include <iostream>

#include "annealing_solver.hpp"

int main(int argc, char const *argv[])
{
    auto board = Board();
    board.parse("../in.txt");
    std::cout << board;

    Solver s{board};
    s.solve();

    std::cout << s.count_matching_boundaries() << "\n";
    return 0;
}
