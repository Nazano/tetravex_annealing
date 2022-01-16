#include "annealing_solver.hpp"

Solver::Solver(Board& b)
    : board(b)
{}

int Solver::solve()
{
    return -1;
}

bool Solver::check_matching_boundaries(int a, int b)
{
    
    if (a > b) {    // makes 'b' the largest number between the two
        int tmp = b;
        b = a;
        a = tmp;
    }
    return ((board.get_pieces()[a].R() == board.get_pieces()[b].L()     // horizontal
                && a + 1 == b)
        ||  (board.get_pieces()[a].B() == board.get_pieces()[b].T()     // vertical
                && a + board.get_board_dimension() == b));
}

int Solver::count_matching_boundaries()
{
    int dim = board.get_board_dimension();
    int size = board.get_board_size();

    int matches = 0;
    int total_boundaries = 0;
    for (int i = 0; i < size; i++) {
        if (i % dim > 0)    // check on the left
        {
            matches += (int)check_matching_boundaries(i - 1, i);
            total_boundaries++;
        }
        if (i >= dim)       // check above
        {
            matches += (int)check_matching_boundaries(i - dim, i);
            total_boundaries++;
        }
    }
    std::cout << matches << " / " << total_boundaries << " matches\n";      //
    return matches;
}