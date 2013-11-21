#ifndef DM_TRANSACTION_POOL_H_
#define DM_TRANSACTION_POOL_H_

namespace adv_db_proj_dm {

/**
 * TransactionPool is a singleton class, whose only instance keep all
 * ongoing transactions, one can easily get access to a transaction by
 * giving the transaction id.
 **/
class TransactionPool {
    public:
        virtual ~TransactionPool ();

        /**
         * input:   adv_db_proj_util::tid_t tid // transaction id to find
         * return:  Transaction *
         *      Success: return transaction pointer
         *      Fail:    return NULL
         * 
         * Find transaction for a given transaction id
         **/
        Transaction *get_transaction (adv_db_proj_util::tid_t tid);

        /**
         * input:   adv_db_proj_util::tid_t tid     // transaction id
         * input:   Transaction * transaction       // pointer to the transaction
         *
         * Insert a new transaction to the pool
         **/
        void insert (adv_db_proj_util::tid_t tid, Transaction * transaction);

        /**
         * input:   adv_db_proj_util::tid_t tid     // transaction id
         *
         * Remove a transaction from the pool
         **/
        void remove (adv_db_proj_util::tid_t tid);

        /**
         * return:  TransactionPool *
         *
         * Get singleton instance
         **/
        static TransactionPool *get_instance ();

        /**
         * Delete singleton instance
         **/
        static void delete_instance ();
    private:
        /** map stores all ongoing transactions */
        std::map<adv_db_proj_util::tid_t, Transaction *> transaction_map_;
        /** lock for access to transaction_map_ */
        pthread_mutex_t transaction_map_mutex_;

        TransactionPool ();

        static TransactionPool *transaction_pool_;
};

}

#endif
