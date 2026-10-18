add_executable(rpc.ttdbserver
    db_server_functions.C
    db_server_svc.C
    dm_access_cache.C
    dm_server.C
    tt_db_message_info_utils.C
    tt_db_msg_q_lock.C
    tt_db_msg_q_lock_entry_utils.C
    tt_db_partition_global_map_ref.C
    tt_db_partition_redirection_map.C
    tt_db_server_db.C
    tt_db_server_db_utils.C
    tt_isam_file.C
    tt_isam_file_utils.C
    tt_isam_key_descriptor.C
    tt_isam_key_descriptor_utils.C
    tt_isam_record.C
    tt_isam_record_utils.C
)
target_include_directories(rpc.ttdbserver PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(rpc.ttdbserver PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS rpc.ttdbserver RUNTIME DESTINATION libexec/cde)
set_target_properties(rpc.ttdbserver PROPERTIES INSTALL_RPATH "$ORIGIN/../../lib")
