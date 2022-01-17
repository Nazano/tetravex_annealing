#include "game.hpp"

class Solver
{
    private:
        float T;
        Board board;
    public:
        Solver(Board&);

        /**
         * Solve the Board with a simulated annealing.
         * Returns 0 if the solution was found, -1 otherwise
         */
        int solve(float lambda, float Tmin, float Tmax, float max_iter, bool verbose);

        /**
         * returns the energy of a board, which corresponds
         * to the number of matching pieces
         */
        int get_energy(std::vector<Piece> pieces, int dim);

        /**
         * Checks if two neighbour tiles match together.
         * 
         * 'a' and 'b' should be the indexes of two neighbour tiles.
         * If they are not neighbours, this function returns false.
         */
        bool check_matching_boundaries(std::vector<Piece> pieces, int a, int b, int dim);
        /**
         * Counts how many neighbour tiles match together
         */
        int count_matching_boundaries(std::vector<Piece> pieces, int dim);

        Board& get_board() {return board;};
};