add_test(NAME DtHelp.compile_volume
    COMMAND ${CMAKE_COMMAND} -DWRAPPER=${PROJECT_BINARY_DIR}/src/help-parser/dthelptag
        -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/roundtrip.htg
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/CompileVolume.cmake)
set_tests_properties(DtHelp.compile_volume PROPERTIES TIMEOUT 15)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/invalid-work)
add_test(NAME DocBook.reject_invalid_document
    COMMAND ${CMAKE_COMMAND} -DGENERATOR=$<TARGET_FILE:docbook_infolib_generator>
        -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/invalid.sgm
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/invalid-work
        -P ${CMAKE_CURRENT_SOURCE_DIR}/RejectInvalid.cmake)
set_tests_properties(DocBook.reject_invalid_document PROPERTIES TIMEOUT 15
    ENVIRONMENT "PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}")

add_test(NAME DtHelp.registered_volumes
    COMMAND ${CMAKE_COMMAND} -DPREFIX=${CMAKE_INSTALL_PREFIX}
        -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/help-index
        -P ${CMAKE_CURRENT_SOURCE_DIR}/HelpIndex.cmake)
set_tests_properties(DtHelp.registered_volumes PROPERTIES TIMEOUT 15)
