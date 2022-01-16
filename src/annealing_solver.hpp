#include "game.hpp"

class Solver
{
    private:
        float T;
        Board board;
    public:
        Solver(Board&);

        // returns 0 if the board could be solved, -1 otherwise.
        int solve();

        /**
         * Checks if two neighbour tiles match together.
         * 
         * 'a' and 'b' should be the indexes of two neighbour tiles.
         * If they are not neighbours, this function returns false.
         */
        bool check_matching_boundaries(int a, int b);
        /**
         * Counts how many neighbour tiles match together
         */
        int count_matching_boundaries();
};