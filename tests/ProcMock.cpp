#include "ProcMock.hpp"

PFN_vkVoidFunction ProcMock::getProcAddr(const char *name) const
{
    auto it = procMap.find(std::string(name));

    if (it == procMap.end())
    {
        return nullptr;
    }
    else
    {
        return it->second;
    }
}

void ProcMock::setProcAddr(const char *name, PFN_vkVoidFunction proc)
{
    procMap[std::string(name)] = proc;
}
