//
// Created by Семён Чубенко on 20.10.2022.
//

#ifndef CHECKERS_APPRENDER_H
#define CHECKERS_APPRENDER_H

#include "../AppModel/AppModel.h"
#include "SFML/Graphics.hpp"

class AppRender : public sf::Drawable, public sf::Transformable {
private:
    AppModel* m_model;
    sf::RenderWindow m_window;

    int screen_width;
    int screen_height;

    void Init();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    explicit AppRender(AppModel* model);
    sf::RenderWindow& window() { return m_window; };

    void Render();
};


#endif //CHECKERS_APPRENDER_H
