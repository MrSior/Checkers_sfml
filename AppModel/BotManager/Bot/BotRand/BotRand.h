//
// Created by Семён Чубенко on 03.11.2022.
//

#ifndef CHECKERS_BOTRAND_H
#define CHECKERS_BOTRAND_H

#include "vector"
#include "../IBot.h"
#include "random"

class BotRand : public IBot{

public:
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Move(Board board) override;
    bool IsShouldAttack(Board board) override;
    int GetBotType() override { return 0; };
};


#endif //CHECKERS_BOTRAND_H
