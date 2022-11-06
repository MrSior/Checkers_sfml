//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppModel.h"

AppModel::AppModel() {
    botManager_ = std::make_shared<BotManager>();
    Init();
}

void AppModel::Init() {
    selectedCell_ = {-1, -1};
    isCellSelected_ = false;
    isPLayerTurn = true;
}

const std::vector<std::vector<Cell>> &AppModel::GetBoard() {
    return board_.GetBoard();
}

const std::pair<size_t, size_t> &AppModel::GetBoardSize() {
    return board_.GetBoardSize();
}


void AppModel::SetSelectedCell(std::pair<size_t, size_t> cell) {
    if (!board_.isPieceWhite(cell)) return;
    selectedCell_ = cell;
    selectedCellPossibleMoves_ = board_.GetCellPossibleMoves(selectedCell_);
    isCellSelected_ = true;
}

const std::pair<size_t, size_t> &AppModel::GetSelectedCell() {
    return selectedCell_;
}

bool AppModel::GetIsCellSelected() const {
    return isCellSelected_;
}

bool AppModel::CheckIsPossibleMove(std::pair<size_t, size_t> cell) {
    const auto moves = board_.GetCellPossibleMoves(selectedCell_);
    return std::find(board_.GetPossibleMoves().begin(),
                     board_.GetPossibleMoves().end(),
                     std::make_pair(selectedCell_, cell)) != board_.GetPossibleMoves().end();
//           && std::find(moves.begin(), moves.end(), cell) != moves.end();

}

void AppModel::Move(std::pair<size_t, size_t> cell) {
    if (cell == selectedCell_) return;
    bool isPlayerShouldAttack = board_.GetIsShouldAttack();
    board_.Move(selectedCell_, cell);
    isCellSelected_ = false;
    isPLayerTurn = board_.GetIsShouldAttack() && isPlayerShouldAttack;
}

bool AppModel::isPieceWhite(std::pair<size_t, size_t> cell) const {
    return board_.isPieceWhite(cell);
}

void AppModel::BotsMove() {
    auto isBotShouldAttack = botManager_->GetIsShouldAttack(board_);
    auto move = botManager_->GetBotsMove(board_);
    board_.Move(move.first, move.second);
    isPLayerTurn = !(botManager_->GetIsShouldAttack(board_) && isBotShouldAttack);
}

bool AppModel::IsPlayerWon() {
    return board_.isWhiteWon();
}
