#include "ImGUIHandler.hpp"

namespace Future
{
    ImGUIHandler::ImGUIHandler(Window* window){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
        int w, h;
        SDL_GetWindowSize(window->GetWindow(), &w, &h);
        io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));

        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetGLContext());
        ImGui_ImplOpenGL3_Init("#version 430");

        if (!ImGui::GetCurrentContext()) {
            FE_CORE_ERROR("ImGui context is not initialized");
        }
        else {
            FE_CORE_INFO("ImGui context is initialized");
        }
    }

    ImGUIHandler::~ImGUIHandler(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGUIHandler::NewFrame(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void ImGUIHandler::DrawFrame(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGUIHandler::DebugWindow(){
        static bool isOpen = true;

        ImGui::Begin("Future Engine Diagnostic Window", &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        ImGui::Text("Rendering Time: %s", std::to_string(Future::Renderer::Get().frameTime).c_str());
        ImGui::Text("Frames Per Second: %s", std::to_string(Future::Renderer::Get().fps).c_str());
        ImGui::Text("Delta Time: %s", std::to_string(Future::Renderer::Get().deltaTime).c_str());

        ImGui::End();
    }
}