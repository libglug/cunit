cmake_minimum_required(VERSION 3.0)
project(CUnit_root)

option(BUILD_XMPLS "Build (and install) the examples")

add_subdirectory(CUnit)

# install documentation
install(
    DIRECTORY
        doc/.
    DESTINATION
        doc/CUnit
)

# install the headers with the documentation
file(GLOB HDR_FILES include/CUnit/*)
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

# build and install examples
if (${BUILD_XMPLS} STREQUAL "ON")
    # disable find_package in the Examples subproject for finding CUnit
    macro(find_package)
        if (NOT "${ARGV0}" STREQUAL "CUnit")
            _find_package(${ARGV})
        endif()
    endmacro()

    add_subdirectory(Examples)

    add_custom_command(
        OUTPUT
            copy_cunit
        COMMAND
            ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}/Examples
        DEPENDS
            CUnit
    )

    add_custom_target(
        copy_cunit_example
        ALL
        DEPENDS
            copy_cunit
    )

endif()

