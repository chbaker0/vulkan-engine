find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
  main.cpp
  InstanceTests.cpp
  DeviceTests.cpp
  CommandPoolTests.cpp
  ProcMock.cpp
  ProcMock.hpp
  InstanceMock.cpp
  InstanceMock.hpp
  DeviceMock.cpp
  DeviceMock.hpp)

target_link_libraries(tests vulkan-engine glfw ${GTEST_BOTH_LIBRARIES})
set_property(TARGET tests PROPERTY CXX_STANDARD 11)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)
