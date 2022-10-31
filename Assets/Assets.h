//
// Created by Семён Чубенко on 26.10.2022.
//

#ifndef CHECKERS_ASSETS_H
#define CHECKERS_ASSETS_H

#include "SFML/Graphics.hpp"

class Assets {
public:
    sf::Texture blackPieceT;
    sf::Texture whitePieceT;

    static Assets& Instance()
    {
        static Assets s;
        return s;
    }
    void Load();
};


#endif //CHECKERS_ASSETS_H
