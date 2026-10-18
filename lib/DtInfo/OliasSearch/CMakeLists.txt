add_library(info_OliasSearch OBJECT
    ResultID.C
)
target_link_libraries(info_OliasSearch PRIVATE info_build_options)
target_include_directories(info_OliasSearch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
