cmake_minimum_required(VERSION 3.0)

set(VER_MAJOR 2)
set(VER_MINOR 3)
set(VER_PATCH 0)
project(CUnit VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})

option(BUILD_STATIC "Build as a static library instead of shared")

set(CUNIT_CNF_HDRS ${CMAKE_CURRENT_BINARY_DIR}/configured/headers)
set(CUNIT_INC_DIR include/CUnit)

configure_file(${CUNIT_INC_DIR}/Version.h.in ${CUNIT_CNF_HDRS}/CUnit/Version.h)

list(
    APPEND
    SOURCES
    ${CUNIT_INC_DIR}/Assert.h
    ${CUNIT_INC_DIR}/Automated.h
    ${CUNIT_INC_DIR}/Basic.h
    ${CUNIT_INC_DIR}/Console.h
    ${CUNIT_INC_DIR}/CUError.h
    ${CUNIT_INC_DIR}/CUnit.h
    ${CUNIT_INC_DIR}/CUnit_intl.h
    ${CUNIT_INC_DIR}/Export.h
    ${CUNIT_INC_DIR}/MyMem.h
    ${CUNIT_INC_DIR}/TestDB.h
    ${CUNIT_INC_DIR}/TestRun.h
    ${CUNIT_INC_DIR}/Typedefs.h
    ${CUNIT_INC_DIR}/Util.h
    ${CUNIT_INC_DIR}/Version.h.in
    src/Automated/Automated.c
    src/Basic/Basic.c
    src/Console/Console.c
    src/Framework/CUError.c
    src/Framework/MyMem.c
    src/Framework/TestDB.c
    src/Framework/TestRun.c
    src/Framework/Util.c
)

if (${BUILD_STATIC} STREQUAL "ON")
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_library(
    CUnit
    ${LIB_TYPE}
    ${SOURCES}
)

if (${LIB_TYPE} STREQUAL "SHARED")
    target_compile_definitions(
        CUnit
        PRIVATE
            CU_DLL
            CU_BUILD_DLL
    )
endif()

target_include_directories(
    CUnit
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CUNIT_CNF_HDRS}> # because "Version.h" is a configured file
    INTERFACE
        $<INSTALL_INTERFACE:include>
)
target_compile_definitions(
    CUnit
    PRIVATE
        _CRT_SECURE_NO_WARNINGS
)

# export build tree
export(
    TARGETS
        CUnit
    FILE
        CUnitConfig.cmake
)

# export the package to be included in other projects
export(PACKAGE CUnit)

# install the library
install(
    TARGETS
        CUnit
    EXPORT
        FindCUnit
    DESTINATION
        lib
)

# install export file
install(
    EXPORT
        FindCUnit
    DESTINATION
        cmake
)

# install the headers
install(
    DIRECTORY
        ${CUNIT_INC_DIR}
    DESTINATION
        include
    FILES_MATCHING PATTERN
        "*.h"
)
install(
    FILES
        ${CUNIT_CNF_HDRS}/CUnit/Version.h
    DESTINATION
        include/CUnit
)
