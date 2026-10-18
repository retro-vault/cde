add_executable(tt_type_comp
    mp_type_comp.C
    mp_types_table.C
    frozen.mp_types_lex.C
    frozen.mp_types_gram.C
)
target_include_directories(tt_type_comp PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(tt_type_comp PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS tt_type_comp RUNTIME DESTINATION bin)
