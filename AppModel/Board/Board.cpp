//
// Created by Семён Чубенко on 03.11.2022.
//

#include "Board.h"

Board::Board() {
    boardSize_ = {8, 8};
    board_.assign(boardSize_.first, std::vector<Cell>(boardSize_.second, EMPTY));
    isShouldAttack_ = false;

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

//    board_[2][1] = EMPTY;
//    board_[2][3] = EMPTY;
//    board_[3][2] = BLACK_PIECE;
//    board_[4][1] = EMPTY;
//    board_[5][2] = WHITE_PIECE;
//    board_[4][5] = WHITE_PIECE;
////    board_[5][2] = EMPTY;
//    board_[5][4] = EMPTY;
//    board_[6][3] = EMPTY;

//    board_[7][2] = WHITE_KING;
//    board_[1][2] = WHITE_PIECE;
//    board_[6][1] = BLACK_PIECE;
//    board_[6][3] = BLACK_PIECE;
//    board_[4][1] = BLACK_PIECE;
//    board_[4][3] = BLACK_PIECE;

//    board_[6][1] = WHITE_PIECE;
//    board_[5][0] = BLACK_PIECE;
//    board_[7][4] = WHITE_PIECE;

//    board_[1][2] = BLACK_PIECE;
//    board_[3][2] = WHITE_PIECE;
//    board_[4][5] = WHITE_PIECE;

    CountPossibleMoves();
}

void Board::CountPossibleMoves() {
    possibleMoves_.clear();
    CheckIsShouldAttack();
    for (int line = 0; line < boardSize_.first; ++line) {
        for (int column = 0; column < boardSize_.second; ++column) {
            if (isPieceWhite({line, column})) {
                bool isShouldAttack = false;
                auto res = GetCellPossibleMoves({line, column}, &isShouldAttack);
                if (!isShouldAttack_ && isShouldAttack) {
                    possibleMoves_.clear();
                    isShouldAttack_ = true;
                }
                if (isShouldAttack == isShouldAttack_) {
                    for (auto elem: res) {
                        possibleMoves_.push_back({{line, column}, elem});
                    }
                }
            }
        }
    }
}

void Board::CheckIsShouldAttack() {
    for (int line = 0; line < boardSize_.first; ++line) {
        for (int column = 0; column < boardSize_.second; ++column) {
            if (isPieceWhite({line, column})) {
                bool isShouldAttack = false;
                auto res = GetCellPossibleMoves({line, column}, &isShouldAttack);
                if (isShouldAttack) {
                    isShouldAttack_ = true;
                    return;
                }
            }
        }
    }
    isShouldAttack_ = false;
}

std::vector<std::pair<size_t, size_t>>
Board::GetCellPossibleMoves(std::pair<size_t, size_t> cell, bool *isShouldAttack) {
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
                    if (isEnemy(i + 1, j - 1) && isEmpty(i + 2, j - 2)) {
                        res.emplace_back(i + 2, j - 2);
                    }
                    if (isEnemy(i + 1, j + 1) && isEmpty(i + 2, j + 2)) {
                        res.emplace_back(i + 2, j + 2);
                    }
                    return res;
                }
                auto CheckDiagonal =
                        [&](std::pair<int, int> cell, std::pair<int, int> direction) {
                            while (cell.first >= 0 && cell.first < boardSize_.first
                                   && cell.second >= 0 && cell.second < boardSize_.second) {
                                if (isEnemy(cell.first, cell.second)
                                    && isEmpty(cell.first + direction.first,
                                               cell.second + direction.second)) {
//                                    cell.first += direction.first;
//                                    cell.second += direction.second;
//                                    while (isEmpty(cell.first, cell.second)) {
//                                        res.emplace_back(cell.first, cell.second);
//                                        cell.first += direction.first;
//                                        cell.second += direction.second;
//                                    }
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
        if (isShouldAttack) *isShouldAttack = true;
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

bool Board::isPieceWhite(std::pair<size_t, size_t> cell) const {
    return board_[cell.first][cell.second] == WHITE_PIECE
           || board_[cell.first][cell.second] == WHITE_KING;
}

void Board::Move(std::pair<size_t, size_t> cell, std::pair<size_t, size_t> new_position) {
    std::swap(board_[new_position.first][new_position.second],
              board_[cell.first][cell.second]);
    std::pair<int, int> direction;
    direction.first = (int) new_position.first - (int) cell.first > 0 ? 1 : -1;
    direction.second = (int) new_position.second - (int) cell.second > 0 ? 1 : -1;
    for (std::pair<size_t, size_t> _cell = cell; _cell != new_position;
         _cell.first += direction.first, _cell.second += direction.second) {
        board_[_cell.first][_cell.second] = EMPTY;
    }
    CheckNewKing();
    CountPossibleMoves();
}

Board::Board(Board &board) {
    boardSize_ = board.boardSize_;
    possibleMoves_ = board.possibleMoves_;
    board_ = board.board_;
    isShouldAttack_ = board.isShouldAttack_;
}

void Board::SwapColor() {
    for (auto &line: board_) {
        for (auto &elem: line) {
            if (elem == WHITE_PIECE) {
                elem = BLACK_PIECE;
            } else if (elem == BLACK_PIECE) {
                elem = WHITE_PIECE;
            } else if (elem == WHITE_KING) {
                elem = BLACK_KING;
            } else if (elem == BLACK_KING) {
                elem = WHITE_KING;
            }
        }
    }
    std::reverse(board_.begin(), board_.end());
    CountPossibleMoves();
}

void Board::CheckNewKing() {
    for (int column = 0; column < boardSize_.second; ++column) {
        if (board_[0][column] == WHITE_PIECE) {
            board_[0][column] = WHITE_KING;
        }
        if (board_[boardSize_.first - 1][column] == BLACK_PIECE) {
            board_[boardSize_.first - 1][column] = BLACK_KING;
        }
    }
}

bool Board::isWhiteWon() {
    for (const auto& line : board_) {
        for (auto elem : line) {
            if (elem == WHITE_PIECE) {
                return false;
            }
        }
    }
    return true;
}

int Board::GetNumberPieces(Cell type) const {
    int cnt = 0;
    for (auto& line : board_) {
        for(auto elem : line) {
            cnt += elem == type;
        }
    }
    return cnt;
}

Board::Board(const Board &board) {
    boardSize_ = board.boardSize_;
    possibleMoves_ = board.possibleMoves_;
    board_ = board.board_;
    isShouldAttack_ = board.isShouldAttack_;
}
