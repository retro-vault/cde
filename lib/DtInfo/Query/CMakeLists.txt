add_library(info_Query OBJECT
    QueryEditor.C
    QueryTermView.C
    QueryGroupView.C
    QueryTerm.C
    QueryGroup.C
)
target_link_libraries(info_Query PRIVATE info_build_options)
target_include_directories(info_Query PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
