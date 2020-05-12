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

#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Magnum.h"
#include "Magnum/Vk/Version.h"
#include "Magnum/Vk/Vulkan.h"

namespace Magnum { namespace Vk { namespace Test { namespace {

struct VersionTest: TestSuite::Tester {
    explicit VersionTest();

    void extract();
};

VersionTest::VersionTest() {
    addTests({&VersionTest::extract});
}

void VersionTest::extract() {
    constexpr UnsignedInt packed = VK_MAKE_VERSION(1, 5, 789);

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #endif
    CORRADE_COMPARE(versionMajor(packed), VK_VERSION_MAJOR(packed));
    CORRADE_COMPARE(versionMinor(packed), VK_VERSION_MINOR(packed));
    CORRADE_COMPARE(versionPatch(packed), VK_VERSION_PATCH(packed));
    CORRADE_COMPARE(versionMajor(packed), 1);
    CORRADE_COMPARE(versionMinor(packed), 5);
    CORRADE_COMPARE(versionPatch(packed), 789);
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif
}

}}}}

CORRADE_TEST_MAIN(Magnum::Vk::Test::VersionTest)
