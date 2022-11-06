//
// Created by Семён Чубенко on 26.10.2022.
//

#ifndef CHECKERS_BOTMANAGER_H
#define CHECKERS_BOTMANAGER_H

#include "Bot/IBot.h"
#include "Bot/BotRand/BotRand.h"
#include "Bot/BotGrandmaster/BotGrandmaster.h"
#include "../Board/Board.h"
#include "memory"
#include "iostream"

class BotManager {
private:
    IBot* bot_;
public:
    BotManager();

    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> GetBotsMove(Board board);
    bool GetIsShouldAttack(Board board);
};


#endif //CHECKERS_BOTMANAGER_H
