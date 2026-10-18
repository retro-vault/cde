file(REMOVE ${WORK_DIR}/roundtrip.sdl)
configure_file(${SOURCE} ${WORK_DIR}/roundtrip.htg COPYONLY)
execute_process(COMMAND sh ${WRAPPER} -verbose roundtrip.htg
    WORKING_DIRECTORY ${WORK_DIR} RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
if(NOT result EQUAL 0 OR NOT EXISTS ${WORK_DIR}/roundtrip.sdl)
    message(FATAL_ERROR "Help compiler failed: ${result}\n${output}\n${error}")
endif()
file(SIZE ${WORK_DIR}/roundtrip.sdl size)
if(size LESS 512)
    message(FATAL_ERROR "Help compiler produced an incomplete volume (${size} bytes)")
endif()
# The second pass must also be able to read its compressed output.
execute_process(COMMAND sh ${WRAPPER} -verbose -decompress roundtrip.sdl
    WORKING_DIRECTORY ${WORK_DIR} COMMAND_ERROR_IS_FATAL ANY)
file(READ ${WORK_DIR}/roundtrip.sdl content)
if(NOT content MATCHES "Help compiler test" OR NOT content MATCHES "index entry")
    message(FATAL_ERROR "Compiled help lost topic or index text")
endif()
