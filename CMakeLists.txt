cmake_minimum_required(VERSION 3.2)

project(vulkan-engine)

find_package(glfw3 3.2)

add_subdirectory(vulkanwrapper)

add_executable(vulkan-engine
  main.cpp
  $<TARGET_OBJECTS:vulkanwrapper>
  )

target_link_libraries(vulkan-engine glfw SPIRV glslang)
