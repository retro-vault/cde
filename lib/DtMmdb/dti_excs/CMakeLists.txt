add_library(mmdb_dti_excs OBJECT
    Jump_Environment.C
    Exceptions.C
    Exception.C
    Destructable.C
    terminate.C
)
target_link_libraries(mmdb_dti_excs PRIVATE mmdb_build_options)
set_target_properties(mmdb_dti_excs PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(mmdb_dti_excs PRIVATE NATIVE_EXCEPTIONS)
target_include_directories(mmdb_dti_excs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
