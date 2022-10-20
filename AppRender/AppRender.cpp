//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppRender.h"

AppRender::AppRender(AppModel *model) {
    m_model = model;
    Init();
}

void AppRender::Init() {
    screen_width = 1024;
    screen_height = 1024;
    m_window.create(sf::VideoMode(screen_width, screen_height), "Checkers");
}

void AppRender::Render() {
    m_window.clear(sf::Color(255,255,255));
    m_window.draw(*this);
    m_window.display();
}

void AppRender::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}
