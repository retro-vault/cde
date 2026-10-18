add_library(info_Support OBJECT
    List_base.C
    UtilityFunctions.C
)
target_link_libraries(info_Support PRIVATE info_build_options)
target_include_directories(info_Support PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
