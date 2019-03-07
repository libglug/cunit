
function(add_unit_test)
    set(SINGLE_VALS TARGETNAME)
    set(MULTI_VALS SOURCES INCLUDE_DIRS LINK_LIBS DEFINES)
    cmake_parse_arguments(UT "" "${SINGLE_VALS}" "${MULTI_VALS}" "${ARGN}")

    configure_unit_test(${UT_TARGETNAME} "${UT_SOURCES}" FILES_WO_MOCK)

    add_executable(
        ${UT_TARGETNAME}
        ${FILES_WO_MOCK} # add the transformed files (the built files)
        ${UT_SOURCES}    # add the original source (for use by IDE)
    )
    foreach(ORIG_FILE ${UT_SOURCES})
        set_source_files_properties(${ORIG_FILE} PROPERTIES HEADER_FILE_ONLY TRUE)
    endforeach()

    target_compile_definitions(
        ${UT_TARGETNAME}
        PRIVATE
            _CRT_SECURE_NO_WARNINGS # clear the secure warnings for things like strcat
    )

    target_include_directories(
        ${UT_TARGETNAME}
        PRIVATE
            ${UT_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${UT_TARGETNAME}
        ${UT_LINK_LIBS}
    )

    target_compile_definitions(
        ${UT_TARGETNAME}
        PRIVATE
            ${UT_DEFINES}
    )
    add_test(${UT_TARGETNAME} ${UT_TARGETNAME})
endfunction()

function(configure_unit_test TARGETNAME SOURCES TRANSFORMED_FILES)
    set(MOCK_FCN_PREFIX "mock_")
    set(MOCK_FCN_SIG "CU_MOCK_FCN")

    set(CONF_PATH "${CMAKE_CURRENT_BINARY_DIR}/conf/${TARGETNAME}")

    foreach(SOURCE ${SOURCES})
        string(
            REGEX REPLACE "^(../)+" ""
                FLATTENED_PATH
                ${SOURCE}
        )
        file(READ ${SOURCE} FILE_SRC)
        parse_mock_include("${FILE_SRC}" ${SOURCE} MOCKLESS_SRC MOCK_PATHS_OUT MOCK_INC_OUT)
        file(WRITE ${CONF_PATH}/${FLATTENED_PATH} "${MOCKLESS_SRC}")

        list(
            LENGTH MOCK_PATHS_OUT
            NEW_MOCK_LEN
        )
        if (NEW_MOCK_LEN GREATER 0)
            list(
                APPEND ALL_MOCK_INCLUDE
                ${MOCK_INC_OUT}
            )
            list(
                APPEND MOCK_PATHS
                ${MOCK_PATHS_OUT}
            )
        endif()
        list(
            APPEND FILES_WO_MOCK
            ${CONF_PATH}/${FLATTENED_PATH}
        )
        unset(MOCK_PATHS_OUT)
        unset(MOCK_INC_OUT)
    endforeach()

    foreach(FILE_WO_MOCK ${FILES_WO_MOCK})
        file(READ ${FILE_WO_MOCK} FILE_SRC)
        parse_mock_func("${FILE_SRC}" MOCKLESS_SRC MOCK_FCN_NAMES)
        file(WRITE ${FILE_WO_MOCK} "${MOCKLESS_SRC}")

        list(
            LENGTH MOCK_FCN_NAMES
                NEW_MOCK_LEN
        )

        if (NEW_MOCK_LEN GREATER 0)
            list(
                APPEND ALL_MOCK_FCN
                ${MOCK_FCN_NAMES}
            )
        endif()
        unset(MOCK_FCN_NAMES)
    endforeach()

    list(
        LENGTH ALL_MOCK_FCN
            TOTAL_FCN_MOCKS
    )
    if (${TOTAL_FCN_MOCKS} GREATER 0)
        foreach(FILE_WO_MOCK ${FILES_WO_MOCK})
            file(READ ${FILE_WO_MOCK} FILE_SRC)

            foreach(MOCK_FCN ${ALL_MOCK_FCN})
                string(
                    REGEX REPLACE
                        "([^a-zA-Z0-9_])(${MOCK_FCN})([^a-zA-Z0-9_])" "\\1${MOCK_FCN_PREFIX}\\2\\3"
                        FILE_SRC
                        "${FILE_SRC}"
                )
            endforeach()

            file(WRITE ${FILE_WO_MOCK} "${FILE_SRC}")
        endforeach()
    endif()

    list(
        LENGTH ALL_MOCK_INCLUDE
            TOTAL_MOCK_INCS
    )
    if (${TOTAL_MOCK_INCS} GREATER 0)
        foreach(FILE_WO_MOCK ${FILES_WO_MOCK})
            file(READ ${FILE_WO_MOCK} FILE_SRC)

            math(EXPR MAX_MOCK_IDX "${TOTAL_MOCKS}-1")
            foreach(CURR_MOCK_IDX RANGE ${MAX_MOCK_IDX})
                list(
                    GET MOCK_PATHS
                        ${CURR_MOCK_IDX}
                        CURR_MOCK
                )
                string(
                    REGEX MATCH "#include[^<\"]*[<\"]${CURR_MOCK}[>\"]."
                        INCLUDE_MATCH
                        "${FILE_SRC}"
                )
                if (INCLUDE_MATCH)
                    list(
                        GET ALL_MOCK_INCLUDE
                            ${CURR_MOCK_IDX}
                            CURR_BODY
                    )
                    file(READ ${CURR_BODY} MOCK_NEWINC)
                    string(
                        REPLACE "${INCLUDE_MATCH}" "${MOCK_NEWINC}"
                            FILE_SRC
                            "${FILE_SRC}"
                    )
                endif()
            endforeach()
            file(WRITE ${FILE_WO_MOCK} "${FILE_SRC}")
        endforeach()
    endif()
    set(${TRANSFORMED_FILES} "${FILES_WO_MOCK}" PARENT_SCOPE)
endfunction()

function(parse_mock_func FILE_SRC PARSED_FILE MOCK_FCN_NAMES)
    string(
        LENGTH ${MOCK_FCN_SIG}
            MOCK_FCN_SIG_LEN
    )

    set(MOCKLESS_SRC "${FILE_SRC}")
    set(MOCKLESS_PARSED "${FILE_SRC}")
    string(
        LENGTH "${MOCKLESS_SRC}"
            SRC_LEN
    )
    string(
        FIND "${MOCKLESS_SRC}"
            ${MOCK_FCN_SIG}
            MOCK_START
    )
    while (${MOCK_START} GREATER -1)
        string(
            SUBSTRING "${MOCKLESS_SRC}"
                0
                ${MOCK_START}
                MOCKLESS_HEAD
        )
        set(NESTED_PAREN 0)
        math(EXPR CHR_IDX "${MOCK_START}+${MOCK_FCN_SIG_LEN}")
        while(CHR_IDX LESS ${SRC_LEN})
            string(
                SUBSTRING "${MOCKLESS_SRC}"
                    ${CHR_IDX}
                    1
                    SRC_CHR
            )
            math(EXPR CHR_IDX "${CHR_IDX}+1")
            string(
                COMPARE EQUAL
                    "${SRC_CHR}"
                    "("
                    IS_OPEN
            )
            string(
                COMPARE EQUAL
                    "${SRC_CHR}"
                    ")"
                    IS_CLOSE
            )
            if (${IS_OPEN})
                math(EXPR NESTED_PAREN "${NESTED_PAREN}+1")
            endif()
            if (${IS_CLOSE})
                math(EXPR NESTED_PAREN "${NESTED_PAREN}-1")
            endif()
            if (${NESTED_PAREN} EQUAL 0)
                math(EXPR MOCK_LEN "${CHR_IDX}-${MOCK_START}")
                math(EXPR MOCK_END "${CHR_IDX}+1")
                string(
                    SUBSTRING "${MOCKLESS_SRC}"
                        ${MOCK_START}
                        ${MOCK_LEN}
                        MOCK
                )
                string(
                    REPLACE "${MOCK}" ""
                        MOCKLESS_SRC
                        "${MOCKLESS_SRC}"
                )
                string(
                    REGEX REPLACE
                        "CU_MOCK_FCN[ ]*\\(([^,]+),[ ]*(.*)\\)" "extern \\1 ${MOCK_FCN_PREFIX}\\2"
                        PARSED_MOCK
                        "${MOCK}"
                )
                string(
                    REPLACE "${MOCK}" "${PARSED_MOCK}"
                        MOCKLESS_PARSED
                        "${MOCKLESS_PARSED}"
                )

                string(
                    REGEX MATCH ",[ ]*([^\\(]+)"
                        MOCK_NAME
                        "${MOCK}"
                )
                list(
                    APPEND MOCK_FCNS
                    "${CMAKE_MATCH_1}"
                )

                break()
            endif()
            string(
                LENGTH "${MOCKLESS_SRC}"
                    NEW_LEN
            )
            if (${CHR_IDX} GREATER ${NEW_LEN})
                message(FATAL_ERROR "Failed parsing ${MOCK_FCN_SIG} in ${FILE}")
            endif()
        endwhile()
        if (NOT ${NESTED_PAREN} EQUAL 0)
            message(FATAL_ERROR "Failed parsing  ${MOCK_FCN_SIG} in ${FILE}")
        endif()

        string(
            FIND "${MOCKLESS_SRC}"
                ${MOCK_FCN_SIG}
                MOCK_START
        )
    endwhile()

    set(${PARSED_FILE} "${MOCKLESS_PARSED}" PARENT_SCOPE)
    set(${MOCK_FCN_NAMES} "${MOCK_FCNS}" PARENT_SCOPE)

endfunction()

function(parse_mock_include FILE_SRC FILE_PATH PARSED_FILE MOCK_PATHS MOCK_NEWINC)
    string(
        REGEX MATCHALL "#include CU_MOCK_INCLUDE *\\([^,]*,[^\\)]+\\)"
            MOCK_DEFS
            "${FILE_SRC}"
    )
    string(
        REGEX MATCH "(.*)/"
            SRC_PATH
            "${FILE_PATH}"
    )
    foreach(MOCK_DEF ${MOCK_DEFS})
        string(
            REGEX MATCH "\\(((\"[^\"]+\")|([^,]+)), ([^\\)]+)"
                MOCK_HEAD
                "${MOCK_DEF}"
        )
        string(
            REPLACE ${MOCK_DEF} "#include ${CMAKE_MATCH_4}"
                FILE_SRC
                "${FILE_SRC}"
        )
        string(
            REPLACE "\"" ""
                CMAKE_MATCH_1
                "${CMAKE_MATCH_1}"
        )
        string(
            REPLACE "\"" ""
                CMAKE_MATCH_4
                "${CMAKE_MATCH_4}"
        )
        string(
            STRIP "${CMAKE_MATCH_1}"
                CMAKE_MATCH_1
        )
        list(
            APPEND ${MOCK_PATHS}
                "${CMAKE_MATCH_1}"
        )
        list(
            APPEND ${MOCK_NEWINC}
                "${SRC_PATH}${CMAKE_MATCH_4}"
        )
    endforeach()

    set(${PARSED_FILE} "${FILE_SRC}" PARENT_SCOPE)
    set(${MOCK_PATHS} "${${MOCK_PATHS}}" PARENT_SCOPE)
    set(${MOCK_NEWINC} "${${MOCK_NEWINC}}" PARENT_SCOPE)
endfunction()
