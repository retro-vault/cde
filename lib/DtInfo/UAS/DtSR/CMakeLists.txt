add_library(info_UAS_DtSR OBJECT
    DtSR_BookcaseEntry.C
    DtSR_Parser.C
    DtSR_SearchEngine.C
    DtSR_SearchResults.C
    DtSR_SearchResultsEntry.C
    DtSR_Stems.C
    DtSR_SearchZones.C
    Tml_TextRenderer.C
    TextParser.C
)
target_link_libraries(info_UAS_DtSR PRIVATE info_build_options)
target_include_directories(info_UAS_DtSR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
