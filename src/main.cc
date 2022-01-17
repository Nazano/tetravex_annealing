#include <iostream>

#include "annealing_solver.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    { 
        std::cout << "Usage: [input file] [out file]\n";
        return -1;
    }

    std::string in_file = argv[1];
    std::string out_file = argv[2];

    auto board = Board();
    board.parse(in_file);
    std::cout << board;

    Solver s{board};

    int result = s.solve(0.99, 0.1, 10, 100000, true);

    if (result == 0)
        std::cout << "Solution found :\n";
    else
        std::cout << "Solution not found in time :\n";

    std::cout << s.get_board();

    s.get_board().save(out_file);

    return 0;
}
