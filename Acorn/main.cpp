#include <iostream>
#include <SDL.h>
#include "Application.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#undef main
using namespace std;

int main(int argc, char* args[]) {

    Application app;

    app.loop();
    //app.draw();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}