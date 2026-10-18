add_executable(test_mmdb_document test_document.C)
target_include_directories(test_mmdb_document PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_link_libraries(test_mmdb_document PRIVATE cde_build_options DtMmdb)
add_test(NAME DtMmdb.generated_document
    COMMAND test_mmdb_document ${CMAKE_INSTALL_PREFIX}/share/dt/infolib/en_US.UTF-8/cde.dti)
set_tests_properties(DtMmdb.generated_document PROPERTIES TIMEOUT 15)
foreach(locale de_DE.UTF-8 es_ES.UTF-8 fr_FR.UTF-8 it_IT.UTF-8 ja_JP.UTF-8)
    include(${PROJECT_SOURCE_DIR}/src/documentation/locales/${locale}/GuideTitles.cmake)
    add_test(NAME DtMmdb.document_${locale}
        COMMAND test_mmdb_document ${CMAKE_INSTALL_PREFIX}/share/dt/infolib/${locale}/cde.dti "${guide_title_usersGuide}")
    set_tests_properties(DtMmdb.document_${locale} PROPERTIES TIMEOUT 15)
endforeach()

add_executable(test_mmdb_marks test_marks.C)
target_include_directories(test_mmdb_marks PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_link_libraries(test_mmdb_marks PRIVATE cde_build_options DtMmdb)
add_test(NAME DtMmdb.user_marks
    COMMAND ${CMAKE_COMMAND} -DPROGRAM=$<TARGET_FILE:test_mmdb_marks>
        -DPREFIX=${CMAKE_INSTALL_PREFIX} -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/marks-work
        -P ${CMAKE_CURRENT_SOURCE_DIR}/Marks.cmake)
set_tests_properties(DtMmdb.user_marks PROPERTIES TIMEOUT 15)
