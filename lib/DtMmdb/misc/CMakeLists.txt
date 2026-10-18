add_library(mmdb_misc OBJECT
    unique_id.c
)
target_link_libraries(mmdb_misc PRIVATE mmdb_build_options)
set_target_properties(mmdb_misc PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_misc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
