#include "oliasdb/mmdb.h"

#include <cstdio>
#include <cstring>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 3) {
        return 1;
    }
    INIT_EXCEPTIONS();
    mtry {
        OLIAS_DB database;
        info_lib *library = database.openInfoLib(argv[1]);
        if (library == nullptr || library->num_of_bases() != 1) {
            std::fprintf(stderr, "Generated information library is incomplete\n");
            return 1;
        }
        info_base *bookcase = library->get_info_base("CDEDOC");
        if (bookcase == nullptr) {
            return 1;
        }
        node_smart_ptr contents(bookcase, "CDE.USERSGUIDE.TOC");
        const std::string locator(contents.locator());
        const std::string title(contents.long_title());
        const std::string data(contents.data(), contents.data_size());
        const char *expected_title = argc == 3 ? argv[2] : "User's Guide";
        if (title != expected_title || data.size() < 128 ||
            (argc == 2 && data.find("Preface") == std::string::npos)) {
            std::fprintf(stderr, "locator=%s title=%s bytes=%zu contents=%.200s\n",
                         locator.c_str(), title.c_str(), data.size(), data.c_str());
            return 1;
        }
    }
    mcatch(mmdbException &, error) {
        std::fprintf(stderr, "Cannot read generated information library\n");
        return 1;
    } end_try;
    return 0;
}
