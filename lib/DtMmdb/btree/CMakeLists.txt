add_library(mmdb_btree OBJECT
    btree.C
)
target_link_libraries(mmdb_btree PRIVATE mmdb_build_options)
set_target_properties(mmdb_btree PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_btree PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
