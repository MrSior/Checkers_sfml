#include <iostream>
#include "AppModel/AppModel.h"
#include "AppRender/AppRender.h"
#include "AppController/AppController.h"

int main() {
    AppModel appModel;
    AppRender appRender(&appModel);
    AppController appController(&appModel, &appRender);
    appController.Run();
    return 0;
}
