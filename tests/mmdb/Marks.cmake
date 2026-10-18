file(REMOVE_RECURSE ${WORK_DIR})
file(MAKE_DIRECTORY ${WORK_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E env
    DTINFO_MARKSPECPATH=${PREFIX}/share/dt/infolib/etc
    ${PROGRAM} ${WORK_DIR}/marks/default RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Marks creation/reopen test failed: ${result}")
endif()
