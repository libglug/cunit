function(add_unit_test)
    set(SINGLE_VALS TARGETNAME)
    set(MULTI_VALS SOURCES INCLUDE_DIRS LINK_LIBS DEFINES)
    cmake_parse_arguments(UT "" "${SINGLE_VALS}" "${MULTI_VALS}" "${ARGN}")

    set(CONF_PATH "${CMAKE_CURRENT_BINARY_DIR}/conf/${UT_TARGETNAME}")

    set(TOTAL_MOCKS 0)
    foreach(SOURCE ${UT_SOURCES})
        string(REGEX REPLACE "^(../)+" "" FLATTENED_PATH ${SOURCE})
        conf_source(${SOURCE} CONF_SOURCE_STR SOURCE_MOCK_PATHS SOURCE_MOCK_BODIES)

        file(WRITE ${CONF_PATH}/${FLATTENED_PATH} "${CONF_SOURCE_STR}")
        if (DEFINED SOURCE_MOCK_PATHS)
            list(LENGTH SOURCE_MOCK_PATHS NEW_MOCK_LEN)
            math(EXPR NEW_MOCK_LEN "${NEW_MOCK_LEN}-1")
            if (NEW_MOCK_LEN GREATER -1)
                foreach(MOCK_IDX RANGE 0 ${NEW_MOCK_LEN})
                    set(MOCK_BODY${TOTAL_MOCKS} ${SOURCE_MOCK_BODIES${MOCK_IDX}})
                    math(EXPR TOTAL_MOCKS "${TOTAL_MOCKS}+1")
                endforeach()
            endif()
            # TOOD: report errors if there are multiple of the same mock?
            list(
                APPEND
                MOCK_PATHS
                ${SOURCE_MOCK_PATHS}
            )
            unset(SOURCE_MOCK_PATHS)
        endif()
        list(
            APPEND
            FILES_WO_MOCK
            ${CONF_PATH}/${FLATTENED_PATH}
        )
    endforeach()

    if (TOTAL_MOCKS GREATER 0)
        foreach(FILE_WO_MOCK ${FILES_WO_MOCK})
            file(READ ${FILE_WO_MOCK} FILE_SRC)
            math(EXPR MAX_MOCK_IDX "${TOTAL_MOCKS}-1")
            foreach(CURR_MOCK_IDX RANGE ${MAX_MOCK_IDX})
                list(GET MOCK_PATHS ${CURR_MOCK_IDX} CURR_MOCK)
                string(
                    REGEX REPLACE
                        "#include[^<\"]*[<\"]${CURR_MOCK}[>\"]." "${MOCK_BODY${CURR_MOCK_IDX}}"
                        FILE_SRC "${FILE_SRC}"
                )
            endforeach()
            file(WRITE ${FILE_WO_MOCK} "${FILE_SRC}")
        endforeach()
    endif()

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

function(conf_source FILE CONF_FILE MOCK_PATHS MOCK_BODIES)
    set(MOCK_SIG "CU_MOCK_IMPORT(")
    string(LENGTH ${MOCK_SIG} MOCK_SIG_LEN)
    set(NMOCK -1)

    list(APPEND MOCK_LIST)
    file(READ ${FILE} MOCKLESS)
    string(LENGTH "${MOCKLESS}" SRC_LEN)
    string(FIND "${MOCKLESS}" ${MOCK_SIG} MOCK_START)
    while (${MOCK_START} GREATER -1)
        string(SUBSTRING "${MOCKLESS}" 0 ${MOCK_START} MOCKLESS_HEAD)
        set(NESTED_PAREN 1)
        math(EXPR MOCK_START "${MOCK_START}+${MOCK_SIG_LEN}")
        set(CHR_IDX ${MOCK_START})
        while(CHR_IDX LESS ${SRC_LEN})
            string(SUBSTRING "${MOCKLESS}" ${CHR_IDX} 1 SRC_CHR)
            string(COMPARE EQUAL "${SRC_CHR}" "(" IS_OPEN)
            string(COMPARE EQUAL "${SRC_CHR}" ")" IS_CLOSE)
            if (${IS_OPEN})
                math(EXPR NESTED_PAREN "${NESTED_PAREN}+1")
            endif()
            if (${IS_CLOSE})
                math(EXPR NESTED_PAREN "${NESTED_PAREN}-1")
            endif()
            if (${NESTED_PAREN} EQUAL 0)
                math(EXPR MOCK_LEN "${CHR_IDX}-${MOCK_START}")
                math(EXPR MOCK_END "${CHR_IDX}+1")
                string(SUBSTRING "${MOCKLESS}" ${MOCK_START} ${MOCK_LEN} MOCK)
                math(EXPR NMOCK "${NMOCK}+1")
                set(MOCK${NMOCK} ${MOCK})
                string(LENGTH "${MOCKLESS_HEAD}" HEAD_LEN)
                math(EXPR SRC_LEN "${SRC_LEN}-${MOCK_LEN}")
                math(EXPR TAIL_LEN "${SRC_LEN}-${HEAD_LEN}")
                string(SUBSTRING "${MOCKLESS}" ${MOCK_END} ${TAIL_LEN}, MOCKLESS_TAIL)
                string(CONCAT MOCKLESS "${MOCKLESS_HEAD}" "${MOCKLESS_TAIL}")
                string(LENGTH "${MOCKLESS}" NEW_LEN)
                break()
            endif()
            if (${CHR_IDX} GREATER ${SRC_LEN})
                message(FATAL_ERROR "Failed parsing MOCK in ${FILE}")
            endif()
            math(EXPR CHR_IDX "${CHR_IDX}+1")
        endwhile()
        if (NOT ${NESTED_PAREN} EQUAL 0)
            message(FATAL_ERROR "Failed parsing MOCK in ${FILE}")
        endif()

        string(FIND "${MOCKLESS}" ${MOCK_SIG} MOCK_START)
    endwhile()

    if(${NMOCK} GREATER -1)
        foreach(MOCK_IDX RANGE ${NMOCK})
            string(REGEX MATCH "\"[^\"]+\"|[^,]+" "MOCK_INC${MOCK_IDX}" ${MOCK${MOCK_IDX}})
            string(LENGTH "${MOCK_INC${MOCK_IDX}}" NAME_LEN)
            string(LENGTH "${MOCK${MOCK_IDX}}" BODY_LEN)
            math(EXPR NAME_LEN "${NAME_LEN}+1")
            math(EXPR BODY_LEN "${BODY_LEN}-${NAME_LEN}")
            string(SUBSTRING "${MOCK${MOCK_IDX}}" ${NAME_LEN} ${BODY_LEN} MOCK${MOCK_IDX})
            list(
                APPEND
                MOCK_PATH
                ${MOCK_INC${MOCK_IDX}}
            )
            set(${MOCK_BODIES}${MOCK_IDX} ${MOCK${MOCK_IDX}} PARENT_SCOPE)
        endforeach()
        set(${MOCK_PATHS} ${MOCK_PATH} PARENT_SCOPE)
    endif()

    set(${CONF_FILE} "${MOCKLESS}" PARENT_SCOPE)

endfunction()
