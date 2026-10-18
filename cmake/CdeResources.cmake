function(cde_resource output input destination)
    cmake_parse_arguments(RESOURCE "EXECUTABLE;KEEP_COMMENTS;NO_INSTALL" "" "" ${ARGN})
    set(cpp_extra)
    if(RESOURCE_KEEP_COMMENTS)
        list(APPEND cpp_extra -C)
    endif()
    get_filename_component(output_dir "${CMAKE_CURRENT_BINARY_DIR}/${output}" DIRECTORY)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${output}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
        COMMAND ${CMAKE_COMMAND} -DGENERATOR=$<TARGET_FILE:tradcpp>
            "-DGENERATOR_ARGS=-P;${cpp_extra};-DXCOMM=#;-DCDE_INSTALLATION_TOP=${CDE_INSTALLATION_TOP};-DCDE_DATA_TOP=${CDE_DATA_TOP};-DCDE_CONFIGURATION_TOP=${CDE_CONFIGURATION_TOP};-DCDE_LOGFILES_TOP=${CDE_LOGFILES_TOP};-DKORNSHELL=/bin/ksh;-DDTKORNSHELL=${CDE_INSTALLATION_TOP}/bin/dtksh;${CMAKE_CURRENT_SOURCE_DIR}/${input}"
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${output}
            -P ${PROJECT_SOURCE_DIR}/cmake/RunGenerator.cmake
        DEPENDS tradcpp ${input} VERBATIM)
    string(MAKE_C_IDENTIFIER "${CMAKE_CURRENT_BINARY_DIR}_${output}" resource_target)
    add_custom_target(${resource_target} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${output})
    if(RESOURCE_NO_INSTALL)
        return()
    endif()
    if(RESOURCE_EXECUTABLE)
        install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${output} DESTINATION ${destination})
    else()
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${output} DESTINATION ${destination})
    endif()
endfunction()

function(cde_localized_resource output input messages destination)
    cmake_parse_arguments(MERGE "" "DEFAULT_MESSAGES" "" ${ARGN})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${output}
        COMMAND ${CMAKE_COMMAND} -DGENERATOR=$<TARGET_FILE:resource_merge>
            -DINPUT=${input} -DMESSAGES=${messages}
            -DDEFAULT_MESSAGES=${MERGE_DEFAULT_MESSAGES}
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${output}
            -P ${PROJECT_SOURCE_DIR}/cmake/RunMerge.cmake
        DEPENDS resource_merge ${input} ${messages} ${MERGE_DEFAULT_MESSAGES} VERBATIM)
    string(MAKE_C_IDENTIFIER "${CMAKE_CURRENT_BINARY_DIR}_${output}" resource_target)
    add_custom_target(${resource_target} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${output})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${output} DESTINATION ${destination})
    if(NOT MERGE_DEFAULT_MESSAGES)
        set_property(GLOBAL APPEND PROPERTY CDE_TRANSLATABLE_RESOURCES
            "${output}|${input}|${messages}|${destination}")
    endif()
endfunction()

# Recreate catalogs rather than merging with a previous generated catalog.
function(cde_message_catalog name)
    cmake_parse_arguments(CATALOG "" "LOCALE" "" ${ARGN})
    if(NOT CATALOG_LOCALE)
        set(CATALOG_LOCALE C)
        set_property(GLOBAL APPEND PROPERTY CDE_MESSAGE_CATALOGS ${name})
        set(target catalog_${name})
    else()
        string(MAKE_C_IDENTIFIER "catalog_${CATALOG_LOCALE}_${name}" target)
    endif()
    find_program(GENCAT_EXECUTABLE gencat REQUIRED)
    set(output ${CMAKE_CURRENT_BINARY_DIR}/catalogs/${name}.cat)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/catalogs)
    add_custom_command(OUTPUT ${output}
        COMMAND ${CMAKE_COMMAND} -E rm -f ${output}
        COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8 ${GENCAT_EXECUTABLE} ${output} ${CATALOG_UNPARSED_ARGUMENTS}
        DEPENDS ${CATALOG_UNPARSED_ARGUMENTS} VERBATIM)
    add_custom_target(${target} ALL DEPENDS ${output})
    install(FILES ${output} DESTINATION share/dt/lib/nls/msg/${CATALOG_LOCALE})
endfunction()
