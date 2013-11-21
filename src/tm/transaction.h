#include <tm/type.h>
#include <util/type.h>

#include <pthread.h>
#include <queue>

#ifndef TM_TRANSACTION_H_
#define TM_TRANSACTION_H_

namespace adv_db_proj_tm {

/**
 * One transaction record in the TM side is one instance of Transaction.
 * All operations from a single transaction will be executed and accumu-
 * lated in one instance. The top operation is sent to site by calling 
 * dispatch_operation
 **/
class Transaction {
    public:
        Transaction (tid_t itd, timestamp_t timestamp, bool is_RO);

        virtual ~Transaction ();

        /**
         * input:   operation_t *operation      // pointer to new operation
         *
         * Push one new operation to the operations_ queue. Each operation
         * needs to be free the destructor.
         **/
        void push_operation (operation_t *operation);

        /**
         * return:  bool
         *      true:   the transaction ends
         *      false:  the transaction does not end
         **/
        bool is_end ();

        /**
         * input:   void *transaction_ptr   // pointer to a Transaction obj
         *
         * Call transaction_ptr->dispatch_operation();
         *
         **/
        static void dispatch_operation_pthr_wrapper (void *transaction_ptr);

    private:
        /**
         * Pop an operation from the operations_ queue, and use the RPC
         * client to send the operation to the sites got from Topology-
         * Manager.
         * The output will be print to stdout.
         *
         * If an operation is blocked, do not pop the operation_ queue,
         * the operation will be retry at next time tick
         *
         * If an operation result in an abort, set is_end_ to true.
         *
         * This will be exec by different threads, use the public func-
         * tion: dispatch_operation_pthr_wrapper to do the wrapping.
         *
         **/
        void dispatch_operation();

        adv_db_proj_util::tid_t tid_; /** transaction id */
        adv_db_proj_util::timestamp_t time_; /** transaction begin time */

        std::queue<operation_t *> operations_; /** queue of operations */
        pthread_mutex_t operations_mutex_; /** mutex for access operations_ */

        bool is_RO_; /** whether this transaction is READ ONLY */
        bool is_end_; /** whether this transaction is end */
};

}

#endif
