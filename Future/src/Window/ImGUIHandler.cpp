#include "ImGUIHandler.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "../Log.hpp"

namespace Future
{
    ImGUIHandler::ImGUIHandler(Window* window){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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
}