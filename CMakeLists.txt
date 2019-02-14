cmake_minimum_required(VERSION 3.9.2)
project(PlannedObsolescence)

if(UNIX AND APPLE)
    set(PLATFORM "osx" )
elseif(UNIX)
    set(PLATFORM "linux")
else()
    set(PLATFORM "win")
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
        Source/Sprites/ScaledSpriteArray.h
        Source/Sprites/ScaledSpriteArray.cpp
        Source/Managers/SceneManager.h
        Source/Managers/SceneManager.cpp
        Source/FileHandler/FileHandler.h
        Source/FileHandler/FileHandler.cpp
        Source/Managers/CharacterManager.h
        Source/Managers/CharacterManager.cpp
        Source/Scenes/Scene.h
        Source/Scenes/Splashscreen.h
        Source/Scenes/Splashscreen.cpp
        Source/Scenes/GameCore.h
        Source/Scenes/GameCore.cpp
        Source/Scenes/GameOver.h
        Source/Scenes/GameOver.cpp
        Source/Scenes/MainMenu.h
        Source/Scenes/MainMenu.cpp
        Source/Scenes/PauseMenu.h
        Source/Scenes/PauseMenu.cpp
        Source/Characters/Character.h
        Source/Characters/Character.cpp
        Source/Characters/Boss.h
        Source/Characters/Boss.cpp
        Source/Characters/Goon.h
        Source/Characters/Goon.cpp
        Source/Characters/LabTechnician.h
        Source/Characters/LabTechnician.cpp
        Source/Characters/Security.h
        Source/Characters/Security.cpp
        Source/Constants.h
        Source/Characters/Pathfinding/PathfindingMap.h
        Source/Characters/Pathfinding/PathNode.h
        Source/Characters/Pathfinding/NodeConnection.h
        Source/Math/Point.h
        Source/Math/Point.cpp
        Source/Math/Vector.h
        Source/Math/Vector.cpp
        Source/Map/GameMap.cpp
        Source/Map/GameMap.h
        Source/Map/Room.cpp
        Source/Map/Room.h
        Source/Map/Tile.cpp
        Source/EventSystem/Observer.cpp
        Source/EventSystem/Observer.h
        Source/EventSystem/Subject.cpp
        Source/EventSystem/Subject.h
        Source/EventSystem/Entity.h
        Source/Map/Tile.h
        Source/Characters/Pathfinding/PathfindingMap.cpp
        Source/Debug/DebugText.h
        Source/Debug/DebugText.cpp
        Source/Viewport/Camera.h
        Source/Viewport/Camera.cpp
        Source/ConfigParsers/CharacterData.h
        Source/ConfigParsers/TileData.h
        Source/Viewport/ClickArea.cpp
        Source/Viewport/ClickArea.h
        Source/Keybinds/Keybinds.h
        Source/Keybinds/Keybinds.cpp)

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

if ( CMAKE_COMPILER_IS_GNUCC )
    list(APPEND BUILD_FLAGS_FOR_CXX
        "-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor"
        "-Wold-style-cast" "-Wunused" "-pedantic"
        "-Woverloaded-virtual" "-Wpedantic" "-Wconversion"
        "-Wduplicated-cond" "-Wduplicated-branches" "-Wlogical-op"
        "-Wnull-dereference" "-Wuseless-cast"
        "-Wno-unused-parameter" "-Werror")

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS_FOR_CXX}>)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )
elseif( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

if ( CMAKE_COMPILER_IS_GNUCC )
    list(APPEND BUILD_FLAGS_FOR_CXX
            "-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor"
            "-Wold-style-cast" "-Wunused" "-pedantic"
            "-Woverloaded-virtual" "-Wpedantic" "-Wconversion"
            "-Wduplicated-cond" "-Wduplicated-branches" "-Wlogical-op"
            "-Wnull-dereference" "-Wuseless-cast"
            "-Wno-unused-parameter" "-Werror")

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS_FOR_CXX}>)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )
elseif( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

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

## Copy launcher to build directory on Windows
if (${PLATFORM} MATCHES "win")
    configure_file(${CMAKE_SOURCE_DIR}/Launcher/PO_Launcher.exe ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Launcher.exe COPYONLY)
endif()

## enable static linking against gcc build
if (WIN32 AND NOT BUILD_SHARED_LIBS AND NOT MSVC)
    target_link_libraries(${PROJECT_NAME} -static)
endif()

## utility scripts
SET(ENABLE_SOUND ON CACHE BOOL "Adds SoLoud to the Project" FORCE)
include(CMake/datapak.cmake)
target_link_libraries(${PROJECT_NAME} soloud)

## build types
set(CMAKE_CONFIGURATION_TYPES Debug;Release)
