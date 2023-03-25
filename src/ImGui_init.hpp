#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

typedef void (*init_func_t)();
typedef void (*render_func_t)(double time);
typedef void (*resize_func_t)(GLFWwindow* window, int width, int height);
typedef void (*key_func_t)(GLFWwindow* window, int key, int scancode, int action, int mods);

struct WindowArgs {
    int width;
    int height;
    init_func_t init_func;
    resize_func_t resize_func;
    render_func_t render_func;
    key_func_t key_func;
};
    
class Window {
private:
    WindowArgs args_;
    GLFWwindow* window_;
    
    void main_loop();

    std::atomic<bool> running_;
public:
    int init();
    int start(WindowArgs args);
    int stop();
    bool is_running();
};

