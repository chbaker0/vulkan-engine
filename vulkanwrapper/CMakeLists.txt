add_library(vulkanwrapper OBJECT
  Instance.cpp
  Instance.hpp
  InstanceFunctionNames.h
  Device.cpp
  Device.hpp
  )

set_property(TARGET vulkanwrapper PROPERTY CXX_STANDARD 11)
set_property(TARGET vulkanwrapper PROPERTY CXX_STANDARD_REQUIRED ON)
