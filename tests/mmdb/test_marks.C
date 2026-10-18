#include "oliasdb/mmdb.h"
#include "oliasdb/mark.h"
#include <cstdio>
#include <cstring>

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }
    INIT_EXCEPTIONS();
    mtry {
        OLIAS_DB database;
        {
            mark_base base(argv[1], "mark_base", "", user_base::WRITE);
            if (base.open_status() != user_base::SUCC) {
                std::fprintf(stderr, "Cannot create writable marks database\n");
                return 1;
            }
            mark_smart_ptr mark(&base, "CDE.USERSGUIDE.TOC");
            mark.update_usermark("saved bookmark", 14);
        }
        {
            mark_base base(argv[1], "mark_base", "", user_base::WRITE);
            if (base.open_status() != user_base::SUCC) {
                std::fprintf(stderr, "Cannot reopen marks database\n");
                return 1;
            }
            mmdb_pos_t position = base.first();
            if (!position) {
                return 1;
            }
            mark_smart_ptr mark(&base, base.get_mark_oid(position));
            if (std::strcmp(mark.node_locator(), "CDE.USERSGUIDE.TOC") != 0 ||
                    mark.mark_value()->size() != 14 ||
                    std::memcmp(mark.mark_value()->get(), "saved bookmark", 14) != 0) {
                std::fprintf(stderr, "Saved bookmark did not survive closing the database\n");
                return 1;
            }
        }
    }
    mcatch_any() {
        std::fprintf(stderr, "Marks database raised an exception\n");
        return 1;
    } end_try;
    return 0;
}
