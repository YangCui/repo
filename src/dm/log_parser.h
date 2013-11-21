#include <dm/type.h>

#ifndef DM_LOG_PARSER_H_
#define DM_LOG_PARSER_H_

namespace adv_db_proj_dm {

class LogParser {
    /**
     * input:   item_t item
     * output:  char **log
     * return:  status_t
     *      SUCCESS
     *      FAIL
     *
     * Transfer item_t to a char array, so as to put it into stable storage
     **/
    static status_t item2log (item_t item, char **log);

    /**
     * input:   char *log
     * output:  item_t &item
     * return:  status_t
     *      SUCCESS
     *      FAIL
     *
     * Parse log in stable storage to item_t
     **/
    static status_t log2item (const char *log, item_t &item);
};

}

#endif
