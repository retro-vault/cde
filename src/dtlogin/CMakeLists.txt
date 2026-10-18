find_library(XDMCP_LIBRARY Xdmcp REQUIRED)
add_library(login_build_options INTERFACE)
target_link_libraries(login_build_options INTERFACE cde_build_options
    DtPrint DtHelp DtWidget DtSvc tt DtXinerama PAM::PAM ${XDMCP_LIBRARY} X11::Xau ${CRYPT_LIBRARY})
target_compile_definitions(login_build_options INTERFACE HAS_PAM_LIBRARY
    HASDES HASXDMAUTH UNIXCONN TCPCONN XDMCP BINDIR="/usr/bin"
    XDMDIR="${CDE_LOGFILES_TOP}" KORNSHELL=/bin/ksh)
add_library(login_resources OBJECT resource.c)
target_link_libraries(login_resources PRIVATE login_build_options)
target_compile_definitions(login_resources PRIVATE
    DEF_SESSION="${CDE_INSTALLATION_TOP}/bin/Xsession"
    DEF_SYSTEM_SHELL="/bin/sh" DEF_CHOOSER="${CDE_INSTALLATION_TOP}/bin/dtchooser"
    DEF_XDM_CONFIG="${CDE_DATA_TOP}/config/Xconfig"
    "DEF_SERVER_LINE=\":0 Local local /usr/bin/X :0\""
    XRDB_PROGRAM="/usr/bin/xrdb" DEF_USER_PATH="/usr/bin:/bin"
    DEF_SYSTEM_PATH="/usr/sbin:/usr/bin:/sbin:/bin"
    DEF_FAILSAFE_CLIENT="/usr/bin/xterm"
    DEF_AUTH_FILE="${CDE_LOGFILES_TOP}/auth-server" DEF_AUTH_DIR="${CDE_LOGFILES_TOP}"
    CPP_PROGRAM="/usr/bin/cpp"
    DEF_PM_SEARCH_PATH="${CDE_DATA_TOP}/appconfig/icons/%L/%B%M.pm:${CDE_DATA_TOP}/appconfig/icons/C/%B%M.pm"
    DEF_BM_SEARCH_PATH="${CDE_DATA_TOP}/appconfig/icons/%L/%B%M.bm:${CDE_DATA_TOP}/appconfig/icons/C/%B%M.bm")
add_executable(dtlogin
    access.c
    auth.c
    genauth.c
    daemon.c
    dm.c
    dpylist.c
    error.c
    file.c
    mitauth.c
    protodpy.c
    policy.c
    reset.c
    server.c
    session.c
    socket.c
    util.c
    verify.c
    sysauth.c
    fontpath.c
    qualify.c
    choose.c
    netaddr.c
    xdmcp.c
    xdmauth.c
)
target_link_libraries(dtlogin PRIVATE login_build_options login_resources)
install(TARGETS dtlogin RUNTIME DESTINATION bin)
add_executable(dtgreet
    vgcallback.c
    vglogo.c
    vgmain.c
    vgutil.c
    vglang.c
)
target_link_libraries(dtgreet PRIVATE login_build_options)
install(TARGETS dtgreet RUNTIME DESTINATION bin)
add_executable(dtchooser
    chooser.c
    dtchooser.c
    vglogo.c
    vgutil.c
    vgcallback.c
    vglang.c
)
target_link_libraries(dtchooser PRIVATE login_build_options)
install(TARGETS dtchooser RUNTIME DESTINATION bin)

configure_file(config/Xsession.in Xsession @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/Xsession DESTINATION bin)
configure_file(config/Xconfig.in Xconfig @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Xconfig DESTINATION share/dt/config)
configure_file(config/Xservers.in Xservers @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Xservers DESTINATION share/dt/config)
configure_file(config/Xaccess.in Xaccess @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Xaccess DESTINATION share/dt/config)
configure_file(config/Xfailsafe.in Xfailsafe @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/Xfailsafe DESTINATION share/dt/config)
configure_file(config/Xreset.in Xreset @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/Xreset DESTINATION share/dt/config)
configure_file(config/Xsetup.in Xsetup @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/Xsetup DESTINATION share/dt/config)
configure_file(config/Xstartup.in Xstartup @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/Xstartup DESTINATION share/dt/config)
configure_file(config/0060.dtsysenv.in 0060.dtsysenv @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/0060.dtsysenv DESTINATION share/dt/config/Xsession.d)
configure_file(config/dtlslocale.in dtlslocale @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dtlslocale DESTINATION bin)
configure_file(config/dtprofile.in sys.dtprofile @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/sys.dtprofile DESTINATION share/dt/config)
configure_file(config/Dtlogin.in Dtlogin.raw @ONLY)
cde_localized_resource(Dtlogin ${CMAKE_CURRENT_BINARY_DIR}/Dtlogin.raw
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/Dtlogin.tmsg share/dt/app-defaults/C)
configure_file(config/Xresources.in Xresources.raw @ONLY)
cde_localized_resource(Xresources ${CMAKE_CURRENT_BINARY_DIR}/Xresources.raw
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/Xresources.tmsg share/dt/config/C)
configure_file(config/dtlogin.in pam/dtlogin @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pam/dtlogin DESTINATION etc/pam.d)
configure_file(config/current.session.in current.session.raw @ONLY)
cde_localized_resource(0100.session ${CMAKE_CURRENT_BINARY_DIR}/current.session.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/_common.session.tmsg share/dt/config/C/Xresources.d)
configure_file(config/home.session.in home.session.raw @ONLY)
cde_localized_resource(0120.session ${CMAKE_CURRENT_BINARY_DIR}/home.session.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/_common.session.tmsg share/dt/config/C/Xresources.d)
configure_file(config/display.current.session.in display.current.session.raw @ONLY)
cde_localized_resource(0140.session ${CMAKE_CURRENT_BINARY_DIR}/display.current.session.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/_common.session.tmsg share/dt/config/C/Xresources.d)
configure_file(config/display.home.session.in display.home.session.raw @ONLY)
cde_localized_resource(0160.session ${CMAKE_CURRENT_BINARY_DIR}/display.home.session.raw ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/_common.session.tmsg share/dt/config/C/Xresources.d)
