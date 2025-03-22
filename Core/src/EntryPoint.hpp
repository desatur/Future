#pragma once
#include "Core.hpp"
//#include "./Log/Log.hpp"

extern Core* CreateApplication();

//int argc, char *argv[]
int main() {
    //Log::Init();
    //LOG_INFO("Starting Future " Future_VERSION);
    auto app = CreateApplication();
    app->Run();
    delete app;
    return 0;
}