#include <Dt/DtXinerama.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "line %d: %s\n", __LINE__, #condition); \
        return EXIT_FAILURE; \
    } \
} while (0)

int main(void)
{
    XineramaScreenInfo screens[] = {
        {0, 0, 0, 1920, 1080},
        {1, -1280, 100, 1280, 1024}
    };
    DtXineramaInfo_t info = {2, screens};
    unsigned int width = 7, height = 7, x = 7, y = 7;

    CHECK(_DtXineramaInit(NULL) == NULL);
    _DtXineramaFree(NULL);
    CHECK(!_DtXineramaGetScreen(NULL, 0, &width, NULL, NULL, NULL));
    CHECK(width == 7);
    CHECK(!_DtXineramaGetScreen(&info, 2, &width, NULL, NULL, NULL));
    CHECK(width == 7);
    CHECK(_DtXineramaGetScreen(&info, 0, &width, &height, &x, &y));
    CHECK(width == 1920 && height == 1080 && x == 0 && y == 0);
    CHECK(_DtXineramaGetScreen(&info, 1, &width, &height, &x, &y));
    CHECK(width == 1280 && height == 1024 && x == (unsigned int)-1280 && y == 100);
    CHECK(_DtXineramaGetScreen(&info, 1, NULL, NULL, NULL, NULL));
    info.numscreens = -1;
    CHECK(!_DtXineramaGetScreen(&info, 0, NULL, NULL, NULL, NULL));
    info.numscreens = 0;
    CHECK(!_DtXineramaGetScreen(&info, 0, NULL, NULL, NULL, NULL));
    info.numscreens = 2;
    info.ScreenInfo = NULL;
    CHECK(!_DtXineramaGetScreen(&info, 0, NULL, NULL, NULL, NULL));
    return EXIT_SUCCESS;
}
