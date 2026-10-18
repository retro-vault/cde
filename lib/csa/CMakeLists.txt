find_package(BISON REQUIRED)
find_program(RPCGEN_EXECUTABLE rpcgen REQUIRED)
function(calendar_rpc output input mode prefix)
    set(suffix_args)
    if(ARGC GREATER 4)
        list(APPEND suffix_args -DSUFFIX=${ARGV4})
    endif()
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${output}
        COMMAND ${CMAKE_COMMAND} -DRPCGEN=${RPCGEN_EXECUTABLE}
            -DMODE=${mode} -DINPUT=${input} -DPREFIX=${prefix} ${suffix_args}
            -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${output}
            -P ${PROJECT_SOURCE_DIR}/cmake/GenerateCalendarRpc.cmake
        DEPENDS ${input} ${prefix} ${ARGV4} namechange1.sed namechange2.sed
        VERBATIM)
endfunction()
calendar_rpc(agent.h agent.x -h agent.wrapbegin agent.wrapend)
calendar_rpc(agent_xdr.c agent.x -c EUSinclude)
calendar_rpc(cm_clnt.c cm.x -l EUSinclude)
foreach(version 2 3 4)
    calendar_rpc(rtable${version}_clnt.c rtable${version}.x -l EUSinclude)
    calendar_rpc(rtable${version}_xdr.c rtable${version}.x -c EUSinclude)
endforeach()
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/reparser.c ${CMAKE_CURRENT_BINARY_DIR}/reparser.h
    COMMAND ${CMAKE_COMMAND} -DBISON=${BISON_EXECUTABLE}
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/reparser.y -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}
        -P ${PROJECT_SOURCE_DIR}/cmake/GenerateCalendarParser.cmake
    DEPENDS reparser.y VERBATIM)
add_library(csa SHARED
    ${CMAKE_CURRENT_BINARY_DIR}/agent.h ${CMAKE_CURRENT_BINARY_DIR}/reparser.h
    ${CMAKE_CURRENT_BINARY_DIR}/agent_xdr.c
    ${CMAKE_CURRENT_BINARY_DIR}/cm_clnt.c
    ${CMAKE_CURRENT_BINARY_DIR}/reparser.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable2_clnt.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable2_xdr.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable3_clnt.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable3_xdr.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable4_clnt.c
    ${CMAKE_CURRENT_BINARY_DIR}/rtable4_xdr.c
    agent.c
    api.c
    appt4.c
    attr.c
    calendar.c
    cmcbxdr.c
    cmsdata.c
    cmxdr.c
    connection.c
    convert2-4.c
    convert3-4.c
    convert4-2.c
    convert4-3.c
    convert4-5.c
    convert5-4.c
    debug.c
    entry.c
    free.c
    hash.c
    iso8601.c
    laccess.c
    lutil.c
    match.c
    nametbl.c
    refree.c
    rescan.c
    rpccalls.c
    table.c
    updateattrs.c
    xtclient.c
    ansi_c.c
)
target_compile_definitions(csa PRIVATE RFC_MIME LINE_COUNT V2 OW_I18N)
target_include_directories(csa PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include/csa)
target_link_libraries(csa PRIVATE cde_build_options PkgConfig::TIRPC)
set_target_properties(csa PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(csa PRIVATE -Wl,--no-undefined)
install(TARGETS csa LIBRARY DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/csa/csa.h DESTINATION include/csa)
