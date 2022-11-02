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
    isShouldAttack_ = false;


//    board_[7][2] = WHITE_KING;
//    board_[1][2] = WHITE_PIECE;
//    board_[6][1] = BLACK_PIECE;
//    board_[6][3] = BLACK_PIECE;
//    board_[4][1] = BLACK_PIECE;
//    board_[4][3] = BLACK_PIECE;

    for (size_t line = 0; line < boardSize_.first; ++line) {
        if (line >= 3 && line < boardSize_.first - 3) continue;
        size_t start_ind = (line + 1) % 2;
        for (size_t column = start_ind; column < boardSize_.second; column += 2) {
            if (line < 3) {
                board_[line][column] = BLACK_PIECE;
            } else {
                board_[line][column] = WHITE_PIECE;
            }
        }
    }

    CountPossibleMoves();
}

const std::vector<std::vector<Cell>> &AppModel::GetBoard() {
    return board_;
}

const std::pair<size_t, size_t> &AppModel::GetBoardSize() {
    return boardSize_;
}

std::vector<std::pair<size_t, size_t>> AppModel::GetPossibleMoves(std::pair<size_t, size_t> cell, bool* isShouldAttack) {
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
                if (board_[i][j] == WHITE_PIECE) {
                    if (isEnemy(i - 1, j - 1) && isEmpty(i - 2, j - 2)) {
                        res.emplace_back(i - 2, j - 2);
                    }
                    if (isEnemy(i - 1, j + 1) && isEmpty(i - 2, j + 2)) {
                        res.emplace_back(i - 2, j + 2);
                    }
//                    if (isEnemy(i + 1, j - 1) && isEmpty(i + 2, j - 2)) {
//                        res.emplace_back(i + 2, j - 2);
//                    }
//                    if (isEnemy(i + 1, j + 1) && isEmpty(i + 2, j + 2)) {
//                        res.emplace_back(i + 2, j + 2);
//                    }
                    return res;
                }
                auto CheckDiagonal =
                        [&](std::pair<int, int> cell, std::pair<int, int> direction) {
                            while (cell.first >= 0 && cell.first < boardSize_.first
                                   && cell.second >= 0 && cell.second < boardSize_.second) {
                                if (isEnemy(cell.first, cell.second)
                                    && isEmpty(cell.first + direction.first,
                                               cell.second + direction.second)) {
                                    res.emplace_back(cell.first + direction.first,
                                                     cell.second + direction.second);
                                    break;
                                }
                                cell.first += direction.first;
                                cell.second += direction.second;
                            }
                        };
                CheckDiagonal({i, j}, {1, 1});
                CheckDiagonal({i, j}, {1, -1});
                CheckDiagonal({i, j}, {-1, 1});
                CheckDiagonal({i, j}, {-1, -1});
                return res;
            };


    if (cell.first >= boardSize_.second) return {};
    if (cell.second >= boardSize_.first) return {};
    if (board_[cell.first][cell.second] == BLACK_PIECE || board_[cell.first][cell.second] == BLACK_KING) return {};

    auto res = GetAttackingLine((int) cell.first, (int) cell.second);
    if (!res.empty()) {
        if(isShouldAttack) *isShouldAttack = true;
        return res;
    }
    if (isShouldAttack_) return res;
    if (board_[cell.first][cell.second] == WHITE_PIECE) {
        if (isEmpty((int) cell.first - 1, (int) cell.second - 1)) {
            res.emplace_back(cell.first - 1, cell.second - 1);
        }
        if (isEmpty((int) cell.first - 1, (int) cell.second + 1)) {
            res.emplace_back(cell.first - 1, cell.second + 1);
        }
    } else {
        auto CheckDiagonal =
                [&](std::pair<int, int> cell, std::pair<int, int> direction) {
                    cell.first += direction.first;
                    cell.second += direction.second;
                    while (isEmpty(cell.first, cell.second)) {
                        res.emplace_back(cell.first, cell.second);
                        cell.first += direction.first;
                        cell.second += direction.second;
                    }
                };
        CheckDiagonal({cell.first, cell.second}, {1, 1});
        CheckDiagonal({cell.first, cell.second}, {1, -1});
        CheckDiagonal({cell.first, cell.second}, {-1, 1});
        CheckDiagonal({cell.first, cell.second}, {-1, -1});
    }
    return res;
}

void AppModel::SetSelectedCell(std::pair<size_t, size_t> cell) {
    if (board_[cell.first][cell.second] != WHITE_PIECE && board_[cell.first][cell.second] != WHITE_KING) return;
    selectedCell_ = cell;
    selectedCellPossibleMoves_ = GetPossibleMoves(selectedCell_);
    isCellSelected_ = true;
}

const std::pair<size_t, size_t> &AppModel::GetSelectedCell() {
    return selectedCell_;
}

const std::vector<std::pair<size_t, size_t>> &AppModel::GetSelectedCellPossibleMoves() {
    return selectedCellPossibleMoves_;
}

bool AppModel::GetIsCellSelected() const {
    return isCellSelected_;
}

bool AppModel::CheckIsPossibleMove(std::pair<size_t, size_t> cell) {
    return std::find(possibleMoves_.begin(),
                     possibleMoves_.end(),
                     cell) != possibleMoves_.end();
}

void AppModel::Move(std::pair<size_t, size_t> cell) {
    if (cell == selectedCell_) return;
    std::swap(board_[selectedCell_.first][selectedCell_.second],
              board_[cell.first][cell.second]);


    std::pair<int, int> direction;
    direction.first = (int) cell.first - (int) selectedCell_.first > 0 ? 1 : -1;
    direction.second = (int) cell.second - (int) selectedCell_.second > 0 ? 1 : -1;
    for (std::pair<size_t, size_t> _cell = selectedCell_; _cell != cell;
         _cell.first += direction.first, _cell.second += direction.second) {
        board_[_cell.first][_cell.second] = EMPTY;
    }

    isCellSelected_ = false;
    selectedCellPossibleMoves_.clear();
    CountPossibleMoves();
}

bool AppModel::isPieceWhite(std::pair<size_t, size_t> cell) const {
    return board_[cell.first][cell.second] == WHITE_PIECE
           || board_[cell.first][cell.second] == WHITE_KING;
}

void AppModel::CountPossibleMoves() {
    possibleMoves_.clear();
    CheckIsShouldAttack();
    for (int line = 0; line < boardSize_.first; ++line) {
        for (int column = 0; column < boardSize_.second; ++column) {
            if (isPieceWhite({line, column})){
                bool isShouldAttack = false;
                auto res = GetPossibleMoves({line, column}, &isShouldAttack);
                if (!isShouldAttack_ && isShouldAttack) {
                    possibleMoves_.clear();
                    isShouldAttack_ = true;
                }
                if (isShouldAttack == isShouldAttack_) {
                    for (auto elem: res) {
                        possibleMoves_.emplace_back(elem);
                    }
                }
            }
        }
    }
}

void AppModel::CheckIsShouldAttack() {
    for (int line = 0; line < boardSize_.first; ++line) {
        for (int column = 0; column < boardSize_.second; ++column) {
            if (isPieceWhite({line, column})){
                bool isShouldAttack = false;
                auto res = GetPossibleMoves({line, column}, &isShouldAttack);
                if (isShouldAttack) {
                    isShouldAttack_ = true;
                    return;
                }
            }
        }
    }
    isShouldAttack_ = false;
}
