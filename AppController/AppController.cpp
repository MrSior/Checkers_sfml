//
// Created by Семён Чубенко on 20.10.2022.
//

#include "AppController.h"

AppController::AppController(AppModel *model, AppRender *render) {
    m_model = model;
    m_render = render;
}

void AppController::Run() {
    sf::Event event{};

    while (m_render->window().isOpen()) {
        while (m_render->window().pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_render->window().close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePosition = sf::Mouse::getPosition(m_render->window());
                    size_t line = mousePosition.y / m_render->GetCellSize();
                    size_t column = mousePosition.x / m_render->GetCellSize();
                    m_render->SetSelectedCell({line, column});
                    std::cout << column << line;
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    m_model->GetPossibleMoves(7, 2);
                }
            }
        }

        m_render->Render();
    }
}
