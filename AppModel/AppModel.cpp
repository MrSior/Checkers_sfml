//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppModel.h"

AppModel::AppModel() {
    bot_manager_ = std::make_shared<BotManager>();
    Init();
}

void AppModel::Init() {
    boardSize_ = {8, 8};
    board_.assign(boardSize_.first, std::vector<Cell>(boardSize_.second, NONE));

    for (size_t line = 0; line < boardSize_.first; ++line) {
        if (line >= 3 && line < boardSize_.first - 3) continue;
        size_t start_ind = (line + 1) % 2;
        for (size_t column = start_ind; column < boardSize_.second; column += 2) {
            if (line < 3) {
                board_[line][column] = BLACK_PIECE;
            } else {
                board_[line][column] = WHITE_PIECE;
            }
//            board_[line][column] = 1 * ((line < 3) ? -1: 1);
        }
    }
}

const std::vector<std::vector<Cell>>& AppModel::GetBoard() {
    return board_;
}

const std::pair<size_t, size_t> &AppModel::GetBoardSize() {
    return boardSize_;
}
