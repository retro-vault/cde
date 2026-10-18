add_executable(dtwm
    WmCDInfo.c
    WmCDecor.c
    WmCEvent.c
    WmCPlace.c
    WmColormap.c
    WmError.c
    WmEvent.c
    WmEwmh.c
    WmFeedback.c
    WmFunction.c
    WmGraphics.c
    WmIDecor.c
    WmIPlace.c
    WmIconBox.c
    WmImage.c
    WmInitWs.c
    WmKeyFocus.c
    WmMain.c
    WmManage.c
    WmMenu.c
    WmProperty.c
    WmProtocol.c
    WmResCvt.c
    WmResParse.c
    WmResource.c
    WmSignal.c
    WmWinConf.c
    WmWinInfo.c
    WmWinList.c
    WmWinState.c
    WmMultiHead.c
    WmScreenChanges.c
    Button.c
    Callback.c
    Clock.c
    DataBaseLoad.c
    PanelS.c
    Parse.c
    PopupMenu.c
    Session.c
    UI.c
    WmBackdrop.c
    WmFP.c
    WmHelp.c
    WmIPC.c
    WmInstantTitle.c
    WmOL.c
    WmParse.c
    WmParseP.c
    WmPresence.c
    WmWrkspace.c
    WmXSMP.c
)
target_link_libraries(dtwm PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama X11::Xrandr m)
target_include_directories(dtwm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
target_compile_definitions(dtwm PRIVATE LARGECURSORS R2_COMPAT OPAQUE SHAPE UNMAP_ON_RESTART BATCH_DRAG_REQUESTS USE_XINERAMA)
install(TARGETS dtwm RUNTIME DESTINATION bin)
cde_resource(sys.dtwmrc sys.dtwmrc.src share/dt/config/C NO_INSTALL)
cde_resource(Dtwm.defs Dtwm.defs.src share/dt/config/C NO_INSTALL)
add_executable(dtfplist Print.c Parse.c DataBaseLoad.c WmParse.c Session.c)
target_link_libraries(dtfplist PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtfplist RUNTIME DESTINATION bin)
