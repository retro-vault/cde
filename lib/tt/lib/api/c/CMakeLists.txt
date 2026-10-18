add_library(tt_api OBJECT
    api_api.C
    api_auth.C
    api_default.C
    api_error.C
    api_file.C
    api_filemap.C
    api_handle.C
    api_message.C
    api_mp.C
    api_mp_io.C
    api_mp_otype.C
    api_objid_spec.C
    api_pattern.C
    api_session_prop.C
    api_spec.C
    api_spec_map_ref.C
    api_storage.C
    api_typecb.C
    api_typecb_utils.C
    api_utils.C
    api_xdr.C
)
target_link_libraries(tt_api PRIVATE tt_build_options)
set_target_properties(tt_api PROPERTIES POSITION_INDEPENDENT_CODE ON)
