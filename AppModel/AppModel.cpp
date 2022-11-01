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
    selectedCell_ = {-1, -1};
    isCellSelected_ = false;


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

    auto GetAttackingLine =
            [&](int i, int j) -> std::vector<std::pair<size_t, size_t>> {
                if (i < 0 || i >= boardSize_.first) {
                    return {};
                }
                if (j < 0 || j >= boardSize_.second) {
                    return {};
                }
                std::vector<std::pair<size_t, size_t>> res;
                if (isEnemy(i - 1, j - 1)) {
                    res.emplace_back(i - 2, j - 2);
                }
                if (isEnemy(i - 1, j + 1)){
                    res.emplace_back(i - 2, j + 2);
                }
                if (isEnemy(i + 1, j - 1)){
                    res.emplace_back(i + 2, j - 2);
                }
                if (isEnemy(i + 1, j + 1)){
                    res.emplace_back(i + 2, j + 2);
                }
                return res;
    };


    if (column < 0 || column >= boardSize_.second) return {};
    if (line < 0 || line >= boardSize_.first) return {};
    if (board_[line][column] == BLACK_PIECE || board_[line][column] == BLACK_KING) return {};

    auto res = GetAttackingLine(line, column);
    if (!res.empty()) {
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

void AppModel::SetSelectedCell(std::pair<size_t, size_t> cell) {
    if (board_[cell.first][cell.second] != WHITE_PIECE) return;
    selectedCell_ = cell;
    selectedCellPossibleMoves_ = GetPossibleMoves(selectedCell_.first, selectedCell_.second);
    isCellSelected_ = true;
}

const std::pair<int, int> &AppModel::GetSelectedCell() {
    return selectedCell_;
}

const std::vector<std::pair<size_t, size_t>> &AppModel::GetSelectedCellPossibleMoves() {
    return selectedCellPossibleMoves_;
}

bool AppModel::GetIsCellSelected() const {
    return isCellSelected_;
}

bool AppModel::CheckIsPossibleMove(std::pair<size_t, size_t> cell) {
    return std::find(selectedCellPossibleMoves_.begin(),
                     selectedCellPossibleMoves_.end(),
                     cell) != selectedCellPossibleMoves_.end();
}

void AppModel::Move(std::pair<size_t, size_t> cell) {
    std::swap(board_[selectedCell_.first][selectedCell_.second],
              board_[cell.first][cell.second]);

    if (abs((int)cell.first - (int)selectedCell_.first) > 1) {
        std::pair<size_t, size_t> betweenCell(selectedCell_.first + ((int)cell.first - (int)selectedCell_.first) / 2,
                                              selectedCell_.second + ((int)cell.second - (int)selectedCell_.second) / 2);
        board_[betweenCell.first][betweenCell.second] = EMPTY;
    }
    isCellSelected_ = false;
    selectedCellPossibleMoves_.clear();
}
