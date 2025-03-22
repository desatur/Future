#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include "SDL.h"
#include <glad/glad.h>
#include "../Log.hpp"
#include <imgui_impl_sdl2.h>

namespace Future
{
    class Window {
    public:
        Window(const std::string& title = "SDL2 Window", int width = 1920, int height = 1080, bool fullscreen = false); // Constructor with parameters for customization
        ~Window();
        static Window Get();

        bool Init();
        void Destroy();
        SDL_Event Tick();
        
        void ToggleBindCursor();
        void ToggleWindowVisibility();
        void SetWindowTitle(const std::string& title);

        [[nodiscard]] bool IsRunning() const { return mRunning; };
        [[nodiscard]] SDL_Window* GetWindow() const { return sdlWindow; }
        [[nodiscard]] SDL_Surface* GetScreenSurface() const { return sdlScreenSurface; }
        [[nodiscard]] SDL_GLContext GetGLContext() const { return glSdlContext; }
    private:
        static Window* instance;
        std::string mTitle;
        int mWidth;
        int mHeight;
        bool mRunning = false;
        bool mFullscreen = false;
        bool mBoundCursor = false;
        bool mWindowVisible = true;

        SDL_Window* sdlWindow;
        SDL_Surface* sdlScreenSurface;
        SDL_GLContext glSdlContext;
    };
}
