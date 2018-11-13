#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

#include "graph.hpp"
#include "position.hpp"
#include "delaunay.hpp"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "app.hpp"

App app(1280, 720);

void resize_callback(GLFWwindow* window, int width, int height) {
  app.resize(width, height);
}

int main() {
  int node_c; std::cin >> node_c;
  std::vector<Position> nodes;
  for (int i = 0; i < node_c; i++) {
    float x, y;
    std::cin >> x;
    std::cin >> y;
    nodes.push_back(Position(x, y));
  }
  
  Delaunay solution(nodes, false);
  solution.calculateDistances();
  Graph graph(solution.getRawGraph());
  
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

  std::vector<float> nodes_2;
  std::vector<std::pair<int, int>> edges;
  for (Position p : nodes) {
    nodes_2.push_back((float)p.getX());
    nodes_2.push_back((float)p.getY());    
  }

  graph = graph.kruskal();
  for (int i = 0; i < graph.numNodes(); i++) {
    for (auto e : graph.edgesFrom(i)){
      edges.push_back(std::pair<int, int>(i, e.getTo()));
    }
  }

  app.setNodes(nodes_2);
  app.setEdges(edges);

  
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
