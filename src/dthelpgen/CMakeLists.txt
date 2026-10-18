add_executable(dthelpgen
    helpgen.c
)
target_include_directories(dthelpgen PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtHelp)
target_link_libraries(dthelpgen PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dthelpgen RUNTIME DESTINATION bin)
