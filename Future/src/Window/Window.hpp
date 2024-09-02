#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "SDL.h"
#include "../Core.hpp"
#include "../Log.hpp"

namespace Future
{
    class FE_API Window
    {
    public:
        Window(const std::string& title = "SDL2 Window", int width = 1920, int height = 1080, bool fullscreen = false); // Constructor with parameters for customization
        ~Window();

        bool Init();
        void Destroy();
        void Tick();
        void ToggleBindCursor();
        void ToggleWindowVisibility();
        void SetWindowTitle(const std::string& title);

        [[nodiscard]] bool IsRunning() const;
        [[nodiscard]] SDL_Window* GetWindow() const { return sdlWindow; }
        [[nodiscard]] SDL_Surface* GetScreenSurface() const { return sdlScreenSurface; }
    private:
        std::string mTitle;
        int mWidth;
        int mHeight;
        bool mFullscreen = false;
        bool mBoundCursor = false;
        bool mWindowVisible = true;

        SDL_Window* sdlWindow;
        SDL_Surface* sdlScreenSurface;
        SDL_GLContext glSdlContext;

        bool mRunning;
    };
}

#endif // WINDOW_HPP
