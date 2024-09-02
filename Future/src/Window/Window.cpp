#include "Window.hpp"
#include "../Log.hpp"
#include "SDL.h"
#include <thread>
#include <glad/glad.h>

namespace Future
{
    Window::Window(const std::string& title, int width, int height, bool fullscreen)
        : mTitle(title), mWidth(width), mHeight(height), mFullscreen(fullscreen),
          sdlWindow(nullptr), sdlScreenSurface(nullptr), mRunning(false)
    {

    }

    Window::~Window()
    {
        Destroy();
    }

    bool Window::Init()
    {
        bool success = true;

        FE_CORE_INFO("Initializing game window");

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            FE_CORE_ERROR("SDL could not initialize!");
            success = false;
        }
        else
        {
            FE_CORE_INFO("SDL2 Initialized");

            Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

            if (mFullscreen)
            {
                flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            }

            sdlWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, flags);
            if (sdlWindow == nullptr)
            {
                FE_CORE_ERROR("Window could not be created!");
                success = false;
            }
            else
            {
                FE_CORE_INFO("Window created");
                sdlScreenSurface = SDL_GetWindowSurface(sdlWindow);
                if (sdlScreenSurface != nullptr)
                {
                    FE_CORE_INFO("Screen surface created");
                }
                glSdlContext = SDL_GL_CreateContext(sdlWindow);
                if (glSdlContext != nullptr)
                {
                    FE_CORE_INFO("GL-SDL Renderer context created");
                    mRunning = true;
                }
            }
        }
        return success;
    }

    void Window::Destroy()
    {
        if (sdlScreenSurface)
        {
            SDL_FreeSurface(sdlScreenSurface);
            sdlScreenSurface = nullptr;
        }
        if (sdlWindow)
        {
            SDL_DestroyWindow(sdlWindow);
            sdlWindow = nullptr;
        }
        SDL_Quit();
    }

    bool Window::IsRunning() const
    {
        return mRunning;
    }

    void Window::ToggleBindCursor()
    {
        if (mBoundCursor)
        {
            mBoundCursor = false;
            SDL_ShowCursor(SDL_ENABLE);
        }
        else
        {
            mBoundCursor = true;
            SDL_ShowCursor(SDL_DISABLE);
        }
    }

    void Window::Tick()
    {
        if (mRunning)
        {
            SDL_GL_SwapWindow(sdlWindow);

            if (mBoundCursor)
            {
                SDL_WarpMouseInWindow(sdlWindow, mWidth / 2, mHeight / 2);
            }

            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    mRunning = false;
                }
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.scancode == SDL_SCANCODE_TAB)
                    {
                        ToggleBindCursor();
                    }
                }
            }
        }
    }
}
