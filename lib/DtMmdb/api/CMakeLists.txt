add_library(mmdb_api OBJECT
    base.C
    info_base.C
    info_lib.C
    smart_ptr.C
    transaction.C
    utility.C
)
target_link_libraries(mmdb_api PRIVATE mmdb_build_options)
set_target_properties(mmdb_api PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_api PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
