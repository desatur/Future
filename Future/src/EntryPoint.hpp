#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include "Engine.hpp"

extern Future::Engine* Future::CreateApplication();

int main(int argc, char *argv[]) { // DO NOT CHANGE THOSE VALUES!!!!!!! REQUIRED BY SDL2
    Future::Log::Init();
    FE_CORE_INFO("Hello World!");
    auto app = Future::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif //ENTRYPOINT_HPP
