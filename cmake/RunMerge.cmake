get_filename_component(output_dir "${OUTPUT}" DIRECTORY)
file(MAKE_DIRECTORY "${output_dir}")
set(default_messages)
if(DEFAULT_MESSAGES)
    list(APPEND default_messages -dfile "${DEFAULT_MESSAGES}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8 "${GENERATOR}" -lang C.UTF-8 ${default_messages} "${MESSAGES}"
    INPUT_FILE "${INPUT}" OUTPUT_FILE "${OUTPUT}"
    WORKING_DIRECTORY "${output_dir}" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    file(REMOVE "${OUTPUT}")
    message(FATAL_ERROR "Resource message merge failed for ${INPUT}: ${result}")
endif()
