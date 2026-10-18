find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(ol_data OL_DataExpr.yy ${CMAKE_CURRENT_BINARY_DIR}/OL_DataExpr.C DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/OL_DataExpr.tab.h COMPILE_FLAGS "-p ol_data")
FLEX_TARGET(ol_content ContentType.ll ${CMAKE_CURRENT_BINARY_DIR}/ContentType.C COMPILE_FLAGS "-Cf -L -8 -s -P ol_data")
ADD_FLEX_BISON_DEPENDENCY(ol_content ol_data)
FLEX_TARGET(node_replace ReplaceIdIdref.ll ${CMAKE_CURRENT_BINARY_DIR}/ReplaceIdIdref.C COMPILE_FLAGS "-Cf -L -8 -s -P nodedata")
FLEX_TARGET(remote_id RemoteId.ll ${CMAKE_CURRENT_BINARY_DIR}/RemoteId.C COMPILE_FLAGS "-Cf -L -8 -s -P remote")
FLEX_TARGET(graphics_type gr_type.ll ${CMAKE_CURRENT_BINARY_DIR}/gr_type.C COMPILE_FLAGS "-Cf -L -8 -s -P graphics_task")
FLEX_TARGET(node_lex lex.ll ${CMAKE_CURRENT_BINARY_DIR}/lex.cc COMPILE_FLAGS "-Cf -L -8 -s")
add_custom_target(infolib_parsers DEPENDS ${BISON_ol_data_OUTPUTS} ${FLEX_ol_content_OUTPUTS} ${FLEX_node_replace_OUTPUTS} ${FLEX_remote_id_OUTPUTS} ${FLEX_graphics_type_OUTPUTS} ${FLEX_node_lex_OUTPUTS})
add_executable(MixedGen
    MixedGen.C
    AttributeList.C
    AttributeRec.C
    BTCollectable.C
    BookCaseDB.C
    DataBase.C
    FlexBuffer.C
    Handler.C
    ${CMAKE_CURRENT_BINARY_DIR}/RemoteId.C
    SGMLName.C
    StringList.C
    Token.C
)
add_dependencies(MixedGen infolib_parsers)
target_include_directories(MixedGen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(MixedGen PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(MixedGen PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(MixedGen PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS MixedGen RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(NCFGen
    NCFGen.C
    AttributeList.C
    AttributeRec.C
    BTCollectable.C
    BookCaseDB.C
    DataBase.C
    Handler.C
    SGMLName.C
    StringList.C
    StyleValidate.C
    Token.C
)
add_dependencies(NCFGen infolib_parsers)
target_include_directories(NCFGen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(NCFGen PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(NCFGen PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(NCFGen PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS NCFGen RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(NodeParser
    ${CMAKE_CURRENT_BINARY_DIR}/lex.cc
    NodeParser.C
    AttributeData.C
    AttributeList.C
    AttributeRec.C
    AusText.C
    AusTextStorage.C
    BookCaseDB.C
    BookTasks.C
    ConcatTask.C
    Content.C
    ${CMAKE_CURRENT_BINARY_DIR}/ContentType.C
    DataBase.C
    DataRepository.C
    Dispatch.C
    EntityList.C
    ExprList.C
    Expression.C
    FirstOf.C
    FlexBuffer.C
    GenericId.C
    GraphicsTask.C
    Handler.C
    LcfTask.C
    NodeData.C
    NodeTask.C
    OLAF.C
    OL_Data.C
    ${CMAKE_CURRENT_BINARY_DIR}/OL_DataExpr.C
    ${CMAKE_CURRENT_BINARY_DIR}/ReplaceIdIdref.C
    SGMLDefn.C
    SGMLName.C
    SearchEng.C
    SearchPath.C
    StringList.C
    StyleTask.C
    StyleTaskDB.C
    TOCTask.C
    Task.C
    Token.C
    ${CMAKE_CURRENT_BINARY_DIR}/gr_type.C
)
add_dependencies(NodeParser infolib_parsers)
target_include_directories(NodeParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(NodeParser PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(NodeParser PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(NodeParser PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS NodeParser RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(StyleUpdate
    ${CMAKE_CURRENT_BINARY_DIR}/lex.cc
    StyleUpdate.C
    AttributeData.C
    AttributeList.C
    AttributeRec.C
    ConcatTask.C
    Content.C
    ${CMAKE_CURRENT_BINARY_DIR}/ContentType.C
    Dispatch.C
    EntityList.C
    ExprList.C
    Expression.C
    FirstOf.C
    FlexBuffer.C
    GenericId.C
    Handler.C
    OLAF.C
    OL_Data.C
    ${CMAKE_CURRENT_BINARY_DIR}/OL_DataExpr.C
    SGMLDefn.C
    SGMLName.C
    SearchPath.C
    StyleTask.C
    StyleValidate.C
    Task.C
    Token.C
)
add_dependencies(StyleUpdate infolib_parsers)
target_include_directories(StyleUpdate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(StyleUpdate PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(StyleUpdate PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(StyleUpdate PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS StyleUpdate RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(dbdrv
    dbdrv.C
)
add_dependencies(dbdrv infolib_parsers)
target_include_directories(dbdrv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(dbdrv PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(dbdrv PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(dbdrv PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS dbdrv RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(valBase
    valBase.C
)
add_dependencies(valBase infolib_parsers)
target_include_directories(valBase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(valBase PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(valBase PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(valBase PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS valBase RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
add_executable(validator
    validator.C
)
add_dependencies(validator infolib_parsers)
target_include_directories(validator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/lib/DtMmdb ${PROJECT_BINARY_DIR}/lib/DtMmdb)
target_compile_definitions(validator PRIVATE CDE_NEXT DTSEARCH DtinfoClient EXPAND_TEMPLATES DTDCBK_DATAROOTDIR="${docbook_data}")
target_link_libraries(validator PRIVATE cde_build_options DtMmdb DtSearch DtSvc tt ${LMDB_LIBRARY})
set_target_properties(validator PROPERTIES INSTALL_RPATH "$ORIGIN/../../../../lib")
install(TARGETS validator RUNTIME DESTINATION libexec/cde/dtdocbook/infolib)
install(PROGRAMS ChangeCaseTitle DeInstallBase Librarian DESTINATION libexec/cde/dtdocbook/infolib)
