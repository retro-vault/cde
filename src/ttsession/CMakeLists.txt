add_executable(ttsession
    mp_server.C
)
target_include_directories(ttsession PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(ttsession PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS ttsession RUNTIME DESTINATION libexec/cde)
set_target_properties(ttsession PROPERTIES INSTALL_RPATH "$ORIGIN/../../lib")
