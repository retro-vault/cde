add_executable(dtimsstart
    action.c
    env.c
    file.c
    main.c
    remote.c
    select.c
    start.c
    util.c
    win.c
    ximserr.h
    ximsfunc.h
    xims.h
    ximspath.h
)
target_link_libraries(dtimsstart PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
target_compile_definitions(dtimsstart PRIVATE NLS)
cde_resource(0020.dtims 0020.dtims.src share/dt/config/Xsession.d EXECUTABLE)
install(TARGETS dtimsstart RUNTIME DESTINATION bin)

configure_file(conf/start.conf.in start.conf @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/start.conf conf/none DESTINATION share/dt/config/ims)
foreach(locale C C.UTF-8 en_US.UTF-8 de_DE.UTF-8 el_GR.UTF-8 es_ES.UTF-8 fr_FR.UTF-8
        it_IT.UTF-8 ja_JP.UTF-8 ko_KR.UTF-8 sv_SE.UTF-8 zh_CN.UTF-8 zh_TW.UTF-8)
    install(FILES conf/default DESTINATION share/dt/config/ims RENAME ${locale})
endforeach()
