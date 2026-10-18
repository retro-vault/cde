add_executable(dtstyle
    Main.c
    MainWin.c
    Font.c
    Audio.c
    Startup.c
    Mouse.c
    SaveRestore.c
    Backdrop.c
    Screen.c
    Keyboard.c
    ColorMain.c
    ColorPalette.c
    ColorFile.c
    ColorEdit.c
    Resource.c
    Protocol.c
    Dtwm.c
    Help.c
    HelpCB.c
    I18nMain.c
    I18nEnv.c
    I18nUtil.c
    Audio.h
    ColorMain.h
    Help.h
    Keyboard.h
    OWsync.h
    Screen.h
    Backdrop.h
    ColorPalette.h
    I18nEnv.h
    Main.h
    Protocol.h
    Startup.h
    ColorEdit.h
    Dtwm.h
    I18nMain.h
    MainWin.h
    Resource.h
    ColorFile.h
    Font.h
    I18nUtil.h
    Mouse.h
    SaveRestore.h
)
target_link_libraries(dtstyle PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtstyle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtstyle RUNTIME DESTINATION bin)
cde_resource(Dtstyle Dtstyle.src share/dt/app-defaults/C NO_INSTALL)
cde_resource(Backdrops Backdrops.src share/dt/backdrops NO_INSTALL)
cde_resource(Palettes Palettes.src share/dt/palettes NO_INSTALL)

cde_localized_resource(backdrops/desc.C ${CMAKE_CURRENT_BINARY_DIR}/Backdrops
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/Backdrops.tmsg share/dt/backdrops)
cde_localized_resource(palettes/desc.C ${CMAKE_CURRENT_BINARY_DIR}/Palettes
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/Palettes.tmsg share/dt/palettes)
