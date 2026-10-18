# Internal headers keep the historical namespace for imported source. Only
# include/ contains the public API and is eligible for SDK installation.
add_library(cde_private_headers INTERFACE)
target_include_directories(cde_private_headers INTERFACE
    ${PROJECT_SOURCE_DIR}/lib/DtHelp/include
    ${PROJECT_SOURCE_DIR}/lib/DtHelp/include/Dt
    ${PROJECT_SOURCE_DIR}/lib/DtHelp/include/DtI
    ${PROJECT_SOURCE_DIR}/lib/DtSvc/include
    ${PROJECT_SOURCE_DIR}/lib/DtSvc/include/Dt
    ${PROJECT_SOURCE_DIR}/lib/DtSvc/include/SPC
    ${PROJECT_SOURCE_DIR}/lib/DtWidget/include
)
