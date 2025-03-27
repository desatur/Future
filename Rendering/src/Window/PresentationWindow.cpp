#include "PresentationWindow.hpp"

/*
    TODO: runtime_error -> log
*/

namespace Future {
    // Static
    std::vector<PresentationWindow*> PresentationWindow::Windows;
    PresentationWindow* PresentationWindow::MainWindow = nullptr;

    // Normal
    std::atomic<bool> UpdateOnTick(true);

    void PresentationWindow::PollWindowEvents() {
        for (PresentationWindow* window : PresentationWindow::Windows) {
            glfwPollEvents();
        }
    }

    void PresentationWindow::SwapWindowBuffers() {
        for (PresentationWindow* window : PresentationWindow::Windows) {
            glfwSwapBuffers(window->BaseWindow);
        }
    }
    
    PresentationWindow::PresentationWindow(int width, int height, const std::string& title)
        : Width(width), Height(height), Title(title), BaseWindow(nullptr), UpdateOnTick(true) {
        if (!MainWindow){
            MainWindow = this;
        }
        Windows.push_back(this);
        Initialize();
    }
    
    PresentationWindow::~PresentationWindow() {
        Cleanup();
        auto it = std::find(Windows.begin(), Windows.end(), this);
        if (it != Windows.end()) {
            Windows.erase(it);
        }
    }
    
    void PresentationWindow::Initialize() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW.");
        }
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        BaseWindow = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
        
        if (!BaseWindow) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window.");
        }
        
        glfwMakeContextCurrent(BaseWindow);
    }

    void PresentationWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR& surface) {
        if (glfwCreateWindowSurface(instance, BaseWindow, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface.");
        }
    }
    
    bool PresentationWindow::ShouldClose() const {
        return glfwWindowShouldClose(BaseWindow);
    }
    
    void PresentationWindow::PollEvents() const {
        glfwPollEvents();
    }
    
    void PresentationWindow::Cleanup() {
        if (BaseWindow) {
            glfwDestroyWindow(BaseWindow);
        }
        glfwTerminate();
    }
}

