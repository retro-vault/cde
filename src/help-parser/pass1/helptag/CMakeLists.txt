add_library(help_pass1_application STATIC
    custom.c
    default.c
    help.c
    option.c
    special.c
    out.c
    xref.c
    global.c
)
add_dependencies(help_pass1_application help_pass1_parser_context help_pass1_elements)
target_link_libraries(help_pass1_application PRIVATE help_pass1_options)
target_include_directories(help_pass1_application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../parser ${CMAKE_CURRENT_BINARY_DIR}/../eltdef ${CMAKE_CURRENT_BINARY_DIR}/../build ${CMAKE_CURRENT_SOURCE_DIR}/../parser ${CMAKE_CURRENT_SOURCE_DIR}/../util)
target_include_directories(help_pass1_application BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/helptag ${CMAKE_CURRENT_SOURCE_DIR}/../../include/parser)
