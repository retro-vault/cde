execute_process(COMMAND ${GENERATOR} tocgen -L en_US.UTF-8 -T ${WORK_DIR}/tmp
    -f ${WORK_DIR}/TOC.sgm ${SOURCE} WORKING_DIRECTORY ${WORK_DIR}
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
if(result EQUAL 0 OR NOT error MATCHES "UndefinedTestEntity")
    message(FATAL_ERROR "Invalid SGML was accepted or the parser did not run: ${result}\n${output}\n${error}")
endif()
