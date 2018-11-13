#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

App app(1280, 720);

void resize_callback(GLFWwindow* window, int width, int height) {
  //resize code
}

int main() {  
  // Setup window
  if (!glfwInit())
    return 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui GLFW+OpenGL3 example", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync
  glfwSetWindowSizeCallback(window, resize_callback);  
  glewInit();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
  ImGui_ImplGlfwGL3_Init(window, true);

  // Setup style
  ImGui::StyleColorsDark();  
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    ImGui_ImplGlfwGL3_NewFrame();

    // ImGui code goes here

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);    
  }


  ImGui_ImplGlfwGL3_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
