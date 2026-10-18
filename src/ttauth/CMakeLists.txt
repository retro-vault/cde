add_executable(ttauth
    ttauth.c
    process.c
)
target_include_directories(ttauth PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(ttauth PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS ttauth RUNTIME DESTINATION bin)
