//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppModel.h"

AppModel::AppModel() {
    bot_manager_ = std::make_shared<BotManager>();
    Init();
}

void AppModel::Init() {
    boardSize_ = {8, 8};
    board_.assign(boardSize_.first, std::vector<Cell>(boardSize_.second, EMPTY));

    board_[7][2] = WHITE_PIECE;
    board_[6][1] = BLACK_PIECE;
    board_[6][3] = BLACK_PIECE;
    board_[4][1] = BLACK_PIECE;
    board_[4][3] = BLACK_PIECE;

//    for (size_t line = 0; line < boardSize_.first; ++line) {
//        if (line >= 3 && line < boardSize_.first - 3) continue;
//        size_t start_ind = (line + 1) % 2;
//        for (size_t column = start_ind; column < boardSize_.second; column += 2) {
//            if (line < 3) {
//                board_[line][column] = BLACK_PIECE;
//            } else {
//                board_[line][column] = WHITE_PIECE;
//            }
////            board_[line][column] = 1 * ((line < 3) ? -1: 1);
//        }
//    }
}

const std::vector<std::vector<Cell>> &AppModel::GetBoard() {
    return board_;
}

const std::pair<size_t, size_t> &AppModel::GetBoardSize() {
    return boardSize_;
}

std::vector<std::pair<size_t, size_t>> AppModel::GetPossibleMoves(int line, int column) {
    auto isEmpty{
            [&](int i, int j) {
                if (i < 0 || i >= boardSize_.first) {
                    return false;
                }
                if (j < 0 || j >= boardSize_.second) {
                    return false;
                }
                return board_[i][j] == EMPTY;
            }
    };

    auto isEnemy{
            [&](int i, int j) {
                if (i < 0 || i >= boardSize_.first) {
                    return false;
                }
                if (j < 0 || j >= boardSize_.second) {
                    return false;
                }
                return board_[i][j] != EMPTY && board_[i][j] != WHITE_PIECE && board_[i][j] != WHITE_KING;
            }
    };

    std::function<std::vector<std::pair<size_t, size_t>>(int, int)> GetAttackingLine =
            [&](int i, int j) -> std::vector<std::pair<size_t, size_t>> {
                if (i < 0 || i >= boardSize_.first) {
                    return {};
                }
                if (j < 0 || j >= boardSize_.second) {
                    return {};
                }
                std::vector<std::pair<size_t, size_t>> res;
                if (isEnemy(i - 1, j - 1)) {
                    auto pieceType = board_[i - 1][j - 1];
                    board_[i - 1][j - 1] = EMPTY;
                    res = GetAttackingLine(i - 2, j - 2);
                    board_[i - 1][j - 1] = pieceType;
                }
                if (isEnemy(i - 1, j + 1)){
                    auto pieceType = board_[i - 1][j + 1];
                    board_[i - 1][j + 1] = EMPTY;
                    auto tmp = GetAttackingLine(i - 2, j + 2);
                    for (auto elem : tmp) {
                        res.emplace_back(elem);
                    }
                    board_[i - 1][j + 1] = pieceType;
                }
                if (isEnemy(i + 1, j - 1)){
                    auto pieceType = board_[i + 1][j - 1];
                    board_[i + 1][j - 1] = EMPTY;
                    auto tmp = GetAttackingLine(i + 2, j - 2);
                    for (auto elem : tmp) {
                        res.emplace_back(elem);
                    }
                    board_[i + 1][j - 1] = pieceType;
                }
                if (isEnemy(i + 1, j + 1)){
                    auto pieceType = board_[i + 1][j + 1];
                    board_[i + 1][j + 1] = EMPTY;
                    auto tmp = GetAttackingLine(i + 2, j + 2);
                    for (auto elem : tmp) {
                        res.emplace_back(elem);
                    }
                    board_[i + 1][j + 1] = pieceType;
                }
                res.emplace_back(i, j);
                return res;
    };


    if (column < 0 || column >= boardSize_.second) return {};
    if (line < 0 || line >= boardSize_.first) return {};
    if (board_[line][column] == BLACK_PIECE || board_[line][column] == BLACK_KING) return {};

    auto res = GetAttackingLine(line, column);
    if (res.size() > 1) {
        res.pop_back();
        return res;
    }
    res.pop_back();
    if (isEmpty(line - 1, column - 1)) {
        res.emplace_back(line - 1, column - 1);
    }
    if (isEmpty(line - 1, column + 1)) {
        res.emplace_back(line - 1, column + 1);
    }
    return res;
}
