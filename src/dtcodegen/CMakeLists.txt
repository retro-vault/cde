add_executable(dtcodegen
    abmf.c
    args.c
    cdefs.c
    connect.c
    create_decls.c
    dtb_utils.c
    generate_code.c
    instances.c
    lib_func_strings.c
    make_file.c
    merge_c.c
    motifdefs.c
    msg_cvt.c
    msg_file.c
    obj_names.c
    parse_c.c
    proj_c_file.c
    proj_header_file.c
    resource_file.c
    stubs_c_file.c
    ui_c_file.c
    ui_header_file.c
    utils.c
    utils_c_file.c
    utils_header_file.c
    write_c.c
    write_code.c
)
target_link_libraries(dtcodegen PRIVATE ABil ABobjXm ABobj AButil cde_build_options
    DtTerm DtSvc tt DtHelp DtXinerama DtWidget)
find_program(GENCAT_EXECUTABLE gencat REQUIRED)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dtcodegen.cat
    COMMAND ${GENCAT_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/dtcodegen.cat
        ${CMAKE_CURRENT_SOURCE_DIR}/dtcodegen.msg
        ${PROJECT_SOURCE_DIR}/lib/AButil/libAButil.msg
        ${PROJECT_SOURCE_DIR}/lib/ABobjXm/libABobjXm.msg
        ${PROJECT_SOURCE_DIR}/lib/ABil/libABil.msg
    DEPENDS dtcodegen.msg ${PROJECT_SOURCE_DIR}/lib/AButil/libAButil.msg
        ${PROJECT_SOURCE_DIR}/lib/ABobjXm/libABobjXm.msg ${PROJECT_SOURCE_DIR}/lib/ABil/libABil.msg
    VERBATIM)
add_custom_target(builder_catalog ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/dtcodegen.cat)
install(TARGETS dtcodegen RUNTIME DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dtcodegen.cat DESTINATION share/dt/lib/nls/msg/C)
