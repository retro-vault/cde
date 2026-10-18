add_executable(tttrace
    tttrace.C
    tttrace_objs.C
)
target_include_directories(tttrace PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(tttrace PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS tttrace RUNTIME DESTINATION bin)
