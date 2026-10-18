flex_target(mmdb_sgml sgml.ll ${CMAKE_CURRENT_BINARY_DIR}/sgml.C COMPILE_FLAGS "-8 -s -P sgml")
flex_target(mmdb_ps ps.ll ${CMAKE_CURRENT_BINARY_DIR}/ps.C COMPILE_FLAGS "-8 -s -P ps")
add_library(mmdb_compression OBJECT
    abs_agent.C
    zip.C
    huffman.C
    trie.C
    code.C
    lzss.C
    ${FLEX_mmdb_sgml_OUTPUTS} ${FLEX_mmdb_ps_OUTPUTS}
)
target_link_libraries(mmdb_compression PRIVATE mmdb_build_options)
set_target_properties(mmdb_compression PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_compression PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
