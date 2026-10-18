bison_target(mmdb_defParser defParser.yy ${CMAKE_CURRENT_BINARY_DIR}/defParser.C DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/defParser.tab.h COMPILE_FLAGS "-p defParser -l")
flex_target(mmdb_defToken defToken.ll ${CMAKE_CURRENT_BINARY_DIR}/defToken.C COMPILE_FLAGS "-8 -s -P defParser")
add_flex_bison_dependency(mmdb_defToken mmdb_defParser)
bison_target(mmdb_style style.yy ${CMAKE_CURRENT_BINARY_DIR}/style.C DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/style.tab.h COMPILE_FLAGS "-p style -l")
flex_target(mmdb_tokenStyle tokenStyle.ll ${CMAKE_CURRENT_BINARY_DIR}/tokenStyle.C COMPILE_FLAGS "-8 -s -P style")
add_flex_bison_dependency(mmdb_tokenStyle mmdb_style)
add_library(mmdb_StyleSheet OBJECT
    ${BISON_mmdb_style_OUTPUTS} ${FLEX_mmdb_tokenStyle_OUTPUTS}
    ${BISON_mmdb_defParser_OUTPUTS} ${FLEX_mmdb_defToken_OUTPUTS}
    Attribute.C
    AttributeList.C
    BitVector.C
    DocParser.C
    Element.C
    Expression.C
    Feature.C
    FeatureDefDictionary.C
    FeatureSet.C
    FeatureValue.C
    PathQualifier.C
    PathTable.C
    RendererHCV.C
    Resolver.C
    ResolverStack.C
    SSPath.C
    SSTemplates.C
    StyleSheet.C
    StyleSheetExceptions.C
    SymTab.C
    VariableTable.C
)
target_link_libraries(mmdb_StyleSheet PRIVATE mmdb_build_options)
set_target_properties(mmdb_StyleSheet PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_StyleSheet PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(mmdb_StyleSheet PRIVATE EXPAND_TEMPLATES CDE_NEXT)
target_include_directories(mmdb_StyleSheet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
