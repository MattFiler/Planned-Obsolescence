cmake_minimum_required(VERSION 3.9.2)
project(PlannedObsolescence)

if(UNIX AND APPLE)
    set(PLATFORM "osx" )
elseif(UNIX)
    set(PLATFORM "linux")
else()
    set(PLATFORM "win")
endif()

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS}                          \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor    \
        -Wold-style-cast -Wunused -pedantic          \
        -Woverloaded-virtual -Wpedantic -Wconversion \
        -Wduplicated-cond                            \
        -Wduplicated-branches -Wlogical-op           \
        -Wnull-dereference -Wuseless-cast            \
        -Wno-unused-parameter -Werror")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )
elseif( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

## hide console unless debug build ##
if (NOT CMAKE_BUILD_TYPE STREQUAL  "Debug" AND WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

## set to true to use dlls instead of static libs ##
set(BUILD_SHARED_LIBS false)

## itch.io and gamedata settings ##
set(GAMEDATA_FOLDER "data")
set(ITCHIO_USER     "")

## files used to build this game
add_executable(
        ${PROJECT_NAME}
        main.cpp
        Source/PlannedObsolescence.cpp
        Source/PlannedObsolescence.h
        Source/Core/GameObject.h
        Source/Core/Geometry.h
        Source/Core/Geometry.cpp
        Source/Core/GameObject.cpp
        Source/Core/AnimatedSprite.h
        Source/Core/AnimatedSprite.cpp
        Source/Core/SceneManager.h
        Source/Core/SceneManager.cpp
        Source/Core/FileHandler.h
        Source/Core/FileHandler.cpp
        Source/Core/Scene.h
        Source/Scenes/TitleScene.h
        Source/Scenes/TitleScene.cpp
        Source/Constants.h)

## library includes
target_include_directories(
        ${PROJECT_NAME}
        SYSTEM
        PRIVATE
        "${CMAKE_SOURCE_DIR}/Libs/ASGE/include"
        "${CMAKE_SOURCE_DIR}/Libs/nlohmann")

## compile language settings
target_compile_features(
        ${PROJECT_NAME}
        PRIVATE
        cxx_std_17)

## build the game libs folder
add_library(ASGE UNKNOWN IMPORTED)
add_subdirectory(Libs)
target_link_libraries(${PROJECT_NAME} ASGE)

## copy the dlls post build
if(BUILD_SHARED_LIBS)
    # copy the game engine dll to bin
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different

            "${GameEngineDLL}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    if(WIN32 AND NOT MSVC)
        # copy the mingw runtime files to bin
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Libs/mingw64/bin $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endif()


## enable static linking against gcc build
if (WIN32 AND NOT BUILD_SHARED_LIBS AND NOT MSVC)
    target_link_libraries(${PROJECT_NAME} -static)
endif()

## utility scripts
include(CMake/clang.format.cmake)
include(CMake/githooks.cmake)
include(CMake/itch.io.cmake)

## build types
set(CMAKE_CONFIGURATION_TYPES Debug;Release)
