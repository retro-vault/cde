add_subdirectory(dtcopy)
add_executable(dtfile
    ChangeDir.c
    ChangeDirP.c
    Command.c
    Common.c
    Desktop.c
    Directory.c
    Encaps.c
    File.c
    FileDialog.c
    FileManip.c
    FileMgr.c
    FileOp.c
    Filter.c
    FilterP.c
    Find.c
    FindP.c
    Help.c
    HelpCB.c
    HelpP.c
    IconWindow.c
    IconicPath.c
    Main.c
    Menu.c
    MkDir.c
    ModAttr.c
    ModAttrP.c
    MultiView.c
    OverWrite.c
    Prefs.c
    PrefsP.c
    SharedMsgs.c
    SharedProcs.c
    ToolTalk.c
    Trash.c
    Utils.c
    fsDialog.c
)
target_link_libraries(dtfile PRIVATE dtfile_copy_common cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama X11::Xrandr)
target_include_directories(dtfile PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dtcopy)
target_compile_definitions(dtfile PRIVATE SHAPE _ILS_MACROS SUN_PERF FILE_MAP_OPTIMIZE)
install(TARGETS dtfile RUNTIME DESTINATION bin)
cde_resource(dtfile.config.raw dtfile.config.cpp share/dt/config/C NO_INSTALL)
cde_localized_resource(dtfile.config ${CMAKE_CURRENT_BINARY_DIR}/dtfile.config.raw
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/dtfile.config.tmsg share/dt/config/C)
cde_resource(dtfile_error dtfile_error.cpp bin EXECUTABLE)
cde_resource(dterror.ds dterror.src bin EXECUTABLE)
