add_executable(dticon
    dtIconShell.c
    event.c
    event.h
    fileIO.c
    fileIO.h
    fileIODialog.c
    globals.c
    graphics.c
    graphics.h
    help.c
    image.c
    image.h
    main.c
    newIconDialog.c
    process.c
    queryDialog.c
    stdErrDialog.c
    utils.c
    utils.h
    constants.h
    externals.h
    help.h
    main.h
)
target_link_libraries(dticon PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dticon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
target_compile_definitions(dticon PRIVATE __TOOLTALK)
install(TARGETS dticon RUNTIME DESTINATION bin)
