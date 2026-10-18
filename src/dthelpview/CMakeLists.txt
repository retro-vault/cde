add_executable(dthelpview
    Main.c
    ManPage.c
    Util.c
)
target_include_directories(dthelpview PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtHelp)
target_link_libraries(dthelpview PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
target_compile_definitions(dthelpview PRIVATE _BMS)
install(TARGETS dthelpview RUNTIME DESTINATION bin)
