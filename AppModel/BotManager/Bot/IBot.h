//
// Created by Семён Чубенко on 26.10.2022.
//

#ifndef CHECKERS_IBOT_H
#define CHECKERS_IBOT_H

#include "vector"
#include "../../Board/Board.h"

class IBot {
public:
    virtual std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Move(Board board) = 0;
    virtual bool IsShouldAttack(Board board) = 0;
};


#endif //CHECKERS_IBOT_H
