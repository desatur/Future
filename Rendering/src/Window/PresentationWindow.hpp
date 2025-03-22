#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <string>
#include <vector>

class PresentationWindow {
public:
    PresentationWindow(int width, int height, const std::string& title);
    ~PresentationWindow();

    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR& surface);
    bool ShouldClose() const;
    void PollEvents() const;
    void Cleanup();
    void Initialize();

    int Width;
    int Height;
    std::string Title;
    GLFWwindow* BaseWindow;
    
    static std::vector<PresentationWindow*> Windows;
    static PresentationWindow* MainWindow;
};
