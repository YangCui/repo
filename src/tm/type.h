#ifndef TM_TYPE_H_
#define TM_TYPE_H_

namespace adv_db_proj_tm {

/** method exec status */
typedef enum {
    SUCCESS, // success
    N_FOUND, // key not found
    N_END,   // end of file reach
} status_t;

/** possible commands */
typedef enum {
    begin,
    beginRO,
    read,
    write,
    dump,
    dump_site,
    dump_value,
    commit
} command_t;

/** operation */
typedef struct {
    command_t command;
    std::string key;
    int value;
} operation_t;

/** site type */
typedef struct {
    char *addr;
    unsigned int port;
} site_t;

}

#endif
