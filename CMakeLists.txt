cmake_minimum_required(VERSION 3.18)
project(imgui)
set (CMAKE_CXX_STANDARD 17)

  find_package( glfw3 3.3 REQUIRED )
    set (OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif()


  find_package(GLEW REQUIRED)
  if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
  endif()



  find_package(Freetype REQUIRED)

include_directories(src)
include_directories(imgui)
include_directories(imgui/misc/freetype)
include_directories(imgui/misc/fonts)
include_directories(imgui/misc/natvis)
include_directories(imgui/backends)

add_library(imgui
  src/ImGui_init.cpp
  imgui/imgui_draw.cpp  
  imgui/misc/freetype/imgui_freetype.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
  )

target_link_libraries(imgui
  Freetype::Freetype
  OpenGL::GL
  ${GLEW_LIBRARIES}
  GLEW::GLEW
  glfw)
