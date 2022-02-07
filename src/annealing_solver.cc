#include <algorithm>
#include <math.h>

#include "annealing_solver.hpp"

Solver::Solver(Board& b)
    : board(b)
{}


int Solver::solve(float lambda, float Tmin, float Tmax, float max_iter, bool verbose)
{
    srand(time(NULL));
    int max_E = board.get_count_boundaries();       // max possible energy
    float T = Tmax;                                 // current temperature
    
    float dim = board.get_board_dimension();        // board dimensions
    int n = board.get_board_size();

    float E = get_energy(board.get_pieces(), dim);  // energy of the current board
    
    std::vector<int> pieces_in_place = board.get_pieces_in_place(); // the pieces that we can't move

    for (int i = 0; i < max_iter; i++)
    {
        // check if we reached the solution
        if (E == max_E)
        {
            return 0;
        }

        // swap two pieces together
        std::vector<Piece> new_pieces = swap_random_pieces(pieces_in_place, board.get_pieces());


        // get the energy from this new board
        float newE = get_energy(new_pieces, dim);
        
        // update the board
        float ran = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);  // random float between 0 and 1
        float condition = exp((float)(newE - E) / T);
        if (verbose) {
            std::cout << "iteration " << i << " : T=" << T
                      << ", [old_E=" << E << " | new_E=" << newE << "]\n";
            if (newE < E)
                std::cout << "    transition probability : " << condition << "\n";
        }
        if (newE > E || ran < condition) {
            board.set_pieces(new_pieces);
            E = newE;
            if (verbose)
                std::cout << "ACCEPTED to swap\n\n";
        }
        else if (verbose)
            std::cout << "REFUSED to swap\n\n";
        
        // update the temperature
        if (T > Tmin)
            T *= lambda;

    }

    return -1;  // solution not found
}

std::vector<Piece> Solver::swap_random_pieces(std::vector<int> pieces_in_place, std::vector<Piece> pieces)
{
    int n = board.get_board_size(); 
    std::vector<Piece> new_pieces(pieces);
    int i1 = rand() % board.get_board_size();
    while (std::find(pieces_in_place.begin(), pieces_in_place.end(), i1) != pieces_in_place.end()) {
        i1 = rand() % n;
    }
    int i2 = i1;
    while (i2 == i1 || std::find(pieces_in_place.begin(), pieces_in_place.end(), i2) != pieces_in_place.end())
        i2 = rand() % n;

    std::iter_swap(new_pieces.begin() + i1, new_pieces.begin() + i2);

    return new_pieces;
}

int Solver::get_energy(std::vector<Piece> pieces, int dim)
{
    return count_matching_boundaries(pieces, dim);
}


int Solver::count_matching_boundaries(std::vector<Piece> pieces, int dim)
{
    int matches = 0;
    int total_boundaries = 0;
    for (int i = 0; i < dim * dim; i++) {
        if (i % dim > 0)    // check on the left
        {
            matches += (int)check_matching_boundaries(pieces, i - 1, i, dim);
            total_boundaries++;
        }
        if (i >= dim)       // check above
        {
            matches += (int)check_matching_boundaries(pieces, i - dim, i, dim);
            total_boundaries++;
        }
    }
    return matches;
}

bool Solver::check_matching_boundaries(std::vector<Piece> pieces, int a, int b, int dim)
{
    
    if (a > b) {    // makes 'b' the largest number between the two
        int tmp = b;
        b = a;
        a = tmp;
    }
    return ((pieces[a].R() == pieces[b].L()     // horizontal
                && a + 1 == b)
        ||  (pieces[a].B() == pieces[b].T()     // vertical
                && a + dim == b));
}