#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL.h"
#include "../Core.hpp"
#include <string>
#include <thread>
#include <atomic>

namespace Future
{
    class FE_API Window
    {
    public:
        Window(const std::string& title = "SDL2 Window", int width = 1920, int height = 1080, bool fullscreen = false); // Constructor with parameters for customization
        ~Window(); // Destructor for cleanup

        bool Init(); // Initialization method
        void Destroy(); // Cleanup method to free resources
        bool IsRunning() const;

        SDL_Window* GetWindow() const { return sdlWindow; }
        SDL_Surface* GetScreenSurface() const { return sdlScreenSurface; }

        void Tick();
        void ToggleBindCursor();

    private:
        std::string mTitle;
        int mWidth;
        int mHeight;
        bool mFullscreen;
        bool mBoundCursor;

        SDL_Window* sdlWindow;
        SDL_Surface* sdlScreenSurface;
        SDL_GLContext glSdlContext;

        bool mRunning;
    };
}

#endif // WINDOW_HPP
