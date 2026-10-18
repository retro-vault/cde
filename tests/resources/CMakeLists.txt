add_test(NAME Resources.installed_text
    COMMAND ${CMAKE_COMMAND} -DPREFIX=${CMAKE_INSTALL_PREFIX}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/CheckInstalled.cmake)

add_test(NAME Resources.clean_install
    COMMAND ${CMAKE_COMMAND} -DBUILD_DIR=${PROJECT_BINARY_DIR}
        -DPREFIX=${CMAKE_INSTALL_PREFIX} -DSTAGE=${CMAKE_CURRENT_BINARY_DIR}/clean-root
        -P ${CMAKE_CURRENT_SOURCE_DIR}/CleanInstall.cmake)
set_tests_properties(Resources.clean_install PROPERTIES TIMEOUT 60 RUN_SERIAL TRUE)
