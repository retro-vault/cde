file(MAKE_DIRECTORY ${WORK_DIR}/home)
foreach(pass RANGE 1 2)
    execute_process(COMMAND ${CMAKE_COMMAND} -E env HOME=${WORK_DIR}/home
        DTUSERSESSION=roundtrip LANG=C DTAPPSEARCHPATH=${DATA_DIR}/appconfig/appmanager/C
        ${PROGRAM} WORKING_DIRECTORY ${WORK_DIR} RESULT_VARIABLE result
        OUTPUT_VARIABLE output ERROR_VARIABLE error)
    if(NOT result EQUAL 0 OR NOT error STREQUAL "")
        message(FATAL_ERROR "Action gathering failed: ${result}\n${output}\n${error}")
    endif()
    if(NOT EXISTS ${WORK_DIR}/home/.dt/appmanager-sessions/roundtrip/Desktop_Apps/Dtpad)
        message(FATAL_ERROR "Gathered application group is missing the editor action")
    endif()
endforeach()
