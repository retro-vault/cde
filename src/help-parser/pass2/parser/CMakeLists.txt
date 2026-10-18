file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/context.h
        ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/context.dat ${CMAKE_CURRENT_BINARY_DIR}/context.dat
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../htag2/delim.par ${CMAKE_CURRENT_BINARY_DIR}/delim.dat
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_pass2_context> -DARGS=
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/context.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_pass2_context context.dat ../htag2/delim.par
    VERBATIM)
add_custom_target(help_pass2_parser_context DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/context.h
    ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c)
add_executable(dthelp_htag2
    parser.c
    actutil.c
    closent.c
    code.c
    cyclent.c
    dcurelt.c
    end.c
    entity.c
    error.c
    getsign.c
    input.c
    level.c
    lookent.c
    minim.c
    optstrg.c
    param.c
    parent.c
    parutil.c
    pi.c
    scan.c
    setpar.c
    start.c
    string.c
    struct.c
    text.c
)
add_dependencies(dthelp_htag2 help_pass2_parser_context help_pass2_elements)
target_include_directories(dthelp_htag2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../eltdef ${CMAKE_CURRENT_BINARY_DIR}/../build ${CMAKE_CURRENT_SOURCE_DIR}/../htag2 ${CMAKE_CURRENT_SOURCE_DIR}/../util)
target_link_libraries(dthelp_htag2 PRIVATE help_pass2_application help_pass2_util DtSvc tt)
set_target_properties(dthelp_htag2 PROPERTIES INSTALL_RPATH "$ORIGIN/../../lib")
install(TARGETS dthelp_htag2 RUNTIME DESTINATION libexec/cde)
target_include_directories(dthelp_htag2 BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../htag2 ${CMAKE_CURRENT_SOURCE_DIR}/../../include/parser)
