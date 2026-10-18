add_executable(dtappgather Options.C dtappgather.C)
target_link_libraries(dtappgather PRIVATE CliSrv)
install(TARGETS dtappgather RUNTIME DESTINATION bin)
