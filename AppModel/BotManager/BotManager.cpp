//
// Created by Семён Чубенко on 26.10.2022.
//

#include "BotManager.h"

void BotManager::Make_bots_move(std::vector<std::vector<int>> &board) {
    bot_->MakeMove(board);
}

