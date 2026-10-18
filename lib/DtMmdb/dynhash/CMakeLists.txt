add_library(mmdb_dynhash OBJECT
    data_t.C
    imp_bucket.C
    imp_die.C
)
target_link_libraries(mmdb_dynhash PRIVATE mmdb_build_options)
set_target_properties(mmdb_dynhash PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_dynhash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
