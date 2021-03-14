#include "ImGui_init.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
  exit(1);
}

void debugCallbackFun(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length,const GLchar *message, const void *userParam) {
  puts(message);
}

void
Window::main_loop()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window_ = glfwCreateWindow(args_.width, args_.height, "Main Window", NULL, NULL);
    if (!window_)
        return;
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync 

    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallbackFun, NULL);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (args_.resize_func)
        glfwSetWindowSizeCallback(window_, args_.resize_func);

    // Setup style
    ImGui::StyleColorsDark();

    //ImGui_ImplGlfwGL3_Init(window_, true);
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    if (args_.init_func) {
        args_.init_func();
    }
    
    std::cout << "begin main_loop" << std::endl;
    while (!glfwWindowShouldClose(window_) && running_) {
        //std::cout << "interation" << std::endl;
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (args_.render_func)
            args_.render_func(glfwGetTime());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window_);    
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

int Window::start(WindowArgs args)
{
    args_ = args;
    running_ = true;
    this->main_loop();
    //std::thread t([this] { this->main_loop(); });    
    //t.detach();
}

int Window::stop()
{
    running_ = false;
}

bool Window::is_running()
{
    return running_;
}
