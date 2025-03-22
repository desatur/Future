#pragma once
#include "Core.hpp"
#include "./Log/Log.hpp"

extern Future::Core* CreateApplication();

int main(int argc, char** argv) {
    Log::Init();
    LOG_INFO("initm");
    auto app = CreateApplication();
    app->Run();
    delete app;
    return 0;
}