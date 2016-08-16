#ifndef PROCMOCK_HPP
#define PROCMOCK_HPP

#include <map>
#include <string>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

class ProcMock
{
public:
    PFN_vkVoidFunction getProcAddr(const char *name) const;
    void setProcAddr(const char *name, PFN_vkVoidFunction procAddr);

private:
    std::map<std::string, PFN_vkVoidFunction> procMap;
};

template <typename PFN_T>
struct DefaultProc;

template <typename... T>
struct DefaultProc<void (VKAPI_PTR *)(T...)>
{
    static void proc(T...)
    {
        return;
    }
};

template <typename... T>
struct DefaultProc<VkResult (VKAPI_PTR *)(T...)>
{
    static VkResult proc(T...)
    {
        return VK_NOT_READY;
    }
};

template <typename... T>
struct DefaultProc<PFN_vkVoidFunction (VKAPI_PTR *)(T...)>
{
    static PFN_vkVoidFunction proc(T...)
    {
        return nullptr;
    }
};

#endif // PROCMOCK_HPP
