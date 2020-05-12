#ifndef Magnum_Vk_Version_h
#define Magnum_Vk_Version_h
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
 * @brief Function @ref Magnum::Vk::versionMajor(), @ref Magnum::Vk::versionMinor(), @ref Magnum::Vk::versionPatch()
 * @m_since_latest
 */

#include "Magnum/Types.h"
#include "Magnum/Vk/visibility.h"

namespace Magnum { namespace Vk {

/**
@brief Extract major version number from a packed representation
@m_since_latest

Equivalent to @def_vk_keyword{VERSION_MAJOR}, but without C-style casts.
*/
constexpr UnsignedInt versionMajor(UnsignedInt packed) {
    return packed >> 22;
}

/**
@brief Extract minor version number from a packed representation
@m_since_latest

Equivalent to @def_vk_keyword{VERSION_MINOR}, but without C-style casts.
*/
constexpr UnsignedInt versionMinor(UnsignedInt packed) {
    return (packed >> 12) & 0x3ff;
}

/**
@brief Extract minor version number from a packed representation
@m_since_latest

Equivalent to @def_vk_keyword{VERSION_PATCH}, but without C-style casts.
*/
constexpr UnsignedInt versionPatch(UnsignedInt packed) {
    return packed & 0xfff;
}

}}

#endif
