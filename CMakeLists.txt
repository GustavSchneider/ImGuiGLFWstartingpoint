cmake_minimum_required(VERSION 3.18)
project(imgui)
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
include_directories(imgui-docking)
include_directories(imgui-docking/misc/freetype)
include_directories(imgui-docking/misc/fonts)
include_directories(imgui-docking/misc/natvis)
include_directories(imgui-docking/backends)

add_library(imgui
  src/ImGui_init.cpp
  imgui-docking/imgui_draw.cpp  
  imgui-docking/misc/freetype/imgui_freetype.cpp
  imgui-docking/imgui_demo.cpp
  imgui-docking/imgui_tables.cpp
  imgui-docking/imgui_widgets.cpp
  imgui-docking/imgui.cpp
  imgui-docking/backends/imgui_impl_glfw.cpp
  imgui-docking/backends/imgui_impl_opengl3.cpp
  )

target_link_libraries(imgui
  Freetype::Freetype
  OpenGL::GL
  ${GLEW_LIBRARIES}
  GLEW::GLEW
  glfw)
