//
// Created by Семён Чубенко on 20.10.2022.
//

#ifndef CHECKERS_APPCONTROLLER_H
#define CHECKERS_APPCONTROLLER_H

#include "../AppModel/AppModel.h"
#include "../AppRender/AppRender.h"

class AppController {
private:
    AppModel* m_model;
    AppRender* m_render;
public:
    AppController(AppModel* model, AppRender* render);

    void Run();
};


#endif //CHECKERS_APPCONTROLLER_H
