cmake_minimum_required(VERSION 3.0)
project(CUnit_root)

add_subdirectory(CUnit)

option(BUILD_XMPLS "Build (and install) the examples")
if (${BUILD_XMPLS} STREQUAL "ON")
    # disable find_package in the Examples subproject for finding CUnit
    macro(find_package)
        if (NOT "${ARGV0}" STREQUAL "CUnit")
            _find_package(${ARGV})
        endif()
    endmacro()

    add_subdirectory(Examples)
endif()

# install documentation
install(
    DIRECTORY
        doc/.
    DESTINATION
        doc/CUnit
)

# install the headers with the documentation
file(GLOB HDR_FILES ${CMAKE_INSTALL_PREFIX}/include/CUnit/*)
install(
    FILES
        ${HDR_FILES}
    DESTINATION
        doc/CUnit/headers
)

# install man pages
install(
    DIRECTORY
        man/.
    DESTINATION
        man
)
