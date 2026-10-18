find_library(XSS_LIBRARY Xss REQUIRED)
add_executable(dtsession
    SmMain.c
    SmHelp.c
    SmGlobals.c
    SmCommun.c
    SmError.c
    SmProperty.c
    SmProtocol.c
    SmSave.c
    SmScreen.c
    SmRestore.c
    SmUI.c
    SmWindow.c
    SmLock.c
    SrvPalette.c
    SrvFile_io.c
    SmStrDefs.c
    SmConMgmt.c
    SmXSMP.c
    SmAuth.c
    SmWatch.c
    SmProp.c
    SmDB.c
    OWsync.h
    SmGlobals.h
    SmProperty.h
    SmScreen.h
    SmXSMP.h
    SmAuth.h
    Sm.h
    SmProp.h
    SmUI.h
    SrvFile_io.h
    SmCommun.h
    SmHelp.h
    SmProtocol.h
    SmWatch.h
    Srv.h
    SmConMgmt.h
    SmHftRing.h
    SmResource.h
    SmWindow.h
    SrvPalette.h
    SmDB.h
    SmLock.h
    SmRestore.h
    SmXdef.h
    SmError.h
    SmMigResources.h
    SmSave.h
    SmXrm.h
)
target_compile_definitions(dtsession PRIVATE dtsession HAS_PAM_LIBRARY USE_X11SSEXT)
target_link_libraries(dtsession PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama PAM::PAM X11::Xrandr ${XSS_LIBRARY} ${CRYPT_LIBRARY})
install(TARGETS dtsession RUNTIME DESTINATION bin)

configure_file(Dtsession.in Dtsession @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Dtsession DESTINATION share/dt/app-defaults/C)
configure_file(dtloadresources.in dtsession_res @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dtsession_res DESTINATION bin)
configure_file(config/dtsession.in pam/dtsession @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pam/dtsession DESTINATION etc/pam.d)
configure_file(sys.resources.in sys.resources.raw @ONLY)
cde_localized_resource(sys.resources ${CMAKE_CURRENT_BINARY_DIR}/sys.resources.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/sys.resources.tmsg share/dt/config/C)
configure_file(sys.font.in sys.font.raw @ONLY)
cde_localized_resource(sys.font ${CMAKE_CURRENT_BINARY_DIR}/sys.font.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/sys.font.tmsg share/dt/config/C)
configure_file(sys.session.in sys.session.raw @ONLY)
cde_localized_resource(sys.session ${CMAKE_CURRENT_BINARY_DIR}/sys.session.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/sys.session.tmsg share/dt/config/C)
