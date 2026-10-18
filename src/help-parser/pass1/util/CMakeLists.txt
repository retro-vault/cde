add_library(help_pass1_util STATIC
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
target_link_libraries(help_pass1_util PUBLIC help_pass1_options)
add_executable(help_pass1_context context.c)
target_link_libraries(help_pass1_context PRIVATE help_pass1_util)
