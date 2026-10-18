add_executable(test_calendar_rpc test_rpc.c)
target_link_libraries(test_calendar_rpc PRIVATE csa cde_build_options)
add_test(NAME Calendar.rpc_roundtrip COMMAND test_calendar_rpc)
set_tests_properties(Calendar.rpc_roundtrip PROPERTIES TIMEOUT 20)
