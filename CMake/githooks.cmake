# create the git hooks for code checks / validations
set (LOCAL_GIT_DIRECTORY)
if (EXISTS ${CMAKE_SOURCE_DIR}/.git)
    set (LOCAL_GIT_DIRECTORY ${CMAKE_SOURCE_DIR}/.git)
else (EXISTS ${CMAKE_SOURCE_DIR}/.git)
endif (EXISTS ${CMAKE_SOURCE_DIR}/.git)

if (EXISTS ${LOCAL_GIT_DIRECTORY})
    if (NOT EXISTS ${LOCAL_GIT_DIRECTORY}/hooks/pre-commit)
        file(DOWNLOAD https://www.dropbox.com/s/raavcqkjnwbj8h4/pre-commit.sh?dl=1
                ${CMAKE_BINARY_DIR}/pre-commit)

        # Make the downloaded file executable, since it is not by default.
        file(COPY ${CMAKE_BINARY_DIR}/pre-commit
                DESTINATION ${LOCAL_GIT_DIRECTORY}/hooks/
                FILE_PERMISSIONS
                OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_WRITE GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)
        file(REMOVE ${CMAKE_BINARY_DIR}/pre-commit)
    endif (NOT EXISTS ${LOCAL_GIT_DIRECTORY}/hooks/pre-commit)
endif (EXISTS ${LOCAL_GIT_DIRECTORY})
##