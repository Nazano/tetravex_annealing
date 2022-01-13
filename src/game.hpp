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
        char B()    {return values[2];};
        char R()    {return values[3];};
    
    friend std::ostream& operator<<(std::ostream&, const Piece&);
};

class Board 
{
    private:
        int size = 0;
        std::vector<Piece> pieces;

    public:
        Board(){};
        /**
         * Parse input file and save the content into the vector pieces 
         */
        void parse(std::string);

        /**
         * Solve the Board inplace
         */
        void solve();

        /**
         * Save the board content to a file
         */
        void save(std::string path = "out.txt");

        int get_board_size()    {return size;};
    
    friend std::ostream& operator<<(std::ostream&, const Board&);
};
