add_executable(dtexec
    Main.c
)
target_link_libraries(dtexec PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtexec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
target_compile_definitions(dtexec PRIVATE MSGLOG_CLIENT_ONLY)
install(TARGETS dtexec RUNTIME DESTINATION bin)
