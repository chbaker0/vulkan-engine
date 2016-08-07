cmake_minimum_required(VERSION 3.2)

project(vulkan-engine)

find_package(glfw3 3.2)

add_subdirectory(vulkanwrapper)

add_library(vulkan-engine
  $<TARGET_OBJECTS:vulkanwrapper>
  )

target_link_libraries(vulkan-engine)
set_property(TARGET vulkan-engine PROPERTY CXX_STANDARD 11)
set_property(TARGET vulkan-engine PROPERTY CXX_STANDARD_REQUIRED ON)
