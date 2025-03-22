#include "PresentationWindow.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

/*
    TODO: runtime_error -> log
*/

std::vector<PresentationWindow*> PresentationWindow::Windows;
PresentationWindow* PresentationWindow::MainWindow = nullptr;

PresentationWindow::PresentationWindow(int width, int height, const std::string& title)
    : Width(width), Height(height), Title(title), BaseWindow(nullptr) {
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
