set(EX_NAME Demo_fprintf)

list(
    APPEND
    SOURCES
    ../ExampleTests.h
    ../ExampleTests.c
    CUnitExample.c
)

add_executable(
    ${EX_NAME}
    ${SOURCES}
)

target_link_libraries(
    ${EX_NAME}
    ${CUNIT_LIB_NAME}
)

target_include_directories(
    ${EX_NAME}
    PUBLIC
    ..
)

target_include_directories(
    ${EX_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${BUILD_ROOT}> # because "CUnit.h" is a configured file
    $<BUILD_INTERFACE:${CUNIT_INC_ROOT}>
    $<INSTALL_INTERFACE:${INSTALL_INC_DIR}>
)

install(
    TARGETS ${EX_NAME}
    DESTINATION ${INSTALL_ROOT}/${INSTALL_SHARE_DIR}
)
