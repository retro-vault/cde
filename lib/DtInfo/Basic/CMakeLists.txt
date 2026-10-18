add_library(info_Basic OBJECT
    FolioObject.C
    BitField.C
    OString.C
    FString.C
    OrderList.C
    List.C
    Atomizer.C
    HashTbl.C
    StringHash.C
    OutlineElement.C
    OutlineList.C
    TOC_Element.C
    Buffer.C
    Long_Lived.C
    NodeViewInfo.C
)
target_link_libraries(info_Basic PRIVATE info_build_options)
target_include_directories(info_Basic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
