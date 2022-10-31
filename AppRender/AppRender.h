//
// Created by Семён Чубенко on 20.10.2022.
//

#ifndef CHECKERS_APPRENDER_H
#define CHECKERS_APPRENDER_H

#include "../AppModel/AppModel.h"
#include "SFML/Graphics.hpp"
#include "../Assets/Assets.h"

class AppRender : public sf::Drawable, public sf::Transformable {
private:
    AppModel* m_model;
    sf::RenderWindow m_window;

    size_t screenWidth_;
    size_t screenHeight_;

    size_t underBoardOffset_;
    size_t cellSize_;

    std::pair<size_t, size_t> selectedCell_;

    void Init();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    explicit AppRender(AppModel* model);
    sf::RenderWindow& window() { return m_window; };

    void Render();

    void SetSelectedCell(std::pair<size_t, size_t> cell);

    size_t GetCellSize() const {return cellSize_;}
};


#endif //CHECKERS_APPRENDER_H
