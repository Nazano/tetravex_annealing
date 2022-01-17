#include <math.h>
#include "game.hpp"

void Board::parse(std::string path)
{
    // Open input file
    std::string line;
    std::ifstream file(path);
    int line_index = 0;
    // Read eachline as a piece and add it to the board
    while (std::getline(file, line))
    {
        auto in_good_place = line.find('@', 3);
        auto sl = line.substr(0, 4);
        auto p = Piece(sl, in_good_place==std::string::npos);
        pieces.push_back(p);
        if (in_good_place != -1)
            pieces_in_place.push_back(line_index);
        line_index ++;
        size += 1;
    }
    file.close();

    dimension = int(sqrt(size));
    
    if (sqrt(size) * sqrt(size) != size)
        std::cout << "WARNING: invalid grid size (" << size << " tiles)\n";
}

void Board::solve()
{

}

void Board::save(std::string path)
{
    std::ofstream outfile("path");

    for (auto& piece : pieces)
        outfile << piece;

    outfile.close();
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    std::string one_str_pieces;
    for (auto& piece : board.pieces)
        one_str_pieces.append(piece.get_value());
    
    int w = sqrt(board.size);

    for (int i = 0; i < w; i++)
    {
        // Print top
        for (int j = 0; j < w * 4; j+=4)
            os << "\t " << one_str_pieces[i * w * 4 + j];
        os << '\n';
        
        // Print left and right
        for (int j = 1; j < w * 4; j+=4)
            os << "\t" << one_str_pieces[i * w * 4 + j] << " " << one_str_pieces[i * w * 4 + (j + 1)];
        os << '\n';
        // Print bot
        for (int j = 3; j <  w * 4; j+=4)
            os << "\t " << one_str_pieces[i * w * 4 + j];
        os << '\n';
    }

    return os;
}

Piece::Piece(std::string& line, bool in_place)
{
    this->in_place = in_place;
    this->values = line;
}

std::ostream& operator<<(std::ostream& os, const Piece& peice)
{
    return os << peice.values;
}