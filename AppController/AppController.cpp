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
        }

        m_render->Render();
    }
}
