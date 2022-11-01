//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppRender.h"

AppRender::AppRender(AppModel *model) {
    m_model = model;
    Init();
}

void AppRender::Init() {
    underBoardOffset_ = 100;
    cellSize_ = 128;
    const auto boardSize = m_model->GetBoardSize();
    screenWidth_ = boardSize.second * cellSize_;
    screenHeight_ = boardSize.first * cellSize_ + underBoardOffset_;
    m_window.create(sf::VideoMode(screenWidth_, screenHeight_), "Checkers");
}

void AppRender::Render() {
    m_window.clear({0x35, 0x35,0x35});
    m_window.draw(*this);
    m_window.display();
}

void AppRender::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    const auto board = m_model->GetBoard();
    const auto selectedCell = m_model->GetSelectedCell();

    for (size_t line = 0; line < screenHeight_ - underBoardOffset_; line += cellSize_) {
        for(size_t column = 0; column < screenWidth_; column += cellSize_) {
            auto cell = sf::RectangleShape({(float)cellSize_, (float)cellSize_});
            cell.setPosition({(float)column, (float)line});
            sf::Color cellColor;
            if ((line / cellSize_) % 2) {
                if ((column / cellSize_) % 2) {
                    cellColor = {0xAD, 0xB5, 0xBD};
                } else {
                    cellColor = {0x6C, 0x75, 0x7D};
                }
            } else {
                if ((column / cellSize_) % 2 == 0) {
                    cellColor = {0xAD, 0xB5, 0xBD};
                } else {
                    cellColor = {0x6C, 0x75, 0x7D};
                }
            }
            if (m_model->GetIsCellSelected()
                && line / cellSize_ == selectedCell.first
                && column / cellSize_ == selectedCell.second) {
                cell.setFillColor({0xDE, 0xB8, 0x41});
            } else {
                cell.setFillColor(cellColor);
            }
            target.draw(cell);
        }
    }

    if (m_model->GetIsCellSelected()) {
        const auto possibleMoves = m_model->GetSelectedCellPossibleMoves();
        for (auto elem: possibleMoves) {
            sf::CircleShape circleShape;
            circleShape.setPosition((float) (elem.second * cellSize_ + cellSize_ / 2 - 10),
                                    (float) (elem.first * cellSize_ + cellSize_ / 2 - 10));
            circleShape.setRadius(10);
            circleShape.setFillColor({0xDE, 0xB8, 0x41});
            target.draw(circleShape);
        }
    }

    for (int line = 0; line < board.size(); ++line) {
        for (int column = 0; column < board[line].size(); ++column) {
            if (board[line][column] == BLACK_PIECE){
                sf::Sprite sprite;
                sprite.setTexture(Assets::Instance().blackPieceT);
                sprite.setPosition(sf::Vector2f((float)column * (float)cellSize_ + 9, (float)line * (float)cellSize_ + 9));
                target.draw(sprite);
            }
            if (board[line][column] == WHITE_PIECE){
                sf::Sprite sprite;
                sprite.setTexture(Assets::Instance().whitePieceT);
                sprite.setPosition(sf::Vector2f((float)column * (float)cellSize_ + 9, (float)line * (float)cellSize_ + 9));
                target.draw(sprite);
            }
        }
    }
}

