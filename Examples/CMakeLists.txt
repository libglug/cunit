# This file assumes that the CUnit target is built by this project too
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

    install(
        TARGETS
            ${TARGET}
        DESTINATION
            ${INSTALL_ROOT}/share/CUnit
    )
endfunction()

add_example(AutomatedTest AutomatedTest/AutomatedTest.c)
add_example(BasicTest BasicTest/BasicTest.c)
add_example(ConsoleTest ConsoleTest/ConsoleTest.c)
add_example(Demo_fprintf Demo_fprintf/CUnitExample.c)
