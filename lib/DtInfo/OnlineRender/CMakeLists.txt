add_library(info_OnlineRender OBJECT
    CanvasRenderer.C
    FeatureSupport.C
    FontCache.C
    SegClientData.C
)
target_link_libraries(info_OnlineRender PRIVATE info_build_options)
target_include_directories(info_OnlineRender PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
