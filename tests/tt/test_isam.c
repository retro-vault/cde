#include "isam_impl.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "line %d: %s (iserrno=%d)\n", __LINE__, #expr, iserrno); \
    return EXIT_FAILURE; \
} } while (0)

int main(void)
{
    char encoded[24];
    char directory[] = "isam-XXXXXX";
    char path[128];
    char record[32] = "0001first record";
    char result[32];
    struct keydesc key = {0};
    int fd;

    memset(encoded, 0x55, sizeof(encoded));
    CHECK(stfloat(1.25f, encoded + 1) == 0);
    CHECK((unsigned char)encoded[0] == 0x55);
    CHECK((unsigned char)encoded[5] == 0x55);
    CHECK(ldfloat(encoded + 1) == 1.25f);
    CHECK(stdbl(-1.25, encoded + 1) == 0);
    CHECK(lddbl(encoded + 1) == -1.25);
    CHECK(stlong(INT32_MAX, encoded + 1) == 0);
    CHECK(ldlong(encoded + 1) == INT32_MAX);
    CHECK(stlong(-1, encoded + 1) == 0);
    CHECK(ldlong(encoded + 1) == -1);
    CHECK(mkdtemp(directory) != NULL);
    CHECK(snprintf(path, sizeof(path), "%s/records", directory) > 0);
    key.k_nparts = 1;
    key.k_start = 0;
    key.k_leng = 4;
    key.k_type = CHARTYPE;
    fd = isbuild(path, sizeof(record), &key, ISINOUT | ISEXCLLOCK);
    CHECK(fd >= 0);
    CHECK(iswrite(fd, record) == 0);
    CHECK(iswrite(fd, record) == -1 && iserrno == EDUPL);
    CHECK(isclose(fd) == 0);
    fd = isopen(path, ISINOUT | ISEXCLLOCK);
    CHECK(fd >= 0);
    memset(result, 0, sizeof(result));
    CHECK(isread(fd, result, ISFIRST) == 0);
    CHECK(memcmp(record, result, sizeof(record)) == 0);
    CHECK(isread(fd, result, ISNEXT) == -1 && iserrno == EENDFILE);
    /* Force multi-page indexes, redistribution, and merging on deletion. */
    for (int i = 999; i >= 0; --i) {
        memset(record, 0, sizeof(record));
        snprintf(record, sizeof(record), "%04dindexed record", i);
        CHECK(iswrite(fd, record) == 0 || (i == 1 && iserrno == EDUPL));
    }
    for (int i = 1; i < 1000; i += 2) {
        snprintf(record, sizeof(record), "%04d", i);
        CHECK(isread(fd, record, ISEQUAL) == 0);
        CHECK(isdelcurr(fd) == 0);
    }
    CHECK(isclose(fd) == 0);
    fd = isopen(path, ISINOUT | ISEXCLLOCK);
    CHECK(fd >= 0);
    for (int i = 0; i < 1000; i += 2) {
        char expected[5];
        snprintf(expected, sizeof(expected), "%04d", i);
        CHECK(isread(fd, result, i == 0 ? ISFIRST : ISNEXT) == 0);
        CHECK(memcmp(expected, result, 4) == 0);
    }
    CHECK(isread(fd, result, ISNEXT) == -1 && iserrno == EENDFILE);
    for (int i = 998; i >= 0; i -= 2) {
        snprintf(record, sizeof(record), "%04d", i);
        CHECK(isread(fd, record, ISEQUAL) == 0);
        CHECK(isdelcurr(fd) == 0);
    }
    CHECK(isread(fd, result, ISFIRST) == -1 && iserrno == EENDFILE);
    CHECK(isclose(fd) == 0);
    CHECK(iserase(path) == 0);
    CHECK(rmdir(directory) == 0);
    return EXIT_SUCCESS;
}
