find_program(XVFB_RUN xvfb-run REQUIRED)
add_test(NAME Dtksh.shell_contract COMMAND dtksh ${CMAKE_CURRENT_SOURCE_DIR}/shell.ksh)
add_test(NAME Dtksh.motif_text_roundtrip
    COMMAND ${XVFB_RUN} -a $<TARGET_FILE:dtksh> ${CMAKE_CURRENT_SOURCE_DIR}/widget.ksh)
set_tests_properties(Dtksh.shell_contract Dtksh.motif_text_roundtrip PROPERTIES TIMEOUT 20)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/home)
set_tests_properties(Dtksh.shell_contract Dtksh.motif_text_roundtrip PROPERTIES ENVIRONMENT "HOME=${CMAKE_CURRENT_BINARY_DIR}/home")
