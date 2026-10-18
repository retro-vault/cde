add_executable(dtksh
    ${PROJECT_SOURCE_DIR}/lib/ksh93/shell/sh/pmain.c
    ${PROJECT_SOURCE_DIR}/lib/ksh93/shell/sh/init.c
    widget.c dtkcvt.c dtkcmds.c XtCvtrs.c xmcvt.c xmcmds.c xmwidgets.c extra.c msgs.c)
target_include_directories(dtksh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/ksh93/shell/include ${PROJECT_SOURCE_DIR}/lib/ksh93/shell
    ${PROJECT_BINARY_DIR}/lib/ksh93/linux/shell
    ${PROJECT_SOURCE_DIR}/lib/DtPrint ${PROJECT_SOURCE_DIR}/lib/DtHelp)
target_compile_definitions(dtksh PRIVATE KSHELL BUILD_DTKSH _API_ast=20100309 ERROR_CONTEXT_T=Error_context_t)
target_link_libraries(dtksh PRIVATE ksh_shell ksh_build_options cde_build_options
    DtPrint DtHelp DtWidget DtSvc tt DtXinerama m ${CMAKE_DL_LIBS})
set_target_properties(dtksh PROPERTIES ENABLE_EXPORTS ON)
install(TARGETS dtksh RUNTIME DESTINATION bin)
install(PROGRAMS DtFuncs.sh DESTINATION lib/dtksh RENAME DtFuncs.dtsh)
install(FILES ${PROJECT_SOURCE_DIR}/lib/ksh93/LICENSE.md DESTINATION share/doc/cde/ksh93)
install(FILES Dtksh DESTINATION share/dt/app-defaults/C)
