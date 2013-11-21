#include <util/type.h>
#include <sys/socket.h>

#ifndef UTIL_RPC_CLIENT_H_
#define UTIL_RPC_CLIENT_H_

namespace adv_db_proj_util {

/**
 * RPC is adopt to make the communication.
 * TM will use RPCClient to call the DM functions with different RPC_t
 **/
class RPCClient {
    public:
        /**
         * input:   sockaddr_in addr // server address
         **/
        RPCClient (sockaddr_in addr);

        virtual ~RPCClient ();

        /**
         * input:   RPC_t proc  // procedure call id
         * input:   a*          // input arguments
         * output:  r
         **/
        template<class R, class A1>
        int call (RPC_t proc, const A1 &a1, R &r);

        template<class R, class A1, class A2>
        int call (RPC_t proc, const A1 &a1, const A2 &a2, R &r);

        template<class R, class A1, class A2, class A3>
        int call (RPC_t proc, const A1 &a1, const A2 &a2, const A3 &a3, R &r);

        template<class R, class A1, class A2, class A3, class A4>
        int call (RPC_t proc, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, R &r);
};

}

#endif
