execute_process(COMMAND "${GENERATOR}" ${GENERATOR_ARGS}
    OUTPUT_FILE "${OUTPUT}" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    file(REMOVE "${OUTPUT}")
    message(FATAL_ERROR "Generator failed with status ${result}")
endif()
