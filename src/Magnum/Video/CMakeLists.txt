#
#   This file is part of Magnum.
#
#   Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
#               2020 Vladimír Vondruš <mosra@centrum.cz>
#
#   Permission is hereby granted, free of charge, to any person obtaining a
#   copy of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom the
#   Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#   DEALINGS IN THE SOFTWARE.
#

find_package(Corrade REQUIRED PluginManager)

set(MagnumVideo_SRCS
    Video.cpp)

set(MagnumVideo_GracefulAssert_SRCS
    AbstractImporter.cpp)

set(MagnumVideo_HEADERS
    AbstractImporter.h
    Video.h
    visibility.h)

if(NOT CORRADE_PLUGINMANAGER_NO_DYNAMIC_PLUGIN_SUPPORT)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
                   ${CMAKE_CURRENT_BINARY_DIR}/configure.h)
endif()

# Objects shared between main and test library
add_library(MagnumVideoObjects OBJECT
    ${MagnumVideo_SRCS}
    ${MagnumVideo_HEADERS})

target_include_directories(MagnumVideoObjects PUBLIC
    $<TARGET_PROPERTY:Magnum,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:Corrade::PluginManager,INTERFACE_INCLUDE_DIRECTORIES>)

if(NOT BUILD_STATIC)
    target_compile_definitions(MagnumVideoObjects PRIVATE "MagnumVideoObjects_EXPORTS")
endif()

if(NOT BUILD_STATIC OR BUILD_STATIC_PIC)
    set_target_properties(MagnumVideoObjects PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
set_target_properties(MagnumVideoObjects PROPERTIES FOLDER "Magnum/Video")

# Video library
add_library(MagnumVideo ${SHARED_OR_STATIC}
    $<TARGET_OBJECTS:MagnumVideoObjects>
    ${MagnumVideo_GracefulAssert_SRCS})

# target_include_directories(MagnumVideo PUBLIC ${OPENAL_INCLUDE_DIR})

set_target_properties(MagnumVideo PROPERTIES
    DEBUG_POSTFIX "-d"
    FOLDER "Magnum/Video")

if(NOT BUILD_STATIC)
    set_target_properties(MagnumVideo PROPERTIES VERSION ${MAGNUM_LIBRARY_VERSION} SOVERSION ${MAGNUM_LIBRARY_SOVERSION})
elseif(BUILD_STATIC_PIC)
    set_target_properties(MagnumVideo PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
target_link_libraries(MagnumVideo Magnum Corrade::PluginManager)

install(TARGETS MagnumVideo
    RUNTIME DESTINATION ${MAGNUM_BINARY_INSTALL_DIR}
    LIBRARY DESTINATION ${MAGNUM_LIBRARY_INSTALL_DIR}
    ARCHIVE DESTINATION ${MAGNUM_LIBRARY_INSTALL_DIR})
install(FILES ${MagnumVideo_HEADERS} DESTINATION ${MAGNUM_INCLUDE_INSTALL_DIR}/Video)

# Magnum Video target alias for superprojects
add_library(Magnum::Video ALIAS MagnumVideo)

# if(BUILD_TESTS)
#     # Library with graceful assert for testing
#     add_library(MagnumAudioTestLib ${SHARED_OR_STATIC}
#         $<TARGET_OBJECTS:MagnumAudioObjects>
#         ${MagnumAudio_GracefulAssert_SRCS})
#     target_compile_definitions(MagnumAudioTestLib PRIVATE
#         "CORRADE_GRACEFUL_ASSERT" "MagnumAudio_EXPORTS")
#     target_include_directories(MagnumAudioTestLib PUBLIC ${OPENAL_INCLUDE_DIR})
#     set_target_properties(MagnumAudioTestLib PROPERTIES
#         DEBUG_POSTFIX "-d"
#         FOLDER "Magnum")
#     if(BUILD_STATIC_PIC)
#         set_target_properties(MagnumAudioTestLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
#     endif()
#     target_link_libraries(MagnumAudioTestLib
#         Magnum
#         Corrade::PluginManager
#         ${OPENAL_LIBRARY})
#     if(WITH_SCENEGRAPH)
#         target_link_libraries(MagnumAudioTestLib MagnumSceneGraph)
#     endif()

#     add_subdirectory(Test)
# endif()
