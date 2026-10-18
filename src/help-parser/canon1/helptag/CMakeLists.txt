add_library(help_canon1_application STATIC
    custom.c
    default.c
    help.c
    option.c
    special.c
    out.c
    xref.c
    global.c
)
add_dependencies(help_canon1_application help_canon1_parser_context help_canon1_elements)
target_link_libraries(help_canon1_application PRIVATE help_canon1_options)
target_include_directories(help_canon1_application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../parser ${CMAKE_CURRENT_BINARY_DIR}/../eltdef ${CMAKE_CURRENT_BINARY_DIR}/../build ${CMAKE_CURRENT_SOURCE_DIR}/../parser ${CMAKE_CURRENT_SOURCE_DIR}/../util)
target_include_directories(help_canon1_application BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/helptag ${CMAKE_CURRENT_SOURCE_DIR}/../../include/parser)
