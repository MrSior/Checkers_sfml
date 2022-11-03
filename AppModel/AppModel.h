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
#include "Board/Board.h"

class AppModel {
private:
    std::shared_ptr<BotManager> bot_manager_;
    Board board_;

    std::pair<size_t, size_t> selectedCell_;
    std::vector<std::pair<size_t, size_t>> selectedCellPossibleMoves_;

    bool isCellSelected_;
    bool isPLayerTurn;
public:
    AppModel();
    void Init();

    void SetSelectedCell(std::pair<size_t, size_t> cell);

    const std::vector<std::vector<Cell>>& GetBoard();
    const std::pair<size_t, size_t>& GetBoardSize();
    const std::pair<size_t, size_t>& GetSelectedCell();
    const auto& GetSelectedCellPossibleMoves() {return selectedCellPossibleMoves_;};
    bool GetIsCellSelected() const;
    bool GetIsPlayerTurn() const {return isPLayerTurn;};

    bool CheckIsPossibleMove(std::pair<size_t, size_t> cell);
    void Move(std::pair<size_t, size_t> cell);
    bool isPieceWhite(std::pair<size_t, size_t> cell) const;

};


#endif //CHECKERS_APPMODEL_H
