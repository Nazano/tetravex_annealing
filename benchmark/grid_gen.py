from random import randint, sample

class Piece:
    def __init__(self) -> None:
        self.l = randint(0, 9)
        self.r = randint(0, 9)
        self.t = randint(0, 9)
        self.b = randint(0, 9)

    def __repr__(self) -> str:
        return f"{self.t}{self.l}{self.r}{self.b}"

class Board:
    def __init__(self, size) -> None:
        self.size = size
        self.solution = self._gen_board(size)
        self.start = self._shuffle_board()

    def _gen_board(self, size):
        board = []
        for _ in range(size):
            line = []
            for _ in range(size):
                line.append(Piece())
            board.append(line)

        for i in range(size - 1):
            for j in range(size - 1):
                board[i][j].r = board[i][j + 1].l
                board[i][j].b = board[i + 1][j].t
        
        for j in range(size - 1):
            board[size - 1][j].t = board[size - 2][j].b
            board[size - 1][j].r = board[size - 1][j + 1].l

        for i in range(size - 1):
            board[i][size - 1].b = board[i + 1][size - 1].t

        return board

    def _shuffle_board(self):
        start = sample(self.solution, k=len(self.solution))
        for l in start:
            l = sample(l, k=len(l))
        return start
        

    def export(self):
        with open(f"{self.size}.txt", "w") as shuf:
            for l in self.start:
                for p in l:
                    shuf.write(str(p) + "\n")

        with open(f"{self.size}-ref.txt", "w") as ref:
            for l in self.solution:
                for p in l:
                    ref.write(str(p) + "\n")

import sys
if __name__ == "__main__":
    if len(sys.argv) == 2:
        Board(int(sys.argv[1])).export()
    else:
        print("Usage: grid_gen.py [board_size]")