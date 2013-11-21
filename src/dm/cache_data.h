#include <dm/recovery_handler.h>
#include <dm/type.h>

#include <pthread.h>

#include <map>
#include <string>

#ifndef DM_CACHE_DATA_H_
#define DM_CACHE_DATA_H_

namespace adv_db_proj_dm {

/**
 * Each read/write transaction will hold an instance of this class, it
 * contains all uncommitted writes.
 * When a transaction wants to commit, just call commit, the writes will
 * be committed to main_cache_data_
 *
 * All available data in a site is in the static variable main_cache_data_.
 * main_cache_data_ will be initilized by friend class RecoveryHandler at
 * the begining.
 **/
class CacheData : public std::map<std::string, item_t> {
    public:
        CacheData ();

        virtual ~CacheData ();

        /**
         * commit all item_t (values) in this instance to main_cache_data_;
         * need to lock main_cache_data_mutex_ first.
         **/
        void commit ();

        /**
         * input:   const std::string key   // variable key
         * output:  item_t *item            // item value get from main_cache_data_
         * return:  status_t
         *      SUCCESS:    read value success
         *      N_FOUND:    key not found
         *
         * Used to read value from main_cache_data_, need to lock first.
         **/
        status_t read_in_main (const std::string key, item_t *item);

    private:
        /** all available data */
        static CacheData *main_cache_data_;
        /** lock for main_cache_data_ */
        static pthread_mutex_t main_cache_data_mutex_;

        /** grant access to class RecoveryHandler */
        friend class RecoveryHandler;
};

}

#endif
