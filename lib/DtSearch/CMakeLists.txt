find_package(BISON REQUIRED)
bison_target(search_parser boolyac.y ${CMAKE_CURRENT_BINARY_DIR}/boolyac.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/boolyac.h)
add_subdirectory(raima)
add_library(DtSearch SHARED ${BISON_search_parser_OUTPUTS}
    apndext.c
    ausdopen.c
    ausexit.c
    bmstrstr.c
    boolpars.c
    boolsrch.c
    cuslang.c
    dbchange.c
    dberr.c
    delspace.c
    dtoe.c
    dtoeinit.c
    dtsrapi.c
    dtsrdbrec.c
    dtsrjoint.c
    dtsrswab.c
    dtsrutil.c
    dtsrve.c
    endslash.c
    fileman.c
    globals.c
    hdecode.c
    hencode.c
    hilite.c
    iscompat.c
    isduprec.c
    jpn.c
    lang.c
    langmap.c
    msgs.c
    msgutil.c
    objdate.c
    ocf.c
    opendblk.c
    ophuf.c
    readchar.c
    strupr.c
    userint.c
    vedelete.c
    vestatis.c
    vstfunct.c
)
target_include_directories(DtSearch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/raima ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(DtSearch PRIVATE cde_build_options dtsr_raima DtSvc m)
set_target_properties(DtSearch PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(DtSearch PRIVATE -Wl,--no-undefined)
install(TARGETS DtSearch LIBRARY DESTINATION lib)
