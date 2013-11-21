#include <dm/type.h>
#include <util/type.h>

#ifndef DM_DISPATCHER_H_
#define DM_DISPATCHER_H_

namespace adv_db_proj_dm {

/**
 * All the member functions will be registered in RPCServer.
 * When called, the function will wrap to class Transaction
 * member functions normally to finish the operation.
 **/
class Dispatcher {
    public:
        static int begin (adv_db_proj_util::tid_t tid, adv_db_proj_util::timestamp timestamp, int &r);

        static int beginRO (adv_db_proj_util::tid_t tid, adv_db_proj_util::timestamp timestamp, int &r);

        static int read (adv_db_proj_util::tid_t tid, char *key, int &r);

        static int write (adv_db_proj_util::tid_t tid, char *key, int value, bool is_replicated, int &r);

        static int dump_site (char **r);

        static int dump_value (char *key, int &r);

        static int precommit (adv_db_proj_util::tid_t tid, int &r);

        static int commit (adv_db_proj_util::tid_t tid, int &r);
};

}

#endif
