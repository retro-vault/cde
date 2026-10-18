file(REMOVE_RECURSE ${WORK_DIR})
file(MAKE_DIRECTORY ${WORK_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E env LANG=C
    DTHELPSEARCHPATH=${PREFIX}/share/dt/appconfig/help/%L/%H
    ${PREFIX}/bin/dthelpgen -dir ${WORK_DIR} -generate
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Help index generation failed: ${result}\n${output}\n${error}")
endif()
file(READ ${WORK_DIR}/browser01.ht index)
foreach(volume Intromgr Calendar Filemgr Mailer Terminal Textedit)
    if(NOT index MATCHES "${volume}")
        message(FATAL_ERROR "Help index does not register ${volume}: ${output}\n${error}")
    endif()
endforeach()
