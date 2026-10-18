add_executable(dtpdm
    JobBox.c
    Main.c
    MainWindow.c
    PdmMsgs.c
    PdmOid.c
    PdmXp.c
    PrinterBox.c
    JobBox.h
    PdmMsgs.h
    PdmOid.h
    PdmXp.h
    MainWindow.h
    PdmOidDefs.h
    PdmOidStrs.h
    PrinterBox.h
)
target_link_libraries(dtpdm PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtpdm RUNTIME DESTINATION bin)
