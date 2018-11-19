if (${BUILD_STATIC} STREQUAL "ON")
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

list(
    APPEND
    SOURCES
    Headers/CUnit/Automated.h
    Headers/CUnit/Basic.h
    Headers/CUnit/Console.h
    Headers/CUnit/CUError.h
    Headers/CUnit/CUnit.h.in
    Headers/CUnit/CUnit_intl.h
    Headers/CUnit/MyMem.h
    Headers/CUnit/TestDB.h
    Headers/CUnit/TestRun.h
    Headers/CUnit/Util.h
    Sources/Automated/Automated.c
    Sources/Basic/Basic.c
    Sources/Console/Console.c
    Sources/Framework/CUError.c
    Sources/Framework/MyMem.c
    Sources/Framework/TestDB.c
    Sources/Framework/TestRun.c
    Sources/Framework/Util.c
#    Sources/Test/test_cunit.c
#    Sources/Test/test_cunit.h
)

add_library(
    ${CUNIT_LIB_NAME}
    ${LIB_TYPE}
    ${SOURCES}
)

if (${LIB_TYPE} STREQUAL "SHARED")
    target_compile_definitions(
        ${CUNIT_LIB_NAME}
        PRIVATE
        CU_DLL
        CU_BUILD_DLL
    )
endif()

target_include_directories(
    ${CUNIT_LIB_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}> # because "CUnit.h" is a configured file
    $<BUILD_INTERFACE:${CUNIT_INC_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_INC_DIR}>
)

install(
    TARGETS ${CUNIT_LIB_NAME}
    DESTINATION ${INSTALL_LIB_DIR}
)

# and install the lib in the share dir because Windows
if (${BUILD_XMPLS} STREQUAL "ON")
    install(
        TARGETS ${CUNIT_LIB_NAME}
        DESTINATION ${INSTALL_SHARE_DIR}
    )
endif()