add_executable(tttar
    tttar.C
    archiver.C
    tttar_utils.C
    tttar_api.C
    tttar_spec.C
    tttar_file_utils.C
    tttar_string_map.C
)
target_include_directories(tttar PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(tttar PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS tttar RUNTIME DESTINATION bin)
