find_program(
        GCF NAMES git-clang-format
        PATHS ${CMAKE_SOURCE_DIR}/Tools/*/
        NO_DEFAULT_PATH)

if(GCF)
    execute_process(COMMAND git config hooks.gitClangFormatExe ${GCF})
endif()

find_program(
        CFE NAMES clang-format
        PATHS ${CMAKE_SOURCE_DIR}/Tools/*/${PLATFORM}/)

if(CFE)
    list(APPEND CLANG-FORMAT_ARGS
            -i
            --style=file
            ${CMAKE_SOURCE_DIR}/Source/*.cpp
            ${CMAKE_SOURCE_DIR}/Source/*.h
            )

    add_custom_target(
            ClangFormat
            COMMAND "${CFE}" ${CLANG-FORMAT_ARGS}
            COMMENT "running clang-format"
    )

    execute_process(COMMAND git config hooks.clangFormatExe ${CFE})
endif ()

message("GitFormat:     " ${GCF})
message("ClangFormat:   " ${CFE})