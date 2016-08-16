#include "DeviceMock.hpp"

#include "vulkanwrapper/DeviceFunctionList.h"

DeviceProcMock::DeviceProcMock()
{
#define X(name) setProcAddr(#name, (PFN_vkVoidFunction) DefaultProc<PFN_##name>::proc);
    VKW_DEVICE_FUNCTION_LIST
#undef X
}
