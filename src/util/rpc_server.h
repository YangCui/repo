#include <util/type.h>
#include <sys/socket.h>

#ifndef UTIL_RPC_SERVER_H_
#define UTIL_RPC_SERVER_H_

namespace adv_db_proj_util {

/**
 * RPCServer is used for DM respond to TM's RPC.
 * By reg the function to the RPCServer, RPCClient would
 * be able to do it. The RPCServer will create a thread
 * to execute the callee function.
 **/
class RPCServer {
    public:
        /**
         * input:   unsigned int port       // listener port
         **/
        RPCServer (unsigned int port);

        virtual ~RPCServer ();

        /**
         * Register method to RPCServer
         **/
        template<class S, class A1, class R>
        void reg(RPC_t proc, S*, int (S::*meth)(const A1 a1, R &r));

        template<class S, class A1, class A2, class R>
        void reg(RPC_t proc, S*, int (S::*meth)(const A1 a1, const A2 a2, R &r));

        template<class S, class A1, class A2, class A3, class R>
        void reg(RPC_t proc, S*, int (S::*meth)(const A1 a1, const A2 a2, const A3 a3, R &r));

        template<class S, class A1, class A2, class A3, class A4, class R>
        void reg(RPC_t proc, S*, int (S::*meth)(const A1 a1, const A2 a2, const A3 a3, const A4 a4, R &r));
};

}

#endif
