set(KORNSHELL /bin/ksh)
set(DTKORNSHELL ${CDE_INSTALLATION_TOP}/bin/dtksh)
install(DIRECTORY backdrops/ DESTINATION share/dt/backdrops)
install(DIRECTORY palettes/ DESTINATION share/dt/palettes)
install(DIRECTORY icons/ DESTINATION share/dt/appconfig/icons/C)
cde_localized_resource(app-defaults/Dtpad ${PROJECT_SOURCE_DIR}/src/dtpad/Dtpad ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtpad.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtcalc ${PROJECT_SOURCE_DIR}/src/dtcalc/Dtcalc ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtcalc.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtfile ${PROJECT_SOURCE_DIR}/src/dtfile/Dtfile ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtfile.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dticon ${PROJECT_SOURCE_DIR}/src/dticon/Dticon ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dticon.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtcreate ${PROJECT_SOURCE_DIR}/src/dtcreate/Dtcreate ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtcreate.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtmail ${PROJECT_SOURCE_DIR}/src/dtmail/Dtmail ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtmail.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtimsstart ${PROJECT_SOURCE_DIR}/src/dtimsstart/Dtimsstart ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtimsstart.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dt ${PROJECT_SOURCE_DIR}/lib/DtSvc/DtUtil2/Dt.ad ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dt.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dthello ${PROJECT_BINARY_DIR}/src/dthello/Dthello ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dthello.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtstyle ${PROJECT_BINARY_DIR}/src/dtstyle/Dtstyle ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtstyle.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtscreen ${PROJECT_BINARY_DIR}/src/dtscreen/Dtscreen ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtscreen.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtterm ${PROJECT_BINARY_DIR}/src/dtterm/Dtterm ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtterm.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dtwm ${PROJECT_BINARY_DIR}/src/dtwm/Dtwm.defs ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtwm.tmsg share/dt/app-defaults/C)
configure_file(types/IconBrowse.dt.in raw-actions/IconBrowse.dt @ONLY)
cde_localized_resource(actions/IconBrowse.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/IconBrowse.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/autoStart.dt.in raw-actions/autoStart.dt @ONLY)
cde_localized_resource(actions/autoStart.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/autoStart.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/datatypes.dt.in raw-actions/datatypes.dt @ONLY)
cde_localized_resource(actions/datatypes.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/datatypes.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/develop.dt.in raw-actions/develop.dt @ONLY)
cde_localized_resource(actions/develop.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/develop.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dt.dt.in raw-actions/dt.dt @ONLY)
cde_localized_resource(actions/dt.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dt.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtappman.dt.in raw-actions/dtappman.dt @ONLY)
cde_localized_resource(actions/dtappman.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtappman.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtcm.dt.in raw-actions/dtcm.dt @ONLY)
cde_localized_resource(actions/dtcm.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtcm.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtfile.dt.in raw-actions/dtfile.dt @ONLY)
cde_localized_resource(actions/dtfile.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtfile.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dthelp.dt.in raw-actions/dthelp.dt @ONLY)
cde_localized_resource(actions/dthelp.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dthelp.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dthelpprint.dt.in raw-actions/dthelpprint.dt @ONLY)
cde_localized_resource(actions/dthelpprint.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dthelpprint.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dthelptag.dt.in raw-actions/dthelptag.dt @ONLY)
cde_localized_resource(actions/dthelptag.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dthelptag.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtims.dt.in raw-actions/dtims.dt @ONLY)
cde_localized_resource(actions/dtims.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtims.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtinfo.dt.in raw-actions/dtinfo.dt @ONLY)
cde_localized_resource(actions/dtinfo.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtinfo.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtmail.dt.in raw-actions/dtmail.dt @ONLY)
cde_localized_resource(actions/dtmail.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtmail.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtpad.dt.in raw-actions/dtpad.dt @ONLY)
cde_localized_resource(actions/dtpad.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtpad.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtscreen.dt.in raw-actions/dtscreen.dt @ONLY)
cde_localized_resource(actions/dtscreen.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtscreen.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/dtwm.fp.in raw-actions/dtwm.fp @ONLY)
cde_localized_resource(actions/dtwm.fp ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/dtwm.fp ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/miscActions.dt.in raw-actions/miscActions.dt @ONLY)
cde_localized_resource(actions/miscActions.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/miscActions.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/miscImages.dt.in raw-actions/miscImages.dt @ONLY)
cde_localized_resource(actions/miscImages.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/miscImages.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/print.dt.in raw-actions/print.dt @ONLY)
cde_localized_resource(actions/print.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/print.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/user-prefs.dt.in raw-actions/user-prefs.dt @ONLY)
cde_localized_resource(actions/user-prefs.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/user-prefs.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/uxstd.dt.in raw-actions/uxstd.dt @ONLY)
cde_localized_resource(actions/uxstd.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/uxstd.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
configure_file(types/xclients.dt.in raw-actions/xclients.dt @ONLY)
cde_localized_resource(actions/xclients.dt ${CMAKE_CURRENT_BINARY_DIR}/raw-actions/xclients.dt ${CMAKE_CURRENT_SOURCE_DIR}/messages/actions.tmsg share/dt/appconfig/types/C)
set(ttype_inputs dtfile dticon dtpad dtcm dtmail dtdbcache dtterm dtinfo dtinfo_start)
set(combined_types "")
set(type_sources)
foreach(type IN LISTS ttype_inputs)
    string(APPEND combined_types "#include \"${CMAKE_CURRENT_SOURCE_DIR}/tttypes/${type}.ptype\"\n")
    list(APPEND type_sources ${CMAKE_CURRENT_SOURCE_DIR}/tttypes/${type}.ptype)
endforeach()
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/types.ptype "${combined_types}")
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/types.xdr
    COMMAND tt_type_comp -I${PROJECT_BINARY_DIR}/include -x
        -o ${CMAKE_CURRENT_BINARY_DIR}/types.xdr ${CMAKE_CURRENT_BINARY_DIR}/types.ptype
    DEPENDS tt_type_comp ${type_sources} ${PROJECT_BINARY_DIR}/include/cde_config.h
    VERBATIM)
add_custom_target(desktop_tooltalk_types ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/types.xdr)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/types.xdr DESTINATION share/dt/appconfig/tttypes)
install(FILES ${PROJECT_SOURCE_DIR}/lib/DtHelp/CDE.lcx DESTINATION share/dt/config/svc)
install(FILES ${PROJECT_SOURCE_DIR}/lib/DtHelp/Linux.lcx DESTINATION share/dt/config/svc)
cde_localized_resource(config/C/sys.dtwmrc ${PROJECT_BINARY_DIR}/src/dtwm/sys.dtwmrc ${CMAKE_CURRENT_SOURCE_DIR}/messages/sys.dtwmrc.tmsg share/dt/config/C)

configure_file(action.in action @ONLY)
set(desktop_actions
    Desktop_Apps/Dtmanpageview
    Desktop_Apps/Dthelpview
    Desktop_Apps/DtPrintManager
    Desktop_Apps/Dtcreate
    Desktop_Apps/Dtstyle
    Desktop_Apps/Dtmail
    Desktop_Apps/Dttrash
    Desktop_Apps/DtLoadInfoLib
    Desktop_Apps/Dtterm
    Desktop_Apps/Dtappbuild
    Desktop_Apps/Dtpad
    Desktop_Apps/Dticon
    Desktop_Apps/Dtcm
    Desktop_Apps/Dtfile
    Desktop_Apps/Dtcalc
    Desktop_Tools/Rm
    Desktop_Tools/DttermRlogin
    Desktop_Tools/Env
    Desktop_Tools/Uncompress
    Desktop_Tools/Xclipboard
    Desktop_Tools/Xwd
    Desktop_Tools/XtermRlogin
    Desktop_Tools/Xload
    Desktop_Tools/DttermConsole
    Desktop_Tools/Compress
    Desktop_Tools/Tar
    Desktop_Tools/DuSort
    Desktop_Tools/TarList
    Desktop_Tools/DttermErrorlog
    Desktop_Tools/Xprop
    Desktop_Tools/XclockDig
    Desktop_Tools/Spell
    Desktop_Tools/Xterm
    Desktop_Tools/Diff
    Desktop_Tools/Xdpyinfo
    Desktop_Tools/Xrefresh
    Desktop_Tools/Grep
    Desktop_Tools/ReloadApps
    Desktop_Tools/Xlsfonts
    Desktop_Tools/RestorePanel
    Desktop_Tools/Df
    Desktop_Tools/Xwud
    Desktop_Tools/SaveSession
    Desktop_Tools/Make
    Desktop_Tools/ExecuteCmd
    Desktop_Tools/CodeGen
    Desktop_Tools/ReloadResources
    Desktop_Tools/TarUnpack
    Desktop_Tools/Dttypes
    Desktop_Tools/Vi
    Desktop_Tools/Wc
    Desktop_Tools/Xfd
    Desktop_Tools/File
    Desktop_Tools/ReloadActions
    Desktop_Tools/DtImsMode
    Desktop_Tools/Xwininfo
    Desktop_Tools/Nm
    Desktop_Tools/Bitmap
    Desktop_Tools/DttermDtspcd
    Desktop_Tools/DtwmrcEdit
    Desktop_Tools/XtermDtspcd
    Information/OpenDtIntro
)
foreach(action IN LISTS desktop_actions)
    get_filename_component(group ${action} DIRECTORY)
    get_filename_component(name ${action} NAME)
    install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/action
        DESTINATION share/dt/appconfig/appmanager/C/${group} RENAME ${name})
endforeach()
install(CODE "file(CREATE_LINK C \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/dt/appconfig/appmanager/en_US.UTF-8\" SYMBOLIC)")

cde_message_catalog(DtHelp ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/DtHelp.msg)
cde_message_catalog(DtMail ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/DtMail.msg)
cde_message_catalog(DtPrint ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/DtPrint.msg)
cde_message_catalog(DtWidget ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/DtWidget.msg)
cde_message_catalog(MotifApp ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/MotifApp.msg)
cde_message_catalog(SUNW_TOOLTALK ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/SUNW_TOOLTALK.msg)
cde_message_catalog(dt ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dt.msg)
cde_message_catalog(dtact ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtact.msg)
cde_message_catalog(dtcalc ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtcalc.msg)
cde_message_catalog(dtcm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtcm.msg)
cde_message_catalog(dtconfig ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtconfig.msg)
cde_message_catalog(dtcopy ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtcopy.msg)
cde_message_catalog(dtcreate ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtcreate.msg)
cde_message_catalog(dtfile ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtfile.msg)
cde_message_catalog(dthello ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dthello.msg)
cde_message_catalog(dthelpgen ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dthelpgen.msg)
cde_message_catalog(dthelpprint ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dthelpprint.msg)
cde_message_catalog(dticon ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dticon.msg)
cde_message_catalog(dtimsstart ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtimsstart.msg)
cde_message_catalog(dtinfo_start ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtinfo_start.msg)
cde_message_catalog(dtksh ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtksh.msg)
cde_message_catalog(dtlogin ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtlogin.msg)
cde_message_catalog(dtlp ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtlp.msg)
cde_message_catalog(dtmailopts ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtmailopts.msg)
cde_message_catalog(dtpad ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtpad.msg)
cde_message_catalog(dtpdm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtpdm.msg)
cde_message_catalog(dtpdmd ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtpdmd.msg)
cde_message_catalog(dtscreen ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtscreen.msg)
cde_message_catalog(dtsearch ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtsearch.msg)
cde_message_catalog(dtstyle ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtstyle.msg)
cde_message_catalog(dtterm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtterm.msg)
cde_message_catalog(dttypes ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dttypes.msg)
cde_message_catalog(dtwm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtwm.msg)
cde_message_catalog(dtudcexch ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtudcexch.msg)
cde_message_catalog(dtudcfonted ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/dtudcfonted.msg)
cde_message_catalog(libABil ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/libABil.msg)
cde_message_catalog(libABobjXm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/libABobjXm.msg)
cde_message_catalog(libAButil ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/libAButil.msg)
cde_message_catalog(libdtcm ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/libdtcm.msg)
cde_message_catalog(libDtMail ${CMAKE_CURRENT_SOURCE_DIR}/catalogs/libDtMail.msg)
cde_message_catalog(dtinfo ${PROJECT_SOURCE_DIR}/lib/DtInfo/dtinfo.msg)
install(CODE "file(CREATE_LINK C \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/dt/lib/nls/msg/en_US.UTF-8\" SYMBOLIC)")
cde_resource(catalogs/dtsession.msg catalogs/dtsession.msg.src share/dt/lib/nls/msg/C NO_INSTALL)
cde_message_catalog(dtsession ${CMAKE_CURRENT_BINARY_DIR}/catalogs/dtsession.msg)
set(CDE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CDE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CDE_VERSION_MICRO ${PROJECT_VERSION_PATCH})
set(CDE_VERSION_DEV "")
configure_file(copyright.in copyright @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/copyright DESTINATION share/doc/cde)

cde_localized_resource(app-defaults/Dtcm ${PROJECT_SOURCE_DIR}/src/dtcm/Dtcm.ad ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dtcm.tmsg share/dt/app-defaults/C)
cde_localized_resource(app-defaults/Dthelpview ${PROJECT_SOURCE_DIR}/src/dthelpview/Dthelpview ${CMAKE_CURRENT_SOURCE_DIR}/messages/Dthelpview.tmsg share/dt/app-defaults/C)
