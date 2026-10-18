add_executable(term_line_to_data util/lineToData.c)
target_include_directories(term_line_to_data PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/TermPrim)
target_compile_definitions(term_line_to_data PRIVATE _DEFAULT_SOURCE)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/TermLineData.c
    COMMAND ${CMAKE_COMMAND} -DGENERATOR=$<TARGET_FILE:term_line_to_data>
        "-DGENERATOR_ARGS=-p;_DtTerm;-f;${CMAKE_CURRENT_SOURCE_DIR}/Term/TermLineData.data"
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/TermLineData.c
        -P ${PROJECT_SOURCE_DIR}/cmake/RunGenerator.cmake
    DEPENDS term_line_to_data Term/TermLineData.data VERBATIM)
add_library(DtTerm SHARED
    ${CMAKE_CURRENT_BINARY_DIR}/TermLineData.c
    Term/Term.c
    Term/TermAction.c
    Term/TermBuffer.c
    Term/TermColor.c
    Term/TermEnhance.c
    Term/TermFunction.c
    Term/TermFunctionKey.c
    Term/TermParse.c
    Term/TermParseTable.c
    Term/TermVersion.c
    TermPrim/TermPrim.c
    TermPrim/TermPrimAction.c
    TermPrim/TermPrimBuffer.c
    TermPrim/TermPrimBufferWc.c
    TermPrim/TermPrimCursor.c
    TermPrim/TermPrimDebug.c
    TermPrim/TermPrimFunction.c
    TermPrim/TermPrimLineDraw.c
    TermPrim/TermPrimParse.c
    TermPrim/TermPrimParseTable.c
    TermPrim/TermPrimParser.c
    TermPrim/TermPrimPendingText.c
    TermPrim/TermPrimRender.c
    TermPrim/TermPrimRenderMb.c
    TermPrim/TermPrimRenderFont.c
    TermPrim/TermPrimRenderFontSet.c
    TermPrim/TermPrimRenderLineDraw.c
    TermPrim/TermPrimRepType.c
    TermPrim/TermPrimScroll.c
    TermPrim/TermPrimSelect.c
    TermPrim/TermPrimSetPty.c
    TermPrim/TermPrimSetUtmp.c
    TermPrim/TermPrimSubproc.c
    TermPrim/TermPrimUtil.c
    TermPrim/TermPrimVersion.c
    TermPrim/TermPrimWMProtocols.c
    TermView/TermView.c
    TermView/TermViewMenu.c
    TermView/TermViewGlobalDialog.c
    TermView/TermViewTerminalDialog.c
    TermPrim/TermPrimGetPty-pts.c
)
target_include_directories(DtTerm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Term
    ${CMAKE_CURRENT_SOURCE_DIR}/TermPrim ${CMAKE_CURRENT_SOURCE_DIR}/TermView)
target_link_libraries(DtTerm PRIVATE cde_build_options DtSvc DtWidget)
set_target_properties(DtTerm PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(DtTerm PRIVATE -Wl,--no-undefined)
install(TARGETS DtTerm LIBRARY DESTINATION lib)
