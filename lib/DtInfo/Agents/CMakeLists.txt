add_library(info_Agents OBJECT
    AgentMotif.C
    MessageAgentMotif.C
    IcccmAgent.C
    AnchorCanvas.C
    MarkIconMotif.C
    MarkCanvas.C
    NodePrintAgent.C
    NodeWindowAgentMotif.C
    NodeListAgentMotif.C
    NodeHistoryAgentMotif.C
    SearchResultsAgentMotif.C
    ListViewMotif.C
    SearchHistoryListViewMotif.C
    MapAgentMotif.C
    OutlineListViewMotif.C
    SearchScopeList.C
    SearchScopeAgentMotif.C
    BookTabMotif.C
    LibraryAgentMotif.C
    BookmarkEditMotif.C
    PrintPanelAgentMotif.C
    PrefAgentMotif.C
    GraphicAgentMotif.C
    HelpAgent.C
    MarkListView.C
    MarkChooser.C
    ScopeMenu.C
    UrlAgentMotif.C
    AddLibraryAgentMotif.C
)
target_link_libraries(info_Agents PRIVATE info_build_options)
target_include_directories(info_Agents PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
