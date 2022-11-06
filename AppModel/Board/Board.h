//
// Created by Семён Чубенко on 03.11.2022.
//

#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H
#include "vector"
#include "iostream"

enum Cell{
    WHITE_PIECE,
    BLACK_PIECE,
    WHITE_KING,
    BLACK_KING,
    EMPTY
};

class Board {
private:
    std::vector<std::vector<Cell>> board_;
    std::pair<size_t, size_t> boardSize_;
    std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> possibleMoves_;
    bool isShouldAttack_;

    void CountPossibleMoves();
    void CheckIsShouldAttack();
    void CheckNewKing();
public:
    Board();
    Board(Board& board);
    Board(const Board& board);

    bool isPieceWhite(std::pair<size_t, size_t> cell) const;
    void Move(std::pair<size_t, size_t> cell, std::pair<size_t, size_t> new_position);
    void SwapColor();

    std::vector<std::pair<size_t, size_t>> GetCellPossibleMoves(std::pair<size_t, size_t> cell, bool* isShouldAttack = nullptr);
    const auto& GetBoard() const { return board_;};
    const auto& GetBoardSize() const {return boardSize_;};
    const auto& GetPossibleMoves() const {return possibleMoves_;};
    bool GetIsShouldAttack() const {return isShouldAttack_;};
    Cell GetElem(size_t line, size_t column) const {return board_[line][column];};
    bool isWhiteWon();

    int GetNumberPieces(Cell type) const;

    void Print() const{
        for (const auto& line : board_) {
            for (auto elem : line) {
                if (elem == WHITE_PIECE || elem == WHITE_KING) {
                    std::cout << 1 << " ";
                } else if (elem == EMPTY) {
                    std::cout << 0 << " ";
                } else {
                    std::cout << 2 << " ";
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

//    int GetNumberPiecesInLine(int line, Cell type);
//    int GetNumberPiecesInColumn(int column, Cell type);
};


#endif //CHECKERS_BOARD_H
