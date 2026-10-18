add_library(DtMrm SHARED DtMrm.c)
target_include_directories(DtMrm PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtTerm/Term
    ${PROJECT_SOURCE_DIR}/lib/DtTerm/TermPrim ${PROJECT_SOURCE_DIR}/lib/DtHelp)
target_link_libraries(DtMrm PRIVATE cde_build_options DtSvc DtWidget DtHelp DtTerm DtPrint ${MRM_LIBRARY})
set_target_properties(DtMrm PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(DtMrm PRIVATE -Wl,--no-undefined)
install(TARGETS DtMrm LIBRARY DESTINATION lib)
