execute_process(COMMAND "${PREPROCESSOR}" -P "-DXCOMM=#" -DFALLBACK_RESOURCES
    "${SOURCE_DIR}/Dtterm.ad.src" OUTPUT_FILE "${OUTPUT_DIR}/fallback.src"
    RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Terminal resource preprocessing failed")
endif()
execute_process(COMMAND sh "${SOURCE_DIR}/mkfallbk"
    INPUT_FILE "${OUTPUT_DIR}/fallback.src"
    OUTPUT_FILE "${OUTPUT_DIR}/DtTermFallBackResources.c" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Terminal fallback generation failed")
endif()
set(ENV{CPP} "${PREPROCESSOR}")
execute_process(COMMAND sh "${SOURCE_DIR}/terminfoCreate"
    INPUT_FILE "${SOURCE_DIR}/terminfoChecklist"
    OUTPUT_FILE "${OUTPUT_DIR}/dtterm.ti" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Terminal terminfo generation failed")
endif()
