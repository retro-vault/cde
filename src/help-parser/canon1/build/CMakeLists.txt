file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/context.h
        ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/context.dat ${CMAKE_CURRENT_BINARY_DIR}/context.dat
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../helptag/delim.bld ${CMAKE_CURRENT_BINARY_DIR}/delim.dat
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_canon1_context> -DARGS=sparse
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/context.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_canon1_context context.dat ../helptag/delim.bld
    VERBATIM)
add_custom_target(help_canon1_build_context DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/context.h
    ${CMAKE_CURRENT_BINARY_DIR}/delim.h ${CMAKE_CURRENT_BINARY_DIR}/case.c)
add_executable(help_canon1_dtd_builder
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
add_dependencies(help_canon1_dtd_builder help_canon1_build_context)
target_link_libraries(help_canon1_dtd_builder PRIVATE help_canon1_util)
target_include_directories(help_canon1_dtd_builder PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../util)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/arc.h ${CMAKE_CURRENT_BINARY_DIR}/dtd.h ${CMAKE_CURRENT_BINARY_DIR}/entity.h
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:help_canon1_dtd_builder> -DARGS=-m
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/../helptag/hptag.dtd
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -DLOG=${CMAKE_CURRENT_BINARY_DIR}/dtd.log
        -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS help_canon1_dtd_builder ../helptag/hptag.dtd VERBATIM)
add_custom_target(help_canon1_dtd DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/arc.h
    ${CMAKE_CURRENT_BINARY_DIR}/dtd.h ${CMAKE_CURRENT_BINARY_DIR}/entity.h)
