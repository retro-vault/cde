find_package(BISON REQUIRED)
bison_target(calendar_server_parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h COMPILE_FLAGS "-p yyy")
add_executable(rpc.cmsd ${BISON_calendar_server_parser_OUTPUTS}
    access.c
    callback.c
    cmscalendar.c
    cmsconvert.c
    cmsentry.c
    cmsmatch.c
    delete.c
    garbage.c
    insert.c
    lexit.c
    list.c
    log.c
    lookup.c
    reclotick.c
    recount.c
    relasttick.c
    reminder.c
    renexttick.c
    repeat.c
    reprevtick.c
    rerule.c
    reutil.c
    tree.c
    utility.c
    v4ops.c
    v5ops.c
    cmsfunc.c
    programtable.c
    rtable2.c
    rtable3.c
    rtable4.c
    svcmain.c
    update.c
    access.h
    cmsentry.h
    insert.h
    tree.h
    callback.h
    cmsmatch.h
    lexer.h
    reminder.h
    update.h
    cmsattr.h
    data.h
    list.h
    repeat.h
    utility.h
    cmscalendar.h
    delete.h
    log.h
    reutil.h
    v4ops.h
    cmsconvert.h
    garbage.h
    lookup.h
    rpcextras.h
    v5ops.h
)
target_include_directories(rpc.cmsd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(rpc.cmsd PRIVATE calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
set_target_properties(rpc.cmsd PROPERTIES INSTALL_RPATH "$ORIGIN/../../lib")
install(TARGETS rpc.cmsd RUNTIME DESTINATION libexec/cde)
target_compile_definitions(rpc.cmsd PRIVATE CDE_CALENDAR_DIR="${CDE_CALENDAR_DIR}")
