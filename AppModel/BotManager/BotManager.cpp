//
// Created by Семён Чубенко on 26.10.2022.
//

#include "BotManager.h"

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> BotManager::GetBotsMove(Board board) {
    board.SwapColor();
    auto move = bot_->Move(board);
    move.first.first = board.GetBoardSize().first - move.first.first - 1;
    move.second.first = board.GetBoardSize().first - move.second.first - 1;
//    std::cout << move.first.first << " " << move.first.second << '\n';
//    std::cout << move.second.first << " " << move.second.second << "\n\n";
    return move;
}

BotManager::BotManager() {
    //bot_ = new BotRand();
    bot_ = new BotGrandmaster();
}

bool BotManager::GetIsShouldAttack(Board board) {
    board.SwapColor();
    return bot_->IsShouldAttack(board);
}

void BotManager::SetBot(int num) {
    if (num == 0){
        bot_ = new BotRand();
    } else if (num == 1) {

    } else if (num == 2) {
        bot_ = new BotGrandmaster();
    }
}

int BotManager::GetBotType() {
    return bot_->GetBotType();
}

