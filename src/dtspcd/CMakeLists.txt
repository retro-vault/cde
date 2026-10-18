add_executable(dtspcd
    main.c
    spcd_event.c
)
target_link_libraries(dtspcd PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtspcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtspcd RUNTIME DESTINATION bin)
