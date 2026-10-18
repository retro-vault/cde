find_package(BISON REQUIRED)
bison_target(calendar_getdate getdate.y ${CMAKE_CURRENT_BINARY_DIR}/getdate.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/getdate_tokens.h)
add_library(calendar_build_options INTERFACE)
target_include_directories(calendar_build_options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/csa ${PROJECT_BINARY_DIR}/lib/csa ${PROJECT_SOURCE_DIR}/include/csa)
target_compile_definitions(calendar_build_options INTERFACE RFC_MIME LINE_COUNT V2 OW_I18N OPT_TIRPC)
target_link_libraries(calendar_build_options INTERFACE cde_build_options csa DtSvc tt)
add_library(DtCmP STATIC ${BISON_calendar_getdate_OUTPUTS}
    cm_tty.c
    cmfns.c
    dtfns.c
    props.c
    resource.c
    timeops.c
    util.c
)
target_link_libraries(DtCmP PUBLIC calendar_build_options)
