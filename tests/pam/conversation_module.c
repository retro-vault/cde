#include <security/pam_modules.h>
#include <stdlib.h>
#include <string.h>

/* Exercise the application's Linux PAM conversation through a real module. */
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags,
                                  int argc, const char **argv)
{
    const void *item = NULL;
    const char *user = NULL;
    const struct pam_conv *conversation;
    struct pam_message login = {PAM_PROMPT_ECHO_ON, "Login:"};
    struct pam_message password = {PAM_PROMPT_ECHO_OFF, "Password:"};
    const struct pam_message *messages[] = {&login, &password};
    struct pam_response *responses = NULL;
    int status;
    (void)flags;

    if (argc != 1 || pam_get_user(handle, &user, NULL) != PAM_SUCCESS ||
        pam_get_item(handle, PAM_CONV, &item) != PAM_SUCCESS) {
        return PAM_AUTH_ERR;
    }
    conversation = item;
    status = conversation->conv(2, messages, &responses, conversation->appdata_ptr);
    if (status != PAM_SUCCESS) {
        return status;
    }
    status = PAM_AUTH_ERR;
    if (responses != NULL && responses[0].resp != NULL && responses[1].resp != NULL &&
        strcmp(user, argv[0]) == 0 && strcmp(responses[0].resp, user) == 0 &&
        strcmp(responses[1].resp, "test-only-password") == 0) {
        status = PAM_SUCCESS;
    }
    if (responses != NULL) {
        free(responses[0].resp);
        free(responses[1].resp);
        free(responses);
    }
    return status;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *handle, int flags,
                             int argc, const char **argv)
{
    (void)handle;
    (void)flags;
    (void)argc;
    (void)argv;
    return PAM_SUCCESS;
}
