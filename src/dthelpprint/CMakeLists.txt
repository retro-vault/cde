add_executable(dthelpprint
    Main.c
    Initialize.c
    PrintUtil.c
    PrintTopics.c
    PrintManStrFile.c
)
target_include_directories(dthelpprint PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtHelp)
target_link_libraries(dthelpprint PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dthelpprint RUNTIME DESTINATION bin)

configure_file(dthelpprint.sh.in dthelpprint.sh @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dthelpprint.sh DESTINATION bin)
