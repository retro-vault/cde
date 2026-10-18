execute_process(COMMAND "${BISON}" -d --output=${OUTPUT_DIR}/reparser.raw.c
    --defines=${OUTPUT_DIR}/reparser.raw.h "${INPUT}"
    RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Calendar grammar generation failed")
endif()
foreach(extension c h)
    file(READ "${OUTPUT_DIR}/reparser.raw.${extension}" generated)
    string(REPLACE "yyparse" "_DtCm_rule_parser" generated "${generated}")
    string(REPLACE "yy" "_DtCm_yy" generated "${generated}")
    string(REPLACE "reparser.raw.h" "reparser.h" generated "${generated}")
    file(WRITE "${OUTPUT_DIR}/reparser.${extension}" "${generated}")
endforeach()
