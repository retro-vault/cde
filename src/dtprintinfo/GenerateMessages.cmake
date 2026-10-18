execute_process(COMMAND ${CMAKE_COMMAND} -E env "CPP=${CPP}" ${PROGRAM} ${SOURCE_DIR}/sym2num dtprintinfo ${SOURCE_DIR}/dtprintinfo.msg.src
    WORKING_DIRECTORY ${OUTPUT_DIR} OUTPUT_FILE ${OUTPUT_DIR}/dtprintinfo.msg COMMAND_ERROR_IS_FATAL ANY)
execute_process(COMMAND ${AWK} -f ${SOURCE_DIR}/msg.awk ${SOURCE_DIR}/dtprintinfo.msg.src
    OUTPUT_FILE ${OUTPUT_DIR}/dtprintinfo_cat.h COMMAND_ERROR_IS_FATAL ANY)
