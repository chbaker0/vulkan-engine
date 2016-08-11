add_library(vulkanwrapper OBJECT
  Instance.cpp
  Instance.hpp
  InstanceFunctionList.h
  Device.cpp
  Device.hpp
  DeviceFunctionList.h
  DeviceObject.hpp
  )

set_property(TARGET vulkanwrapper PROPERTY CXX_STANDARD 11)
set_property(TARGET vulkanwrapper PROPERTY CXX_STANDARD_REQUIRED ON)
