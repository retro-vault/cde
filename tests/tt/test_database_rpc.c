#include <Tt/tt_c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(call) do { Tt_status status = (call); \
    if (status != TT_OK) { \
        fprintf(stderr, "%s: %s\n", #call, tt_status_message(status)); \
        return EXIT_FAILURE; \
    } \
} while (0)

int main(int argc, char **argv)
{
    char *client, *object, *property;
    FILE *file;

    if (argc != 2 || (file = fopen(argv[1], "w")) == NULL) {
        return EXIT_FAILURE;
    }
    fclose(file);
    client = tt_open();
    CHECK(tt_ptr_error(client));
    char *session = tt_default_session();
    CHECK(tt_ptr_error(session));
    CHECK(tt_session_types_load(session, TEST_OBJECT_TYPES));
    tt_free(session);
    object = tt_spec_create(argv[1]);
    CHECK(tt_ptr_error(object));
    CHECK(tt_spec_type_set(object, "CdePortTestObject"));
    CHECK(tt_spec_prop_set(object, "CdePortTest", "persistent"));
    CHECK(tt_spec_write(object));
    property = tt_spec_prop(object, "CdePortTest", 0);
    CHECK(tt_ptr_error(property));
    if (strcmp(property, "persistent") != 0) {
        fprintf(stderr, "ToolTalk database lost the object property\n");
        return EXIT_FAILURE;
    }
    tt_free(property);
    CHECK(tt_spec_destroy(object));
    tt_free(object);
    tt_free(client);
    CHECK(tt_close());
    remove(argv[1]);
    return EXIT_SUCCESS;
}
