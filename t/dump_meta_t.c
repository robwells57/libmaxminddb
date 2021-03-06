#include "MMDB.h"
#include "tap.h"
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include "test_helper.h"

int main(void)
{
    char *fname = get_test_db_fname();

    struct stat sstat;
    int err = stat(fname, &sstat);
    ok(err == 0, "%s exists", fname);

    MMDB_s *mmdb = MMDB_open(fname, MMDB_MODE_MEMORY_CACHE);
    // MMDB_s *mmdb = MMDB_open(fname, MMDB_MODE_STANDARD);
    ok(mmdb != NULL, "MMDB_open successful");
    if (mmdb) {

        MMDB_decode_all_s *decode_all;
        int err = MMDB_get_tree(&mmdb->meta, &decode_all);
        if (err == MMDB_SUCCESS) {
            if (decode_all != NULL)
                MMDB_dump(mmdb, decode_all, 0);
            MMDB_free_decode_all(decode_all);
        }
    }
    done_testing();
}
