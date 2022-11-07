//
// Created by Семён Чубенко on 04.11.2022.
//

#ifndef CHECKERS_BOTGRANDMASTER_H
#define CHECKERS_BOTGRANDMASTER_H

#include "../IBot.h"
#include "vector"

class Node{
public:
    Board board;
    int value;
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> move;
    Node* parent;
    std::vector<Node*> children;
    bool isWhiteMove;

    Node(){
        value = 0;
        isWhiteMove = true;
        parent = nullptr;
    }

    Node(Board board, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> move, Node* parent){
        this->board = board;
        this->move = move;
        this->parent = parent;
        this->isWhiteMove;
        value = 0;
    }
};

class BotGrandmaster : public IBot {

    void BuildTree(Node* node, int depth = 0);
    int EvaluatePosition(const Board& board);
    void dfs(Node* node, bool isMin);
public:
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Move(Board board) override;
    bool IsShouldAttack(Board board) override;
    int GetBotType() override;
};


#endif //CHECKERS_BOTGRANDMASTER_H
