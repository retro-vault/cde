add_library(info_Managers OBJECT
    MessageMgr.C
    StyleSheetMgr.C
    SearchMgr.C
    NodeMgr.C
    NodeListMgr.C
    SearchResultsMgr.C
    HistoryList.C
    MapMgr.C
    SearchScopeMgr.C
    LibraryMgr.C
    GraphicsMgr.C
    PrefMgr.C
    PrintMgr.C
    ClientEventMgrX.C
    ServiceMgrX.C
    SessionMgr.C
    WorkspaceMgr.C
    TtIpcMgr.C
    MarkMgr.C
    LocalHistoryMgr.C
    GlobalHistoryMgr.C
    InputMgrX.C
    UrlMgr.C
    CatMgr.C
    WString.C
    EnvMgr.C
)
target_link_libraries(info_Managers PRIVATE info_build_options)
target_include_directories(info_Managers PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
