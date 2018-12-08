find_package(CUnit REQUIRED)
function(add_example TARGET TARGET_MAIN)
    add_executable(
        ${TARGET}
        ${TARGET_MAIN}
        # and the common example files
        ExampleTests.c
        ExampleTests.h
    )

    target_include_directories(
        ${TARGET}
        PRIVATE
            .
    )

    target_link_libraries(
        ${TARGET}
        CUnit
    )

    # TODO: double check these RPATHs actually work
    set(CMAKE_MACOSX_RPATH "$ORIGIN")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    install(
        TARGETS
            ${TARGET}
        DESTINATION
            share/CUnit
    )
endfunction()

add_example(AutomatedTest AutomatedTest/AutomatedTest.c)
add_example(BasicTest BasicTest/BasicTest.c)
add_example(ConsoleTest ConsoleTest/ConsoleTest.c)
add_example(Demo_fprintf Demo_fprintf/CUnitExample.c)
