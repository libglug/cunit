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
    list(
        APPEND CMAKE_MACOSX_RPATH
            "@ORIGIN"
            "@executable_path"
            "@loader_path"
    )
    list(
        APPEND CMAKE_INSTALL_RPATH
            "$ORIGIN"
    )
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    add_custom_command(
        TARGET
            ${TARGET}
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}/Examples
    )

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
