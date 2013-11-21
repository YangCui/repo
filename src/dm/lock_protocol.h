#include <util/type.h>
#include <dm/recovery_handler.h>
#include <string>
#include <map>
#include <list>

#ifndef DM_LOCK_PROTOCOL_H_
#define DM_LOCK_PROTOCOL_H_

namespace adv_db_proj_dm {

/**
 * This class is a lock manager working on DM side. Lock request on all
 * variables request will be examed by this instance.
 *
 * We are using wait-die read/write lock, where only older transaction
 * is allowed to wait for younger ones.
 *
 * Only the friend class RecoveryHandler is allowed to initialize and
 * build up the lock_map_ at the begining.
 *
 **/
class LockProtocol {
    public:
        /** lock acquire status type */
        typedef enum {
            SUCCESS,    // get lock
            DIE,        // acquiring an lock hold by older transaction, wait-die
            WAIT        // wait for the lock
        } lock_status_t;

        /**
         * input:   std::string key         // variable to lock
         * input:   adv_db_proj_util::tid_t tid     // transaction id
         * input:   adv_db_proj_util::timestamp_t timestamp     // create time
         * return:  lock_status_t
         *      SUCCESS:    get lock
         *      DIE:        wait not allowed
         *      WAIT:       wait for lock
         *
         * To acquire a read lock on variable 'key' by transaction 'tid'
         **/
        lock_status_t r_acquire (std::string key, adv_db_proj_util::tid_t tid, adv_db_proj_util::timestamp_t timestamp);

        /**
         * input:   std::string key         // variable to lock
         * input:   adv_db_proj_util::tid_t tid     // transaction id
         * input:   adv_db_proj_util::timestamp_t timestamp     // create time
         * return:  lock_status_t
         *      SUCCESS:    get lock
         *      DIE:        wait not allowed
         *      WAIT:       wait for lock
         *
         * To acquire a write lock on variable 'key' by transaction 'tid'
         **/
        lock_status_t w_acquire (std::string key, adv_db_proj_util::tid_t tid, adv_db_proj_util::timestamp_t timestamp);

        /**
         * input:   std::string key         // variable to lock
         * input:   adv_db_proj_util::tid_t tid     // transaction id
         *
         * To release a lock on variable 'key' by transaction 'tid'
         **/
        void release (std::string key, adv_db_proj_util::tid_t tid);

    private:
        typedef enum {
            UNLOCKED,
            R_LOCKED,
            W_LOCKED,
        } lock_state_t;

        /** record of each lock transaction info type */
        typedef struct lock_transaction_t_ {
            struct lock_transaction_t_ () {
                tid = (adv_db_proj_util::tid_t)0;
                timestamp = (adv_db_proj_util::timestamp_t)0;
            }
            adv_db_proj_util::tid_t tid;
            adv_db_proj_util::timestamp_t timestamp;
        } lock_transaction_t;

        /** lock state on each variable */
        typedef struct lock_item_t_ {
            struct lock_item_t_ () {
                lock_state = UNLOCKED;
            }
            /** all acquired transactions sorted by timestamp (older->younger) */
            std::list<lock_transaction_t> lock_transactions;
            lock_state_t lock_state;
        } lock_item_t;

        /** all locks on all variables */
        std::map<std::string, lock_item_t> lock_map_;

        /** mutex for access lock_map_ */
        pthread_mutex_t lock_map_mutex_;

        LockProtocol ();

        /**
         * input:   std::string key     // key of a variable
         *
         * Insert a key to build up the lock_map_ at the begining.
         **/
        void insert_key (std::string key);

        friend class RecoveryHandler;
};

}

#endif
