#ifndef UTIL_TYPE_H_
#define UTIL_TYPE_H_

namespace adv_db_proj_util {

/** transaction id type */
typedef unsigned int tid_t;

/** timestamp type */
typedef unsigned long timestamp_t;

typedef enum {
    begin,
    beginRO,
    read,
    write,
    dump_site,
    dump_value,
    precommit,
    commit
} RPC_t;

#endif
