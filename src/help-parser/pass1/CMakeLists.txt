add_library(help_pass1_options INTERFACE)
target_link_libraries(help_pass1_options INTERFACE cde_build_options)
target_compile_definitions(help_pass1_options INTERFACE PASS1)
target_include_directories(help_pass1_options INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/util ${CMAKE_CURRENT_SOURCE_DIR}/../include/build
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/eltdef ${CMAKE_CURRENT_SOURCE_DIR}/../include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/helptag)
add_subdirectory(util)
add_subdirectory(build)
add_subdirectory(eltdef)
add_subdirectory(parser)
add_subdirectory(helptag)
