add_executable(test_isam test_isam.c)
target_link_libraries(test_isam PRIVATE tt_isam tt_build_options)
add_test(NAME ToolTalk.database_roundtrip COMMAND test_isam)
set_tests_properties(ToolTalk.database_roundtrip PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_message test_message.c)
target_link_libraries(test_message PRIVATE tt)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/home)
add_test(NAME ToolTalk.message_roundtrip
    COMMAND ${CMAKE_COMMAND} -E env
        TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data
        HOME=${CMAKE_CURRENT_BINARY_DIR}/home
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/home/authority
        $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_message>)
set_tests_properties(ToolTalk.message_roundtrip PROPERTIES TIMEOUT 20
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME ToolTalk.compiled_types
    COMMAND tt_type_comp -P ${PROJECT_BINARY_DIR}/src/desktop-data/types.xdr)
set_tests_properties(ToolTalk.compiled_types PROPERTIES PASS_REGULAR_EXPRESSION "DTPAD")
add_executable(test_database_rpc test_database_rpc.c)
target_link_libraries(test_database_rpc PRIVATE tt)
add_test(NAME ToolTalk.rpc_database_roundtrip
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/home
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/home/database-authority
        $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_database_rpc>
        ${CMAKE_CURRENT_BINARY_DIR}/rpc-object)
set_tests_properties(ToolTalk.rpc_database_roundtrip PROPERTIES TIMEOUT 20
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/object.xdr
    COMMAND tt_type_comp -x -o ${CMAKE_CURRENT_BINARY_DIR}/object.xdr ${CMAKE_CURRENT_SOURCE_DIR}/object.types
    DEPENDS tt_type_comp object.types VERBATIM)
add_custom_target(test_object_type ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/object.xdr)
target_compile_definitions(test_database_rpc PRIVATE TEST_OBJECT_TYPES="${CMAKE_CURRENT_BINARY_DIR}/object.xdr")
add_dependencies(test_database_rpc test_object_type)
