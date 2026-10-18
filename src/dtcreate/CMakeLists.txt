add_executable(dtcreate
    main.c
    AddFiletype.c
    Confirmed.c
    CreateActionAppShell.c
    FileCharacteristics.c
    OpenFile.c
    UxXt.c
    ca_aux.c
    cmncbs.c
    cmnutils.c
    cmnrtns.c
    ErrorDialog.c
    fileio.c
    af_aux.c
    icon_selection_dialog.c
    parser.c
    AddFiletype.h
    Confirmed.h
    icon_selection_dialog.h
    af_aux.h
    CreateActionAppShell.h
    OpenFile.h
    ca_aux.h
    dtcreate.h
    parser.h
    cmncbs.h
    ErrorDialog.h
    UxXt.h
    cmnrtns.h
    FileCharacteristics.h
    cmnutils.h
    fileio.h
)
target_link_libraries(dtcreate PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtcreate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtcreate RUNTIME DESTINATION bin)
