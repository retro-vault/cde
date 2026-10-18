add_executable(dtpad
    dtpad.c
    editCB.c
    fileCB.c
    fileDlg.c
    fileIo.c
    formatCB.c
    helpCB.c
    helpDlg.c
    main.c
    optionsCB.c
    printJob.c
    printOutput.c
    printSetup.c
    session.c
    ttMsgSupport.c
    ttSaveSupport.c
)
target_link_libraries(dtpad PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtpad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
target_compile_definitions(dtpad PRIVATE DT_LITE WORDWRAP)
install(TARGETS dtpad RUNTIME DESTINATION bin)
