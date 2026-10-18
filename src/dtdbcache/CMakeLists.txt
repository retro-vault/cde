add_executable(dtdbcache
    Main.c
)
target_link_libraries(dtdbcache PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtdbcache PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtdbcache RUNTIME DESTINATION bin)
