set(LIB_NAME ${CMAKE_PROJECT_NAME})

if (${BUILD_STATIC} STREQUAL "ON")
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

list(
    APPEND
    SOURCES
    Headers/Automated.h
    Headers/Basic.h
    Headers/Console.h
    Headers/CUError.h
    Headers/CUnit.h.in
    Headers/CUnit_intl.h
    Headers/MyMem.h
    Headers/TestDB.h
    Headers/TestRun.h
    Headers/Util.h
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
    ${LIB_NAME}
    ${LIB_TYPE}
    ${SOURCES}
)

# because "CUnit.h" is a configured file and is temporarily in ${CMAKE_BINARY_DIR}
target_include_directories(
    ${LIB_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_ROOT}/include/${LIB_NAME}>
)
target_include_directories(
    ${LIB_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Headers>
    $<INSTALL_INTERFACE:${INSTALL_ROOT}/include/${LIB_NAME}>
)

install(
    TARGETS ${LIB_NAME}
    DESTINATION ${INSTALL_LIB_DIR}
)
