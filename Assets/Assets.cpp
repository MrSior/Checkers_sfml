//
// Created by Семён Чубенко on 26.10.2022.
//

#include "Assets.h"

void Assets::Load() {
    blackPieceT.loadFromFile("../Assets/Sprites/EnemyMenRand.png");
    whitePieceT.loadFromFile("../Assets/Sprites/PlayerMen.png");
    whiteKingT.loadFromFile("../Assets/Sprites/quineWhite.png");
    blackKingT.loadFromFile("../Assets/Sprites/quine(2).png");
}
