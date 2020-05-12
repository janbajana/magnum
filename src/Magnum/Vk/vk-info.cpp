/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/Utility/FormatStl.h>

#include "Magnum/Magnum.h"
#include "Magnum/Vk/Device.h"
#include "Magnum/Vk/Result.h"
#include "Magnum/Vk/Version.h"
#include "Magnum/Vk/Vulkan.h"

#include "MagnumExternal/Vulkan/flextVkGlobal.h"

using namespace Magnum;

/** @page magnum-vk-info Magnum Vulkan Info
@brief Displays information about Magnum engine Vulkan capabilities

@m_footernavigation

@todoc
*/

int main() {
    Debug{} << "Instance layers:";

    {
        VkLayerProperties properties[50]{};
        UnsignedInt count = Containers::arraySize(properties);
        MAGNUM_VK_INTERNAL_ASSERT_RESULT(vkEnumerateInstanceLayerProperties(&count, properties));
        for(std::size_t i = 0; i != count; ++i)
            Debug{} << properties[i].layerName;
    }

    Debug{} << Debug::newline << "Instance extensions:";

    {
        VkExtensionProperties properties[50]{};
        UnsignedInt count = Containers::arraySize(properties);
        MAGNUM_VK_INTERNAL_ASSERT_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &count, properties));
        for(std::size_t i = 0; i != count; ++i)
            Debug{} << properties[i].extensionName;
    }

    VkInstance instance;
    {
        VkInstanceCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        MAGNUM_VK_INTERNAL_ASSERT_RESULT(vkCreateInstance(&info, nullptr, &instance));
    }
    flextVkInitInstance(instance, &flextVkInstance);

    {
        VkPhysicalDevice devices[5]{};
        UnsignedInt count = Containers::arraySize(devices);
        MAGNUM_VK_INTERNAL_ASSERT_RESULT(vkEnumeratePhysicalDevices(instance, &count, devices));
        Debug{} << Debug::newline << "Found" << count << "devices:";
        for(std::size_t i = 0; i != count; ++i) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(devices[i], &properties);
            Debug{} << Debug::newline << i << properties.deviceName
                << Utility::formatString("API {}.{}.{}",
                    Vk::versionMajor(properties.apiVersion),
                    Vk::versionMinor(properties.apiVersion),
                    Vk::versionPatch(properties.apiVersion))
                << Utility::formatString("driver {}.{}.{}",
                    Vk::versionMajor(properties.driverVersion),
                    Vk::versionMinor(properties.driverVersion),
                    Vk::versionPatch(properties.driverVersion))
                << Vk::PhysicalDeviceType(properties.deviceType);

            {
                Debug{} << Debug::newline << "Device extensions:";

                VkExtensionProperties extensions[500]{};
                UnsignedInt count = Containers::arraySize(extensions);
                MAGNUM_VK_INTERNAL_ASSERT_RESULT(vkEnumerateDeviceExtensionProperties(devices[i], nullptr, &count, extensions));
                for(std::size_t i = 0; i != count; ++i)
                    Debug{} << extensions[i].extensionName;
            }

            {
                Debug{} << Debug::newline << "Device features:";

                VkPhysicalDeviceFeatures features{};
                vkGetPhysicalDeviceFeatures(devices[i], &features);
                Debug{} << "shaderFloat64" << features.shaderFloat64;
                Debug{} << "pipelineStatisticsQuery" << features.pipelineStatisticsQuery;
            }

            {
                VkQueueFamilyProperties properties[5]{};
                UnsignedInt count = Containers::arraySize(properties);
                vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &count, properties);
                Debug{} << Debug::newline << "Found" << count << "device queue families:";
                for(std::size_t i = 0; i != count; ++i) {
                    Debug d;
                    d << " " << properties[i].queueCount;
                    if(properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) d << "compute";
                    if(properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) d << "graphics";
                    if(properties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) d << "sparse-binding";
                    if(properties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) d << "transfer";
                }
            }

            {
                Debug{} << Debug::newline << "Device memory properties:";

                VkPhysicalDeviceMemoryProperties properties{};
                vkGetPhysicalDeviceMemoryProperties(devices[i], &properties);
                Debug{} << Debug::newline << "Found" << properties.memoryTypeCount << "memory types:";
                for(std::size_t i = 0; i != properties.memoryTypeCount; ++i) {
                    Debug{} << "  host visible:" << !!(properties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) << properties.memoryTypes[i].heapIndex;
                }
                Debug{} << Debug::newline << "Found" << properties.memoryHeapCount << "memory heaps:";
                for(std::size_t i = 0; i != properties.memoryHeapCount; ++i) {
                    Debug{} << "  device local:" << !!(properties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) << properties.memoryHeaps[i].size/1024/1024 << "MB";
                }
            }
        }
    }

    vkDestroyInstance(instance, nullptr);
}
