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
        gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
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
                sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
                if (sdlRenderer != nullptr)
                {
                    FE_CORE_INFO("SDL Renderer created");
                    mRunning = true;
                }
                mRunning = true; // temp
                sdlGLContext = SDL_GL_CreateContext(sdlWindow);
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

    void Window::Loop()
    {
        while (mRunning)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    mRunning = false;
                }

                SDL_UpdateWindowSurface(sdlWindow);
                SDL_Delay(1000 / 30);
            }
        }
    }
}
