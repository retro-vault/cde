file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/context.h
        ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/context.dat ${CMAKE_CURRENT_BINARY_DIR}/context.dat
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../htag2/delim.bld ${CMAKE_CURRENT_BINARY_DIR}/delim.dat
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_pass2_context> -DARGS=sparse
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/context.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_pass2_context context.dat ../htag2/delim.bld
    VERBATIM)
add_custom_target(help_pass2_build_context DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/context.h
    ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c)
add_executable(help_pass2_dtd_builder
    build.c
    buildutl.c
    eltree.c
    except.c
    fsa.c
    out.c
    param.c
    scan.c
    sref.c
    tree.c
)
add_dependencies(help_pass2_dtd_builder help_pass2_build_context)
target_link_libraries(help_pass2_dtd_builder PRIVATE help_pass2_util)
target_include_directories(help_pass2_dtd_builder PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../util)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/arc.h ${CMAKE_CURRENT_BINARY_DIR}/dtd.h ${CMAKE_CURRENT_BINARY_DIR}/entity.h
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_pass2_dtd_builder> 
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/../htag2/sdl.dtd
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/dtd.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_pass2_dtd_builder ../htag2/sdl.dtd VERBATIM)
add_custom_target(help_pass2_dtd DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/arc.h
    ${CMAKE_CURRENT_BINARY_DIR}/dtd.h ${CMAKE_CURRENT_BINARY_DIR}/entity.h)
