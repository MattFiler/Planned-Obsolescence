file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/CI)

set(MD5URL "https://www.dropbox.com/s/isgcjzqpi7a1rjl/payload.md5?dl=1")
set(MD5DL ${CMAKE_SOURCE_DIR}/CI/datpak.zip.md5)

## download the MD5
file( DOWNLOAD
        ${MD5URL}
        ${MD5DL}
        TIMEOUT 30
        STATUS MD5_DL )

## make sure it downloaded successfully
list(GET MD5_DL 0,0 RC)
if( NOT "${RC}" STREQUAL "0" )
    return()
endif()

## read the md5sum
file(STRINGS ${MD5DL} MD5FILE LIMIT_INPUT 32)
message("${MD5FILE}")

set(PAKURL "https://www.dropbox.com/s/biigqm9f031u3cc/payload.zip?dl=1")
set(PAKDL  ${CMAKE_SOURCE_DIR}/CI/datpak.zip)
set(PAKDIR ${CMAKE_SOURCE_DIR}/CI/datpak)

## correct version of arhive already present?
if(EXISTS ${PAKDL})
    file(MD5 ${PAKDL} MD5TMP)
    message("${MD5TMP}")
else()
    set(MD5TMP " ")
endif()

## download if needed
if( NOT ${MD5FILE} EQUAL ${MD5TMP} )
    file( DOWNLOAD
            ${PAKURL}
            ${PAKDL}
            SHOW_PROGRESS
            EXPECTED_MD5 ${MD5FILE}
            STATUS DOWNLOADED
            TIMEOUT 120)
endif()

## unzip the archive
file(MAKE_DIRECTORY ${PAKDIR})
execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${PAKDL}
        WORKING_DIRECTORY ${PAKDIR})

## utility scripts
add_subdirectory(${PAKDIR})
