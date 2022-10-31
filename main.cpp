#include <iostream>
#include "AppModel/AppModel.h"
#include "AppRender/AppRender.h"
#include "AppController/AppController.h"

int main() {
    Assets::Instance().Load();
    auto appModel = new AppModel();
    auto appRender = new AppRender(appModel);
    AppController appController(appModel, appRender);
    appController.Run();
    return 0;
}
