#include "Application/Application.h"

int main() {
    Application application;

    application.Initialize();
    application.Run();
    application.DeInitialize();

    return 0;
}
