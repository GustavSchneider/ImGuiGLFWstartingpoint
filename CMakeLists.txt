cmake_minimum_required(VERSION 3.18)
project(GUI)
set (CMAKE_CXX_STANDARD 17)

if (UNIX)
  find_package( glfw3 3.3 REQUIRED )
    set (OpenGL_GL_PREFERENCE "GLVND")
endif()
if(WIN32)  
  include_directories(${PROJECT_SOURCE_DIR}/lib/glfw/include)
  set (GLFW3_STATIC_LIBRARIES ${PROJECT_SOURCE_DIR}/lib/glfw/lib-vc2015/glfw3.lib)
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif()

if (UNIX)
  find_package(GLEW REQUIRED)
  if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
  endif()
endif()
if (WIN32)
  include_directories(${PROJECT_SOURCE_DIR}/lib/glew)
  set (GLEW_LIBRARIES ${PROJECT_SOURCE_DIR}/lib/glew/glew32.lib)
endif()

if (UNIX)
  find_package(Freetype REQUIRED)
endif()

include_directories(src)
include_directories(libs/imgui)
include_directories(libs/imgui/misc/freetype)
include_directories(libs/imgui/misc/fonts)
include_directories(libs/imgui/misc/natvis)


add_library(GUI
  src/ImGui_init.cpp
  libs/imgui/imgui_draw.cpp
  libs/imgui/imgui_impl_glfw_gl3.cpp
  libs/imgui/misc/freetype/imgui_freetype.cpp
  libs/imgui/imgui_demo.cpp
  libs/imgui/imgui.cpp)

target_link_libraries(GUI
  Freetype::Freetype
  glfw
  OpenGL::GL
  ${GLEW_LIBRARIES}
  GLEW::GLEW)


add_executable(
  main
  main.cpp)

target_link_libraries(
  main
  GUI)
