add_library(help_pass2_util STATIC
    allwhite.c
    inctest.c
    letter.c
    triedump.c
    triepdmp.c
    trieplk.c
    trierset.c
    upcmp8.c
    upstrcmp.c
    wchar.c
    conutil.c
    error.c
    exit.c
    itoa.c
    malloc.c
    openchk.c
    trie.c
    triecnt.c
    whitesp.c
)
target_link_libraries(help_pass2_util PUBLIC help_pass2_options)
add_executable(help_pass2_context context.c)
target_link_libraries(help_pass2_context PRIVATE help_pass2_util)
