add_library(help_pass2_application STATIC
    custom.c
    sdl.c
    option.c
    out.c
    global.c
)
add_dependencies(help_pass2_application help_pass2_parser_context help_pass2_elements)
target_link_libraries(help_pass2_application PRIVATE help_pass2_options)
target_include_directories(help_pass2_application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../parser ${CMAKE_CURRENT_BINARY_DIR}/../eltdef ${CMAKE_CURRENT_BINARY_DIR}/../build ${CMAKE_CURRENT_SOURCE_DIR}/../parser ${CMAKE_CURRENT_SOURCE_DIR}/../util)
target_include_directories(help_pass2_application BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../htag2 ${CMAKE_CURRENT_SOURCE_DIR}/../../include/parser)
