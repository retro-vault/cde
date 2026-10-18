add_executable(dtsearchpath AppSearchPath.C DbSearchPath.C HelpSearchPath.C IconSearchPath.C InfoLibSearchPath.C ManSearchPath.C Options.C SearchPath.C dtsearchpath.C)
target_link_libraries(dtsearchpath PRIVATE CliSrv)
install(TARGETS dtsearchpath RUNTIME DESTINATION bin)
