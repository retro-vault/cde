find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_library(LMDB_LIBRARY lmdb REQUIRED)
find_path(LMDB_INCLUDE_DIR lmdb.h REQUIRED)
add_library(mmdb_build_options INTERFACE)
target_link_libraries(mmdb_build_options INTERFACE cde_build_options)
target_include_directories(mmdb_build_options INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/schema ${LMDB_INCLUDE_DIR})
target_compile_definitions(mmdb_build_options INTERFACE PORTABLE_DB)
add_subdirectory(HardCopy)
add_subdirectory(StyleSheet)
add_subdirectory(api)
add_subdirectory(btree)
add_subdirectory(compression)
add_subdirectory(diskhash)
add_subdirectory(dstr)
add_subdirectory(dti_cc)
add_subdirectory(dti_excs)
add_subdirectory(dynhash)
add_subdirectory(hmphf)
add_subdirectory(index)
add_subdirectory(mgrs)
add_subdirectory(misc)
add_subdirectory(object)
add_subdirectory(oliasdb)
add_subdirectory(schema)
add_subdirectory(storage)
add_subdirectory(utility)
add_library(DtMmdb SHARED
    $<TARGET_OBJECTS:mmdb_HardCopy>
    $<TARGET_OBJECTS:mmdb_StyleSheet>
    $<TARGET_OBJECTS:mmdb_api>
    $<TARGET_OBJECTS:mmdb_btree>
    $<TARGET_OBJECTS:mmdb_compression>
    $<TARGET_OBJECTS:mmdb_diskhash>
    $<TARGET_OBJECTS:mmdb_dstr>
    $<TARGET_OBJECTS:mmdb_dti_cc>
    $<TARGET_OBJECTS:mmdb_dti_excs>
    $<TARGET_OBJECTS:mmdb_dynhash>
    $<TARGET_OBJECTS:mmdb_hmphf>
    $<TARGET_OBJECTS:mmdb_index>
    $<TARGET_OBJECTS:mmdb_mgrs>
    $<TARGET_OBJECTS:mmdb_misc>
    $<TARGET_OBJECTS:mmdb_object>
    $<TARGET_OBJECTS:mmdb_oliasdb>
    $<TARGET_OBJECTS:mmdb_schema>
    $<TARGET_OBJECTS:mmdb_storage>
    $<TARGET_OBJECTS:mmdb_utility>
)
target_link_libraries(DtMmdb PRIVATE mmdb_build_options ${LMDB_LIBRARY})
set_target_properties(DtMmdb PROPERTIES VERSION 2.1.0 SOVERSION 2)
target_link_options(DtMmdb PRIVATE -Wl,--no-undefined)
install(TARGETS DtMmdb LIBRARY DESTINATION lib)
