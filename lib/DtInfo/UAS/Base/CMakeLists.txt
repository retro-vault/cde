add_library(info_UAS_Base OBJECT
    UAS_Base.C
    UAS_Buffer.C
    UAS_Collection.C
    UAS_Common.C
    UAS_EmbeddedObject.C
    UAS_Exceptions.C
    UAS_Factory.C
    UAS_OQLParser.C
    UAS_Path.C
    UAS_SearchEngine.C
    UAS_SearchResults.C
    UAS_SearchResultsEntry.C
    UAS_SearchScope.C
    UAS_BookcaseEntry.C
    UAS_TextRun.C
    UAS_String.C
    UAS_StyleSheet.C
)
target_link_libraries(info_UAS_Base PRIVATE info_build_options)
target_include_directories(info_UAS_Base PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
