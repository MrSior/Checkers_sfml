//
// Created by Семён Чубенко on 03.11.2022.
//

#include "BotRand.h"

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> BotRand::Move(Board board) {
    auto moves = board.GetPossibleMoves();
    std::uniform_int_distribution<> dis(0, (int)moves.size() - 1);
    std::mt19937 gen(time(nullptr));
    return moves[dis(gen)];
}

bool BotRand::IsShouldAttack(Board board) {

    return board.GetIsShouldAttack();
}
