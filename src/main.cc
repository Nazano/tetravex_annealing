#include <iostream>

#include "annealing_solver.hpp"

int main(int argc, char const *argv[])
{
    auto board = Board();
    board.parse("../3x3.txt");
    std::cout << board;

    Solver s{board};

    int result = s.solve(0.99, 0.1, 10, 100000, true);

    if (result == 0)
        std::cout << "Solution found :\n";
    else
        std::cout << "Solution not found in time :\n";

    std::cout << s.get_board();

    return 0;
}
