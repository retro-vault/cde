#include <Tt/tt_c.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_STATUS(expr) do { Tt_status status = (expr); \
    if (status != TT_OK) { \
        fprintf(stderr, "%s: %s\n", #expr, tt_status_message(status)); \
        return EXIT_FAILURE; \
    } \
} while (0)
#define CHECK_POINTER(ptr) CHECK_STATUS(tt_ptr_error(ptr))

int main(void)
{
    char *procid = tt_open();
    char *session;
    Tt_pattern pattern;
    Tt_message message;
    Tt_message received;
    struct pollfd event;
    char *operation;

    CHECK_POINTER(procid);
    session = tt_default_session();
    CHECK_POINTER(session);
    pattern = tt_pattern_create();
    CHECK_POINTER(pattern);
    CHECK_STATUS(tt_pattern_category_set(pattern, TT_OBSERVE));
    CHECK_STATUS(tt_pattern_class_add(pattern, TT_NOTICE));
    CHECK_STATUS(tt_pattern_scope_add(pattern, TT_SESSION));
    CHECK_STATUS(tt_pattern_session_add(pattern, session));
    CHECK_STATUS(tt_pattern_op_add(pattern, "CdePortRoundtrip"));
    CHECK_STATUS(tt_pattern_register(pattern));
    CHECK_STATUS(tt_session_join(session));
    message = tt_message_create();
    CHECK_POINTER(message);
    CHECK_STATUS(tt_message_address_set(message, TT_PROCEDURE));
    CHECK_STATUS(tt_message_class_set(message, TT_NOTICE));
    CHECK_STATUS(tt_message_scope_set(message, TT_SESSION));
    CHECK_STATUS(tt_message_op_set(message, "CdePortRoundtrip"));
    CHECK_STATUS(tt_message_send(message));
    event.fd = tt_fd();
    event.events = POLLIN;
    if (poll(&event, 1, 5000) <= 0) {
        fprintf(stderr, "Timed out waiting for ToolTalk notice\n");
        return EXIT_FAILURE;
    }
    received = tt_message_receive();
    CHECK_POINTER(received);
    if (received == NULL) {
        fprintf(stderr, "No ToolTalk message received\n");
        return EXIT_FAILURE;
    }
    operation = tt_message_op(received);
    CHECK_POINTER(operation);
    if (strcmp(operation, "CdePortRoundtrip") != 0) {
        fprintf(stderr, "Unexpected ToolTalk operation: %s\n", operation);
        return EXIT_FAILURE;
    }
    tt_free(operation);
    CHECK_STATUS(tt_message_destroy(received));
    if (message != received) {
        CHECK_STATUS(tt_message_destroy(message));
    }
    CHECK_STATUS(tt_pattern_destroy(pattern));
    tt_free(session);
    tt_free(procid);
    CHECK_STATUS(tt_close());
    return EXIT_SUCCESS;
}
