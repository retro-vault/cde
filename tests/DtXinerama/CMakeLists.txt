add_executable(test_dtxinerama test_dtxinerama.c)
target_link_libraries(test_dtxinerama PRIVATE DtXinerama)
target_compile_options(test_dtxinerama PRIVATE -Wall -Wextra -Wpedantic -Werror)
add_test(NAME DtXinerama.screen_contract COMMAND test_dtxinerama)
