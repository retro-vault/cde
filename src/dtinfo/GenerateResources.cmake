execute_process(COMMAND ${CPP} -P -C -I${SOURCE_DIR}/resources ${SOURCE_DIR}/resources/Dtinfo.res
    OUTPUT_FILE ${OUTPUT_DIR}/Dtinfo.tree COMMAND_ERROR_IS_FATAL ANY)
execute_process(COMMAND ${PERL} ${SOURCE_DIR}/treeres.pl ${OUTPUT_DIR}/Dtinfo.tree
    OUTPUT_FILE ${OUTPUT_DIR}/Dtinfo COMMAND_ERROR_IS_FATAL ANY)
