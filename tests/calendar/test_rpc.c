#include <csa/csa.h>
#include <pwd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHECK(call) do { CSA_return_code code = (call); \
    if (code != CSA_SUCCESS) { \
        fprintf(stderr, "%s returned %lu\n", #call, (unsigned long)code); \
        return EXIT_FAILURE; \
    } \
} while (0)

int main(void)
{
    struct passwd *account = getpwuid(getuid());
    char address[512];
    CSA_calendar_user user = {0};
    CSA_session_handle session;
    CSA_entry_handle entry, *entries = NULL;
    CSA_uint32 count = 0;
    CSA_attribute_value values[4] = {0};
    CSA_attribute attributes[4] = {0};
    CSA_return_code status;

    if (account == NULL || snprintf(address, sizeof(address), "%s@localhost", account->pw_name) >= (int)sizeof(address)) {
        return EXIT_FAILURE;
    }
    user.user_name = address;
    user.calendar_address = address;
    status = csa_add_calendar(NULL, &user, 0, NULL, NULL);
    if (status != CSA_SUCCESS && status != CSA_E_CALENDAR_EXISTS) {
        fprintf(stderr, "Cannot create test calendar: %lu\n", (unsigned long)status);
        return EXIT_FAILURE;
    }
    CHECK(csa_logon(NULL, &user, NULL, NULL, NULL, &session, NULL));
    attributes[0].name = CSA_ENTRY_ATTR_START_DATE;
    values[0].type = CSA_VALUE_DATE_TIME;
    values[0].item.date_time_value = "20300101T120000Z";
    attributes[1].name = CSA_ENTRY_ATTR_END_DATE;
    values[1].type = CSA_VALUE_DATE_TIME;
    values[1].item.date_time_value = "20300101T130000Z";
    attributes[2].name = CSA_ENTRY_ATTR_SUMMARY;
    values[2].type = CSA_VALUE_STRING;
    values[2].item.string_value = "CDE native calendar RPC test";
    attributes[3].name = CSA_ENTRY_ATTR_TYPE;
    values[3].type = CSA_VALUE_UINT32;
    values[3].item.uint32_value = CSA_TYPE_EVENT;
    for (size_t i = 0; i < 4; ++i) {
        attributes[i].value = &values[i];
    }
    CHECK(csa_add_entry(session, 4, attributes, &entry, NULL));
    CHECK(csa_list_entries(session, 0, NULL, NULL, &count, &entries, NULL));
    if (count != 1) {
        fprintf(stderr, "Expected one appointment, got %lu\n", (unsigned long)count);
        return EXIT_FAILURE;
    }
    CHECK(csa_free(entries));
    CHECK(csa_delete_entry(session, entry, CSA_SCOPE_ALL, NULL));
    CHECK(csa_free((CSA_buffer)(uintptr_t)entry));
    CHECK(csa_delete_calendar(session, NULL));
    return EXIT_SUCCESS;
}
