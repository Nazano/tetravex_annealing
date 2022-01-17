#include <algorithm>
#include <math.h>

#include "annealing_solver.hpp"

Solver::Solver(Board& b)
    : board(b)
{}


int Solver::solve(float lambda, float Tmin, float Tmax, float max_iter, bool verbose)
{
    srand(time(NULL));
    int max_E = board.get_count_boundaries();   // max possible energy
    float T = Tmax;
    float dim = board.get_board_dimension();
    std::vector<int> pieces_in_place = board.get_pieces_in_place();
    int n = board.get_board_size();
    
    // energy of the current board
    float E = get_energy(board.get_pieces(), dim);

    for (int i = 0; i < max_iter; i++)
    {

        if (verbose)
        {
            std::cout << "iteration " << i << ": E=" << E << ", T=" << T << "\n";
            std::cout << board;
        }

        // check if the solution is found
        if (E == max_E)
        {
            std::cout << board;
            return 0;
        }
        std::vector<Piece> new_pieces(board.get_pieces());
        

        // swap two pieces that are not fixed in place
		int i1 = rand() % board.get_board_size();
        while (std::find(pieces_in_place.begin(), pieces_in_place.end(), i1) != pieces_in_place.end()) {
            i1 = rand() % n;
        }
		int i2 = i1;
		while (i2 == i1 || std::find(pieces_in_place.begin(), pieces_in_place.end(), i2) != pieces_in_place.end())
			i2 = rand() % n;

		std::iter_swap(new_pieces.begin() + i1, new_pieces.begin() + i2);


        // get the energy from this new board
        float newE = get_energy(new_pieces, dim);
        
        // update the board
        float ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float condition = exp((float)(newE - E) / T);
        if (newE > E || ran < condition) {
            board.set_pieces(new_pieces);
            E = newE;
            if (verbose)
                std::cout << "accepted to swap " << i1 << " and " << i2 << "\n";
        }
        else if (verbose)
            std::cout << "refused to swap " << i1 << " and " << i2 << "\n";
        
        // update the temperature
        if (T > Tmin)
            T *= lambda;

    }

    return -1;  // too many iterations
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