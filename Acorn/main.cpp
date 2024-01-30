#include <iostream>
#include <SDL.h>
#include "Application.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Engine.hpp"

//#undef main


int main(int argc, char* args[]) {

    //Application app;

    //app.loop();
    //app.draw();

    Engine::GetInstance()->Init();

    while (Engine::GetInstance()->isRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update(1);
        Engine::GetInstance()->Render();
    }

    Engine::GetInstance()->Clean();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}