#pragma once

#include "budCovCommon.hpp"
#include "budCovObject.hpp"
#include "budCovUtils.hpp"
#include "budCovDevice.h"

namespace cov {

using contextCallback = void(*)(const char*, const void*, size_t, void*);

class Context : public ClObject<ObjectMagic, ObjectMagic::CONTEXT_MAGIC> {
    friend class Queue;
    friend class Program;
public:
    explicit Context(const Device& device, contextCallback pfnNotify, void* userData);
    ~Context();

    bool hasDevice(const Device* device) const { return device == &m_device; }
private:
    const Device& m_device;
    contextCallback m_callback;
    void* m_userData;
    VkDevice m_vkDevice;
    VkQueue m_vkQueue;
};

cl_context createContext(const cl_context_properties* properties,
                         cl_uint numDevices,
                         const cl_device_id* devices,
                         contextCallback pfnNotify,
                         void* userData,
                         cl_int* errcodeRet);

cl_int retainContext(cl_context context);

cl_int releaseContext(cl_context context);

}
