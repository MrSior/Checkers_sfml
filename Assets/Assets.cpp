//
// Created by Семён Чубенко on 26.10.2022.
//

#include "Assets.h"

void Assets::Load() {
    blackPieceRandT.loadFromFile("../Assets/Sprites/EnemyMenRand.png");
    blackPieceBeginnerT.loadFromFile("../Assets/Sprites/EnemyMenNewer.png");
    blackPieceGrandmasterT.loadFromFile("../Assets/Sprites/EnemyMenPro.png");
    whitePieceT.loadFromFile("../Assets/Sprites/PlayerMen.png");
    whiteKingT.loadFromFile("../Assets/Sprites/quineWhite.png");
    blackKingRandT.loadFromFile("../Assets/Sprites/quine(2).png");
    blackKingBeginnerT.loadFromFile("../Assets/Sprites/quine(1).png");
    blackKingGrandmasterT.loadFromFile("../Assets/Sprites/quine.png");
}
