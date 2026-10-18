add_library(info_UAS_MMDB OBJECT
    MMDB.C
    MMDB_Common.C
    MMDB_Factory.C
    MMDB_Section.C
    MMDB_Library.C
    MMDB_BookCase.C
    MMDB_EmbeddedObject.C
    MMDB_StyleSheet.C
)
target_link_libraries(info_UAS_MMDB PRIVATE info_build_options)
target_include_directories(info_UAS_MMDB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
