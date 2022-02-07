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
    std::cout << "initial board : \n" << board;

    Solver s{board};
    int dim = board.get_board_dimension();
    
    float lambda = 0.9999;
    if (dim == 5)
        lambda = 0.999999;
    if (dim == 6)
        lambda = 0.9999999;

    int result = s.solve(lambda, 0.25, 0.8, 50000000, true);

    if (result == 0)
        std::cout << "Solution found :\n";
    else
        std::cout << "Solution not found in time :\n";

    std::cout << s.get_board();

    s.get_board().save(out_file);

    return 0;
}
