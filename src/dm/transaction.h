#include <util/type.h>
#include <dm/type.h>
#include <dm/cache_data.h>
#include <dm/lock_protocol.h>

#include <string>

#ifndef DM_TRANSACTION_H_
#define DM_TRANSACTION_H_

namespace adv_db_proj_dm {

/**
 * A transaction instance represents an ongoing transaction.
 * Each has its own CacheData tmp_data_. Every uncommitted
 * write will happen in the tmp_data_. At precommit time,
 * all data item in tmp_data_ will be dump to a disk file
 * named as: pm{timestamp}. At commit time, the file name
 * will be changed to cm{timestamp}, and the main_cache_data_
 * will be written using tmp_data_ by calling tmp_data_.commit
 *
 **/
class Transaction {
    public:
        /**
         * input:   std::string key     // key of the variable to read
         * output:  int &value          // value read
         * return:  LockProtocol::lock_status_t
         *      SUCCESS // read done
         *      DIE     // transaction should be stopped
         *      WAIT    // allow to wait
         *
         * Read value from variable key
         **/
        public LockProtocol::lock_status_t read (std::string key, int &value);

        /**
         * input:   std::string key     // key of the variable to write
         * input:   int value           // value to write
         * input:   bool is_replicated  // is the value replicated
         * return:  LockProtocol::lock_status_t
         *      LockProtocol::SUCCESS // write done
         *      LockProtocol::DIE     // transaction should be stopped
         *      LockProtocol::WAIT    // allow to wait
         *
         * Write value to a variable
         **/
        public LockProtocol::lock_status_t write (std::string key, int value, bool is_replicated);

        /**
         * return:  status_t
         *      SUCCESS
         *      FAIL
         *
         * Dump tmp_data_ to disk file named as: pm{timestamp}
         **/
        public status_t precommit ();

        /**
         * return:  status_t
         *      SUCCESS
         *      FAIL
         *
         * Mv precommitted disk file to: cm{timestmap}, call tmp_data_.commit()
         * to commit data to main_cache_data_
         **/
        public status_t commit ();

    private:
        /** uncommitted write operations */
        CacheData tmp_data_;
        /** transaction id */
        adv_db_proj_util::tid_t tid_;
        /** creation timestamp */
        adv_db_proj_util::timestamp timestamp_;
        /** whether transaction is READ ONLY */
        bool is_RO;
};

}

#endif
