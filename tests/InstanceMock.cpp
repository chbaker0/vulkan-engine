#include "InstanceMock.hpp"

#include "vulkanwrapper/InstanceFunctionList.h"

InstanceProcMock::InstanceProcMock()
{
#define X(name) setProcAddr(#name, (PFN_vkVoidFunction) DefaultProc<PFN_##name>::proc);
    VKW_INSTANCE_FUNCTION_LIST
#undef X
}
