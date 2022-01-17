#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class Piece
{
    private:
        //   T
        // R   L
        //   B
        std::string values; 
        bool in_place;

    public:
        Piece(std::string&, bool);

        std::string get_value() const {return values;};

        char T()    {return values[0];};
        char L()    {return values[1];};
        char R()    {return values[2];};
        char B()    {return values[3];};
    
    friend std::ostream& operator<<(std::ostream&, const Piece&);
};

class Board 
{
    private:
        int size = 0;           // How many tiles we have. Should be a square number
        int dimension = 0;      // The dimension of the grid. dimension = int(sqrt(size))
        std::vector<Piece> pieces;
        std::vector<int> pieces_in_place;
    public:
        Board(){};
        Board(std::vector<Piece> pieces, int size, int dimension)
            : size(size)
            , dimension(dimension)
            , pieces(pieces)
        {};

        /**
         * Parse input file and save the content into the vector pieces 
         */
        void parse(std::string);


        /**
         * Save the board content to a file
         */
        void save(std::string path = "out.txt");

        int get_board_size()    {return size;};
        int get_board_dimension() {return dimension;};

        void set_pieces(std::vector<Piece> p) {pieces = p;};

        std::vector<Piece>& get_pieces() {return pieces;};
        std::vector<int>& get_pieces_in_place() {return pieces_in_place;};

        int get_count_boundaries();
    
    friend std::ostream& operator<<(std::ostream&, const Board&);
};
