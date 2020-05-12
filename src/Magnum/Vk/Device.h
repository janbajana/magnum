#ifndef Magnum_Vk_Device_h
#define Magnum_Vk_Device_h
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

/** @file
 * @brief Enum @ref Magnum::Vk::PhysicalDeviceType
 * @m_since_latest
 */

#include "Magnum/Magnum.h"
#include "Magnum/Vk/Vulkan.h"
#include "Magnum/Vk/visibility.h"

namespace Magnum { namespace Vk {

/**
@brief Physical device type
@m_since_latest

Wraps a @type_vk_keyword{VkPhysicalDeviceType}.
@m_enum_values_as_keywords
*/
enum class PhysicalDeviceType: Int {
    /** Anything that does not match any other available types */
    Other = VK_PHYSICAL_DEVICE_TYPE_OTHER,

    /** Typically a device embedded in or tightly coupled with the host */
    IntegratedGpu = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,

    /**
     * Typically a separate processor connected to the host via an interlink
     */
    DiscreteGpu = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,

    /** Typically a virtual node in a virtualization environment */
    VirtualGpu = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,

    /** Typically running on the same processors as the host */
    Cpu = VK_PHYSICAL_DEVICE_TYPE_CPU
};

/**
@debugoperatorenum{PhysicalDeviceType}
@m_since_latest
*/
MAGNUM_VK_EXPORT Debug& operator<<(Debug& debug, PhysicalDeviceType value);

}}

#endif
