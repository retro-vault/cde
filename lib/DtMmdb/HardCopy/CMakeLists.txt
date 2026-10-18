add_library(mmdb_HardCopy OBJECT
    FPset.C
    HardCopyFP.C
    TemplatesAutoNumber.C
    autoNumber.C
    autoNumberFP.C
)
target_link_libraries(mmdb_HardCopy PRIVATE mmdb_build_options)
set_target_properties(mmdb_HardCopy PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(mmdb_HardCopy PRIVATE EXPAND_TEMPLATES CDE_NEXT)
target_include_directories(mmdb_HardCopy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
