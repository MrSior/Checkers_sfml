//
// Created by Семён Чубенко on 26.10.2022.
//

#ifndef CHECKERS_IBOT_H
#define CHECKERS_IBOT_H

#include "vector"

class IBot {
public:
    virtual void MakeMove(std::vector<std::vector<int>>& board) = 0;
};


#endif //CHECKERS_IBOT_H
