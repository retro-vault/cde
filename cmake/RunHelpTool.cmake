if(DEFINED INPUT)
    execute_process(COMMAND "${TOOL}" ${ARGS} INPUT_FILE "${INPUT}"
        WORKING_DIRECTORY "${WORK_DIR}" OUTPUT_FILE "${LOG}" RESULT_VARIABLE result)
else()
    execute_process(COMMAND "${TOOL}" ${ARGS}
        WORKING_DIRECTORY "${WORK_DIR}" OUTPUT_FILE "${LOG}" RESULT_VARIABLE result)
endif()
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Help generator failed (${result}); see ${LOG}")
endif()
