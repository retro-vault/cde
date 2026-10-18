# Source documents are copied to the build tree because the translators emit
# adjacent logs, temporary files, and table-of-contents fragments.
set(document_work ${CMAKE_CURRENT_BINARY_DIR}/work)
file(MAKE_DIRECTORY ${document_work})
file(COPY help guides common DESTINATION ${document_work})
set(CDE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CDE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CDE_VERSION_MICRO ${PROJECT_VERSION_PATCH})
set(CDE_VERSION_DEV "")
configure_file(common/help/HELPEnt.sgm.in ${document_work}/common/help/HELPEnt.sgm @ONLY)
set(docbook_build_data ${PROJECT_BINARY_DIR}/src/dtdocbook/data)
file(MAKE_DIRECTORY ${docbook_build_data})
foreach(directory sgml spec tcl tpt locales dtsr)
    file(COPY ${PROJECT_SOURCE_DIR}/src/dtdocbook/${directory} DESTINATION ${docbook_build_data})
endforeach()
set(docbook_build_helpers ${CMAKE_CURRENT_BINARY_DIR}/helpers)
file(MAKE_DIRECTORY ${docbook_build_helpers})
add_executable(docbook_infolib_generator ${PROJECT_SOURCE_DIR}/src/dtdocbook/dtdocbook2infolib.c)
target_compile_definitions(docbook_infolib_generator PRIVATE DTDCBK_DATAROOTDIR="${docbook_build_data}" INFOLIB_LIBEXECDIR="${docbook_build_helpers}")
target_link_libraries(docbook_infolib_generator PRIVATE cde_build_options DtSvc tt)
set(docbook_helper_files)
foreach(helper MixedGen NCFGen NodeParser StyleUpdate dbdrv valBase validator)
    add_custom_command(OUTPUT ${docbook_build_helpers}/${helper}
        COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:${helper}> ${docbook_build_helpers}/${helper}
        DEPENDS ${helper} VERBATIM)
    list(APPEND docbook_helper_files ${docbook_build_helpers}/${helper})
endforeach()
add_custom_command(OUTPUT ${docbook_build_data}/dtsr/dtsearch.dbd
    COMMAND ${CMAKE_COMMAND} -DTOOL=$<TARGET_FILE:docbook_mkdbd> -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}
        -DLOG=${docbook_build_data}/dtsr/dtsearch.dbd -P ${PROJECT_SOURCE_DIR}/cmake/RunHelpTool.cmake
    DEPENDS docbook_mkdbd VERBATIM)
add_custom_target(docbook_build_helpers DEPENDS ${docbook_helper_files} ${docbook_build_data}/dtsr/dtsearch.dbd)
file(GLOB_RECURSE guide_sources CONFIGURE_DEPENDS guides/*)
include(${CMAKE_CURRENT_LIST_DIR}/BuildLanguage.cmake)
cde_documentation_language(en_US.UTF-8 ${CMAKE_CURRENT_SOURCE_DIR} ${document_work} "")
foreach(locale de_DE.UTF-8 es_ES.UTF-8 fr_FR.UTF-8 it_IT.UTF-8 ja_JP.UTF-8)
    string(MAKE_C_IDENTIFIER _${locale} suffix)
    cde_documentation_language(${locale} ${CMAKE_CURRENT_SOURCE_DIR}/locales/${locale}
        ${document_work}/locales/${locale} ${suffix})
endforeach()
install(CODE "file(CREATE_LINK en_US.UTF-8 \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/dt/infolib/C\" SYMBOLIC)")
install(CODE "file(CREATE_LINK en_US.UTF-8 \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/dt/appconfig/help/C\" SYMBOLIC)")

# Man-page rendering uses the same translator and character maps as help.
add_custom_command(OUTPUT ${docbook_build_helpers}/instant/instant
    COMMAND ${CMAKE_COMMAND} -E make_directory ${docbook_build_helpers}/instant
    COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:instant> ${docbook_build_helpers}/instant/instant
    DEPENDS instant VERBATIM)
add_custom_target(docbook_manual_translator DEPENDS ${docbook_build_helpers}/instant/instant)
include(${CMAKE_CURRENT_LIST_DIR}/ManualPages.cmake)
add_dependencies(desktop_manual_pages docbook_manual_translator)
