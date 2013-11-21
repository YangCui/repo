#include <util/type.h>

#ifndef DM_TYPE_H_
#define DM_TYPE_H_

namespace adv_db_proj_dm {

typedef enum {
    SUCCESS,
    N_FOUND,
    FAIL
} status_t;

/** stored data item type */
typedef struct {
    int value;
    bool is_replicated;
    adv_db_proj_util::tid_t version; // use the transaction id as the version
} item_t;

}

#endif
