cmake_minimum_required(VERSION 3.2)

project(vulkan-engine)

find_package(glfw3 3.2)

include_directories(.)

add_subdirectory(vulkanwrapper)

add_library(vulkan-engine
  $<TARGET_OBJECTS:vulkanwrapper>
  )

target_link_libraries(vulkan-engine)
set_property(TARGET vulkan-engine PROPERTY CXX_STANDARD 11)
set_property(TARGET vulkan-engine PROPERTY CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)

# Documentation

find_package(Doxygen)

if(DOXYGEN_FOUND)
  find_program(DOXYGEN_DOT dot)
  if(DOXYGEN_DOT EQUAL "DOXYGEN_DOT-NOTFOUND")
    set(HAVE_DOT "NO")
  else()
    set(HAVE_DOT "YES")
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Doxygen running...")
endif(DOXYGEN_FOUND)
