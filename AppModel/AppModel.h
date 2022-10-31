//
// Created by Семён Чубенко on 20.10.2022.
//

#ifndef CHECKERS_APPMODEL_H
#define CHECKERS_APPMODEL_H

#include "BotManager/BotManager.h"
#include "memory"
#include "vector"
#include "iostream"

enum Cell{
    WHITE_PIECE,
    BLACK_PIECE,
    WHITE_KING,
    BLACK_KING,
    NONE
};

class AppModel {
private:
    std::shared_ptr<BotManager> bot_manager_;

    std::vector<std::vector<Cell>> board_;
    std::pair<size_t, size_t> boardSize_;
public:
    AppModel();
    void Init();

    const std::vector<std::vector<Cell>>& GetBoard();
    const std::pair<size_t, size_t>& GetBoardSize();
};


#endif //CHECKERS_APPMODEL_H
