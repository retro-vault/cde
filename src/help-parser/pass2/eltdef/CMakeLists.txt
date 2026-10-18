file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/context.h
        ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/context.dat ${CMAKE_CURRENT_BINARY_DIR}/context.dat
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../htag2/delim.elt ${CMAKE_CURRENT_BINARY_DIR}/delim.dat
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_pass2_context> -DARGS=
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/context.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_pass2_context context.dat ../htag2/delim.elt
    VERBATIM)
add_custom_target(help_pass2_eltdef_context DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/context.h
    ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c)
add_executable(help_pass2_element_builder
    eltdef.c
    eltutil.c
    entity.c
    scan.c
)
add_dependencies(help_pass2_element_builder help_pass2_eltdef_context help_pass2_dtd)
target_link_libraries(help_pass2_element_builder PRIVATE help_pass2_util)
target_include_directories(help_pass2_element_builder PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../build ${CMAKE_CURRENT_SOURCE_DIR}/../util)
set(element_outputs
    ${CMAKE_CURRENT_BINARY_DIR}/efile.c
    ${CMAKE_CURRENT_BINARY_DIR}/entfile.c
    ${CMAKE_CURRENT_BINARY_DIR}/pfile.c
    ${CMAKE_CURRENT_BINARY_DIR}/sfile.c
    ${CMAKE_CURRENT_BINARY_DIR}/stfile.c
    ${CMAKE_CURRENT_BINARY_DIR}/tfile.c
    ${CMAKE_CURRENT_BINARY_DIR}/entity2.h
    ${CMAKE_CURRENT_BINARY_DIR}/globdec.h
    ${CMAKE_CURRENT_BINARY_DIR}/globdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/if.h
    ${CMAKE_CURRENT_BINARY_DIR}/pval.h
    ${CMAKE_CURRENT_BINARY_DIR}/signon.h
    ${CMAKE_CURRENT_BINARY_DIR}/signonx.h
)
add_custom_command(OUTPUT ${element_outputs}
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_pass2_element_builder>
        -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/../htag2/sdl.if
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/elements.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_pass2_element_builder ../htag2/sdl.if VERBATIM)
add_custom_target(help_pass2_elements DEPENDS ${element_outputs})
