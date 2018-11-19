project(CUnit)
cmake_minimum_required(VERSION 3.0)

set(CUNIT_VER_MAJOR 2)
set(CUNIT_VER_MINOR 2)
set(CUNIT_VER_PATCH 0)

set(CUNIT_LIB_NAME CUnit)
option(BUILD_STATIC "Build as a static library instead of shared")
set(INSTALL_ROOT ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Specify a custom install directory")
option(BUILD_XMPLS "Build (and install) the examples")

set(BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

set(INSTALL_LIB_DIR lib)
set(INSTALL_DOC_DIR doc/${CUNIT_LIB_NAME})
set(INSTALL_INC_DIR include/${CUNIT_LIB_NAME})
set(INSTALL_MAN_DIR man)
set(INSTALL_SHARE_DIR share/${CUNIT_LIB_NAME})

set(CUNIT_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/CUnit)
set(CUNIT_INC_ROOT ${CUNIT_SRC_ROOT}/Headers)
set(CUNIT_INC_DIR ${CUNIT_INC_ROOT}/CUnit)
set(CUNIT_DOC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/doc)
set(CUNIT_EX_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Examples)
set(CUNIT_MAN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/man)

configure_file(${CUNIT_INC_DIR}/CUnit.h.in CUnit.h)
file(GLOB HEADERS "${CUNIT_INC_DIR}/*.h")
list(APPEND HEADERS ${BUILD_ROOT}/CUnit.h)

add_subdirectory(${CUNIT_SRC_ROOT})

install(
    FILES ${HEADERS}
    DESTINATION ${INSTALL_ROOT}/${INSTALL_INC_DIR}
)

install(
    DIRECTORY ${CUNIT_DOC_ROOT}/.
    DESTINATION ${INSTALL_ROOT}/${INSTALL_DOC_DIR}
)

install(
    FILES ${HEADERS}
    DESTINATION ${INSTALL_ROOT}/${INSTALL_DOC_DIR}/headers
)

install(
    DIRECTORY ${CUNIT_MAN_ROOT}/.
    DESTINATION ${INSTALL_ROOT}/${INSTALL_MAN_DIR}
)

if (${BUILD_XMPLS} STREQUAL "ON")
    add_subdirectory(${CUNIT_EX_ROOT})
endif()
