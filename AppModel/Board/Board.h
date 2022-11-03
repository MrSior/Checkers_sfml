//
// Created by Семён Чубенко on 03.11.2022.
//

#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H
#include "vector"

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
    std::vector<std::pair<size_t, size_t>> possibleMoves_;
    bool isShouldAttack_;

    void CountPossibleMoves();
    void CheckIsShouldAttack();
public:
    Board();

    bool isPieceWhite(std::pair<size_t, size_t> cell) const;
    void Move(std::pair<size_t, size_t> cell, std::pair<size_t, size_t> new_position);
    std::vector<std::pair<size_t, size_t>> GetCellPossibleMoves(std::pair<size_t, size_t> cell, bool* isShouldAttack = nullptr);
    const auto& GetBoard() { return board_;};
    const auto& GetBoardSize() {return boardSize_;};
    const auto& GetPossibleMoves() {return possibleMoves_;};
    bool GetIsShouldAttack() const {return isShouldAttack_;};
};


#endif //CHECKERS_BOARD_H
