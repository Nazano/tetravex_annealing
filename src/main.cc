#include <iostream>

#include "game.hpp"

int main(int argc, char const *argv[])
{
    auto board = Board();
    board.parse("../in.txt");
    std::cout << board;
    return 0;
}
