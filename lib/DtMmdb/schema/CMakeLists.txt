bison_target(mmdb_schema sheet.yy ${CMAKE_CURRENT_BINARY_DIR}/sheet.C
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/sheet.tab.h COMPILE_FLAGS "-p schema -l")
flex_target(mmdb_schema_tokens token.ll ${CMAKE_CURRENT_BINARY_DIR}/token.C COMPILE_FLAGS "-8 -s -P schema")
add_flex_bison_dependency(mmdb_schema_tokens mmdb_schema)
add_library(mmdb_schema OBJECT
    desc.C
    store_desc.C
    object_dict.C
    stored_object_desc.C
    index_desc.C
    inv_desc.C
    agent_desc.C
    container_desc.C
    ${BISON_mmdb_schema_OUTPUTS} ${FLEX_mmdb_schema_tokens_OUTPUTS}
)
target_link_libraries(mmdb_schema PRIVATE mmdb_build_options)
set_target_properties(mmdb_schema PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_schema PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
