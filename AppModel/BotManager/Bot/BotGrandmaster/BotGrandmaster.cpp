//
// Created by Семён Чубенко on 04.11.2022.
//

#include "BotGrandmaster.h"

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> BotGrandmaster::Move(Board board) {
    //int val = EvaluatePosition(board);
    Node *node = new Node;
    node->board = board;
    BuildTree(node);
    dfs(node, true);
    int min = INT_MAX;
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> move;
    for (auto &child: node->children) {
        if (min > child->value) {
            min = child->value;
            move = child->move;
        }
    }

    return move;
}

bool BotGrandmaster::IsShouldAttack(Board board) {
    return board.GetIsShouldAttack();;
}

int BotGrandmaster::EvaluatePosition(const Board &board) {
    int pawnPiecesNum = board.GetNumberPieces(WHITE_PIECE);
    int kingPiecesNum = board.GetNumberPieces(WHITE_KING);

    int piecesBackLine = 0;
    for (int ind = 0; ind < board.GetBoardSize().second; ++ind) {
        auto elem = board.GetElem(board.GetBoardSize().first - 1, ind);
        piecesBackLine += elem == WHITE_PIECE || elem == WHITE_KING;
    }


    int piecesIn2MidLines4MidColumns = 0;
    int piecesIn2MidLinesNotIn4MidColumns = 0;
    for (int line = 0; line < board.GetBoardSize().first; ++line) {
        for (int column = 0; column < board.GetBoardSize().second; ++column) {
            if (board.GetBoardSize().first - 1 - line - line + 1 <= 2) {
                auto elem = board.GetElem(line, column);
                if (board.GetBoardSize().second - 1 - column - column + 1 <= 4) {
                    piecesIn2MidLines4MidColumns += elem == WHITE_KING || elem == WHITE_PIECE;
                } else {
                    piecesIn2MidLinesNotIn4MidColumns += elem == WHITE_KING || elem == WHITE_PIECE;
                }
            }
        }
    }

    auto CountPiecesOpponentCanTake{
            [](Board board) {
                int res = 0;
                while (board.GetIsShouldAttack()) {
                    auto &moves = board.GetPossibleMoves();
                    board.Move(moves.front().first, moves.front().second);
                    res++;
                }
                return res;
            }
    };
    int piecesOpponentCanTake = CountPiecesOpponentCanTake(board);

    int protectedPieces = 0;
//    board.Print();
    for (int line = 0; line < board.GetBoardSize().first; ++line) {
        for (int column = 0; column < board.GetBoardSize().second; ++column) {
            if (board.isPieceWhite({line, column})) {
                if (line == board.GetBoardSize().first - 1) {
                    protectedPieces++;
                } else {
                    if (column == 0) {
                        protectedPieces += board.isPieceWhite({line + 1, column + 1});
                    } else if (column == board.GetBoardSize().second - 1) {
                        protectedPieces += board.isPieceWhite({line + 1, column - 1});
                    } else {
                        protectedPieces += board.isPieceWhite({line + 1, column - 1})
                                           && board.isPieceWhite({line + 1, column + 1});
                    }
                }
            }
        }
    }

    int piecesAtBoarders = 0;
    for (int line = 0; line < board.GetBoardSize().first; ++line) {
        piecesAtBoarders += board.isPieceWhite({line, 0});
        piecesAtBoarders += board.isPieceWhite({line, board.GetBoardSize().second - 1});
    }

    return pawnPiecesNum * 8 + kingPiecesNum * 16 + piecesIn2MidLinesNotIn4MidColumns * 3
           + piecesIn2MidLines4MidColumns * 4 + piecesBackLine * 2 - piecesOpponentCanTake * 6
           + protectedPieces * 6 + piecesAtBoarders * 2;
}

void BotGrandmaster::BuildTree(Node *node, int depth) {
    if (depth > 3) return;
    for (auto move: node->board.GetPossibleMoves()) {
        auto tmpBoard = node->board;
        tmpBoard.Move(move.first, move.second);
        Node *child = new Node(tmpBoard, move, node);
        while (tmpBoard.GetIsShouldAttack()) {
            tmpBoard.Move(tmpBoard.GetPossibleMoves().front().first, tmpBoard.GetPossibleMoves().front().second);
            child->board = tmpBoard;
        }
        child->board.SwapColor();
        BuildTree(child, depth + 1);
        node->children.push_back(child);
    }
}

void BotGrandmaster::dfs(Node *node, bool isMin) {
    if (node == nullptr) return;
    if (node->children.empty()) {
        node->value = EvaluatePosition(node->board);
        return;
    }
    if (isMin) {
        int min = INT_MAX;
        for (auto &ind: node->children) {
            dfs(ind, false);
            min = std::min(min, ind->value);
        }
        node->value = min;
        return;
    }
    int max = INT_MIN;
    for (auto &ind: node->children) {
        dfs(ind, true);
        max = std::max(max, ind->value);
    }
    node->value = max;
}
