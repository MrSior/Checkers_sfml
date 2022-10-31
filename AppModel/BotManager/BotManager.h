//
// Created by Семён Чубенко on 26.10.2022.
//

#ifndef CHECKERS_BOTMANAGER_H
#define CHECKERS_BOTMANAGER_H

#include "Bot/IBot.h"
#include "memory"

class BotManager {
private:
    std::shared_ptr<IBot> bot_;
public:

    void Make_bots_move(std::vector<std::vector<int>>& board);
};


#endif //CHECKERS_BOTMANAGER_H
