execute_process(COMMAND "${RPCGEN}" "${MODE}" "${INPUT}"
    WORKING_DIRECTORY "${SOURCE_DIR}"
    OUTPUT_FILE "${OUTPUT}.raw" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "rpcgen failed for ${INPUT}")
endif()
execute_process(COMMAND sed -f "${SOURCE_DIR}/namechange1.sed"
    -f "${SOURCE_DIR}/namechange2.sed"
    INPUT_FILE "${OUTPUT}.raw" OUTPUT_VARIABLE generated RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "RPC symbol rewriting failed for ${INPUT}")
endif()
file(READ "${SOURCE_DIR}/${PREFIX}" prefix)
if(DEFINED SUFFIX)
    file(READ "${SOURCE_DIR}/${SUFFIX}" suffix)
endif()
file(WRITE "${OUTPUT}" "${prefix}${generated}${suffix}")
