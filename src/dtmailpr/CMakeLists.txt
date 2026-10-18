add_executable(dtmailpr
    main.C
    message.C
    mailbox.C
    utils.C
)
target_link_libraries(dtmailpr PRIVATE DtMail cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtmailpr RUNTIME DESTINATION bin)
