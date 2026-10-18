function(cde_documentation_language locale source_root work suffix)
    file(MAKE_DIRECTORY ${work}/tmp ${work}/common/help)
    file(COPY ${source_root}/help ${source_root}/guides DESTINATION ${work})
    configure_file(${PROJECT_SOURCE_DIR}/src/documentation/common/help/HELPEnt.sgm.in
        ${work}/common/help/HELPEnt.sgm @ONLY)
    include(${source_root}/GuideTitles.cmake)
    file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${source_root}/guides/*)
    set(tocs)
    foreach(directory IN LISTS guide_directories)
        set(identifier "${guide_id_${directory}}")
        set(title "${guide_title_${directory}}")
        add_custom_command(OUTPUT ${work}/guides/${directory}/TOC.sgm
            COMMAND ${CMAKE_COMMAND} -E make_directory ${work}/tmp/${directory}
            COMMAND ${CMAKE_COMMAND} -E env "SGML_SEARCH_PATH=.:.." LC_ALL=C.UTF-8
                "PATH=$<TARGET_FILE_DIR:dtsrcreate>:$ENV{PATH}"
                $<TARGET_FILE:docbook_infolib_generator> tocgen -T ${work}/tmp/${directory}
                -L ${locale} -m common/catalog -f ${directory}/TOC.sgm
                -id ${identifier} -title "${title}" ${directory}/book.sgm
            WORKING_DIRECTORY ${work}/guides
            DEPENDS docbook_infolib_generator ${docbook_helper_files}
                ${docbook_build_data}/dtsr/dtsearch.dbd ${sources} ${source_root}/GuideTitles.cmake
            VERBATIM)
        list(APPEND tocs ${work}/guides/${directory}/TOC.sgm)
    endforeach()
    add_custom_command(OUTPUT ${work}/cde.dti/CDEDOC/dtsearch/dtsearch.ocf
        COMMAND ${CMAKE_COMMAND} -E make_directory ${work}/tmp/library
        COMMAND ${CMAKE_COMMAND} -E env "SGML_SEARCH_PATH=.:.." LC_ALL=C.UTF-8
            "PATH=$<TARGET_FILE_DIR:dtsrcreate>:$ENV{PATH}"
            $<TARGET_FILE:docbook_infolib_generator> build -T ${work}/tmp/library
            -L ${locale} -m common/catalog -n cde -d "${infolib_description}" -l ../cde.dti bookcase.bc
        WORKING_DIRECTORY ${work}/guides
        DEPENDS docbook_infolib_generator ${docbook_helper_files}
            ${docbook_build_data}/dtsr/dtsearch.dbd ${tocs} ${sources}
            dtsrcreate dtsrload dtsrindex huffcode VERBATIM)
    add_custom_target(desktop_information_library${suffix} ALL
        DEPENDS ${work}/cde.dti/CDEDOC/dtsearch/dtsearch.ocf)
    install(DIRECTORY ${work}/cde.dti DESTINATION share/dt/infolib/${locale})

    file(GLOB_RECURSE help_sources CONFIGURE_DEPENDS ${source_root}/help/*)
    file(GLOB books RELATIVE ${source_root}/help ${source_root}/help/*/book.sgm)
    file(MAKE_DIRECTORY ${work}/help/tmp)
    set(help_products)
    foreach(book IN LISTS books)
        get_filename_component(volume ${book} DIRECTORY)
        set(output ${work}/help/${volume}.sdl)
        add_custom_command(OUTPUT ${output}
            COMMAND ${CMAKE_COMMAND} -E env "SGML_SEARCH_PATH=.:.." "TMPDIR=${work}/help/tmp"
                "dtdcbk_libdir=${docbook_build_data}" "dtdcbk_datarootdir=${docbook_build_data}"
                /bin/ksh ${PROJECT_BINARY_DIR}/src/dtdocbook/dtdocbook2sdl
                -H $<TARGET_FILE:dthelp_htag2> -I $<TARGET_FILE:instant>
                -L ${locale} -o ${volume}.sdl ${book}
            WORKING_DIRECTORY ${work}/help
            DEPENDS instant dthelp_htag2 ${help_sources}
                ${PROJECT_BINARY_DIR}/src/dtdocbook/dtdocbook2sdl
                ${PROJECT_SOURCE_DIR}/src/documentation/common/help/HELPEnt.sgm.in VERBATIM)
        list(APPEND help_products ${output})
        install(FILES ${output} DESTINATION share/dt/appconfig/help/${locale})
        if(EXISTS ${source_root}/help/${volume}/graphics)
            install(DIRECTORY ${source_root}/help/${volume}/graphics
                DESTINATION share/dt/appconfig/help/${locale}/${volume} PATTERN CDR EXCLUDE)
        endif()
    endforeach()
    add_custom_target(desktop_help_volumes${suffix} ALL DEPENDS ${help_products})
    install(DIRECTORY ${source_root}/help/common/graphics DESTINATION share/dt/appconfig/help/${locale})
    file(GLOB family_templates CONFIGURE_DEPENDS ${source_root}/help/common/*.hf.in)
    foreach(template IN LISTS family_templates)
        get_filename_component(family ${template} NAME_WLE)
        configure_file(${template} ${work}/help/common/${family} @ONLY)
        install(FILES ${work}/help/common/${family} DESTINATION share/dt/appconfig/help/${locale})
    endforeach()
endfunction()
