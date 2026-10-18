add_library(builder_build_options INTERFACE)
target_include_directories(builder_build_options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ab_private ${PROJECT_SOURCE_DIR}/lib/ABil
    ${PROJECT_BINARY_DIR}/lib/ABil)
target_link_libraries(builder_build_options INTERFACE cde_build_options)
add_library(AButil STATIC
    abio.c
    abio_path.c
    istr.c
    strlist.c
    util.c
    util_convert.c
    util_ds.c
    util_err.c
    util_file.c
    util_string.c
)
target_link_libraries(AButil PUBLIC builder_build_options )
target_include_directories(AButil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
