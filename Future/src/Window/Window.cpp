#include "Window.hpp"

namespace Future
{
    Window::Window(const std::string& title, int width, int height, bool fullscreen)
        : mTitle(title), mWidth(width), mHeight(height), mFullscreen(fullscreen),
          sdlWindow(nullptr), sdlScreenSurface(nullptr), mRunning(false)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            FE_CORE_ERROR("SDL could not initialize!");
        }
    }

    Window::~Window()
    {
        Destroy();
    }

    bool Window::Init()
    {
        bool success = true;
        FE_CORE_INFO("Initializing game window");

        // TODO: Hide window til engine loads fully

        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL; //SDL_WINDOW_VULKAN alt backend
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

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
                FE_CORE_INFO("Screen surface assigned");
            }
            glSdlContext = SDL_GL_CreateContext(sdlWindow);
            if (glSdlContext != nullptr)
            {
                FE_CORE_INFO("SDL_GLContext created");
                mRunning = true;
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

    void Window::ToggleWindowVisibility()
    {
        if (mWindowVisible)
        {
            mWindowVisible = false;
            SDL_HideWindow(sdlWindow);
        }
        else
        {
            mWindowVisible = true;
            SDL_ShowWindow(sdlWindow);
        }
    }

    void Window::SetWindowTitle(const std::string &title)
    {
        mTitle = title;
        SDL_SetWindowTitle(sdlWindow, mTitle.c_str());
    }

    SDL_Event Window::Tick()
    {
        SDL_Event e;
        if (mRunning)
        {
            SDL_GL_SwapWindow(sdlWindow);

            if (mBoundCursor)
            {
                SDL_WarpMouseInWindow(sdlWindow, mWidth / 2, mHeight / 2);
            }

            while (SDL_PollEvent(&e))
            {
                //ImGui_ImplSDL2_ProcessEvent(&e);
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
        return e;
    }
}
