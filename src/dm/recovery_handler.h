#include <dm/type.h>

#ifndef DM_RECOVERY_HANDLER_H_
#define DM_RECOVERY_HANDLER_H_

namespace adv_db_proj_dm {

class CacheData;
class LockProtocol;

class RecoveryHandler {
    /**
     * input:   const char *dir     // a directory path, in which to find the log
     * output:  LockProtocol **lock_protocol_ptr    // initilized LockProtocol
     *
     * Used to do the recovery.
     * First read the checkpoints file (named as: ck{timestamp})
     * Second read the uncheckpointed committed log (named as: cm{timestamp})
     * No need to read pre-committed log (named as: pc{timestamp})
     *
     **/
    static status_t log2cache (const char *dir, LockProtocol **lock_protocol_ptr);
};

}

#endif
