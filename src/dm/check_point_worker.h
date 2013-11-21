#ifndef DM_CHECK_POINT_WORKER_H_
#define DM_CHECK_POINT_WORKER_H_

namespace adv_db_proj_dm {

/**
 * Reorganize log on the disk, make checkpoint for recovery
 * Running as a single thread aside the main program.
 **/
class CheckPointWorker {
    public:
        /**
         * Periodically execute in a while loop.
         *
         * Dump current committed data into stable storage,
         * remove all previous committed log (named as: cm{timestamp})
         **/
        static void work ();
};

}

#endif
