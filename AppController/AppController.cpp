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
                    if(m_model->GetIsPlayerTurn() && !m_model->IsPlayerWon()) {
                        if (!m_model->GetIsCellSelected() || m_model->isPieceWhite({line, column})) {
                            m_model->SetSelectedCell({line, column});
                        } else {
                            if (m_model->CheckIsPossibleMove({line, column})) {
                                m_model->Move({line, column});
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    m_model->SwitchBot(0);
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    //m_model->SwitchBot(1);
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    m_model->SwitchBot(2);
                }
                if (event.key.code == sf::Keyboard::R) {
                    m_model->Init();
                }
            }
        }
        m_render->Render();

        if (!m_model->GetIsPlayerTurn() && !m_model->IsPlayerWon()){
            sf::sleep(sf::milliseconds(250));
            m_model->BotsMove();
        }
    }
}
