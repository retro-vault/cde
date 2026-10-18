add_executable(dtpdmd
    dispatch.c
    dtpdmd.c
    mailbox.c
    manager.c
    records.c
    nlmsg.c
    setup.c
    util.c
    dtpdmdP.h
    nlmsg.h
)
target_link_libraries(dtpdmd PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtpdmd RUNTIME DESTINATION bin)
target_link_libraries(dtpdmd PRIVATE X11::Xau)
