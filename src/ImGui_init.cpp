#include "ImGui_init.hpp"

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
    if (!glfwInit()) {
        return;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window_ = glfwCreateWindow(args_.width, args_.height, "Main Window", NULL, NULL);
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
    ImGui_ImplGlfwGL3_Init(window_, true);

    if (args_.resize_func)
        glfwSetWindowSizeCallback(window_, args_.resize_func);

    // Setup style
    ImGui::StyleColorsDark();

    if (args_.init_func) {
        args_.init_func();
    }
    
    std::cout << "begin main_loop" << std::endl;
    while (!glfwWindowShouldClose(window_) && running_) {
        //std::cout << "interation" << std::endl;
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (args_.render_func)
            args_.render_func(glfwGetTime());
        
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window_);    
    }

    ImGui_ImplGlfwGL3_Shutdown();
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
