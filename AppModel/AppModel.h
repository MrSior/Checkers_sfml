//
// Created by Семён Чубенко on 20.10.2022.
//

#ifndef CHECKERS_APPMODEL_H
#define CHECKERS_APPMODEL_H

#include "BotManager/BotManager.h"
#include "memory"
#include "vector"
#include "iostream"
#include "functional"

enum Cell{
    WHITE_PIECE,
    BLACK_PIECE,
    WHITE_KING,
    BLACK_KING,
    EMPTY
};

class AppModel {
private:
    std::shared_ptr<BotManager> bot_manager_;

    std::vector<std::vector<Cell>> board_;
    std::pair<size_t, size_t> boardSize_;

    std::pair<size_t, size_t> selectedCell_;
    std::vector<std::pair<size_t, size_t>> selectedCellPossibleMoves_;
    std::vector<std::pair<size_t, size_t>> possibleMoves_;

    bool isCellSelected_;
    bool isShouldAttack_;

    void CountPossibleMoves();
    void CheckIsShouldAttack();
public:
    AppModel();
    void Init();

    void SetSelectedCell(std::pair<size_t, size_t> cell);

    const std::vector<std::vector<Cell>>& GetBoard();
    const std::pair<size_t, size_t>& GetBoardSize();
    const std::pair<size_t, size_t>& GetSelectedCell();
    const std::vector<std::pair<size_t, size_t>>& GetSelectedCellPossibleMoves();
    bool GetIsCellSelected() const;

    std::vector<std::pair<size_t, size_t>> GetPossibleMoves(std::pair<size_t, size_t> cell, bool* isShouldAttack = nullptr);
    bool CheckIsPossibleMove(std::pair<size_t, size_t> cell);
    void Move(std::pair<size_t, size_t> cell);
    bool isPieceWhite(std::pair<size_t, size_t> cell) const;
    bool GetIsShouldAttack();
};


#endif //CHECKERS_APPMODEL_H
