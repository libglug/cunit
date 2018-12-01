project(CUnit)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(CUnit)

set(INSTALL_ROOT ${CMAKE_INSTALL_PREFIX} CACHE STRING "Specify a custom install directory")
option(BUILD_XMPLS "Build (and install) the examples")

# install documentation
install(
    DIRECTORY
        doc/.
    DESTINATION
        ${INSTALL_ROOT}/doc/CUnit
)

# install the headers with the documentation
file(GLOB HDR_FILES ${INSTALL_ROOT}/include/CUnit/*)
install(
    FILES
        ${HDR_FILES}
    DESTINATION
        ${INSTALL_ROOT}/doc/CUnit/headers
)

# install man pages
install(
    DIRECTORY
        man/.
    DESTINATION
        ${INSTALL_ROOT}/man
)

#install examples
if (${BUILD_XMPLS} STREQUAL "ON")
    add_subdirectory(Examples)
    # copy the installed libs to the example root (mostly for Windows support)
    file(GLOB LIB_FILES ${INSTALL_ROOT}/lib/*)
    install(
        FILES
            ${LIB_FILES}
        DESTINATION
            ${INSTALL_ROOT}/share/CUnit
    )
endif()

