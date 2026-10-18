add_library(mmdb_object OBJECT
    composite.C
    compressed_pstring.C
    cset.C
    dl_list.C
    dl_list_cell.C
    handler.C
    integer.C
    long_pstring.C
    oid.C
    oid_list.C
    oid_t.C
    primitive.C
    pstring.C
    random_gen.C
    root.C
    short_list.C
    tuple.C
)
target_link_libraries(mmdb_object PRIVATE mmdb_build_options)
set_target_properties(mmdb_object PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_object PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
