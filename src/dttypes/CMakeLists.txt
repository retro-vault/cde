add_executable(dttypes dttypes.c)
target_link_libraries(dttypes PRIVATE cde_build_options DtSvc tt)
install(TARGETS dttypes RUNTIME DESTINATION bin)
