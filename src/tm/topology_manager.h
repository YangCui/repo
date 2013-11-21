#include <tm/type.h>
#include <string>

#ifndef TM_TOPOLOGY_MANAGER_H_
#define TM_TOPOLOGY_MANAGER_H_

namespace adv_db_proj_tm {

/**
 * There is only one instance of this class in the entire program.
 * Single instance is ensured by Singleton Pattern. The only inst-
 * ance keeps track of all variable distributions in the sites.
 *
 * Topology will control the read balance for each site by return-
 * ing sites info in different orders.
 *
 * To get the instance:
 *     adv_db_proj_tm::TopologyManager tp
 *              = adv_db_proj_tm::TopologyManager.get_instance();
 **/
class TopologyManager {
    public:
        /**
         * input:   const std::string key       // variable id (i.e. x1, x2, ...)
         * output:  site_t ***sites             // array of sites holding value of key
         * output:  unsigned int *sites_size    // size of array
         *
         * return:  status_t
         *      SUCCESS:    found key
         *      N_FOUND:    site info of the key not found
         *
         * Note: need to free sites after using it.
         **/
        status_t get_sites (const std::string key, site_t ***sites, unsigned int *sites_size);

        virtual ~TopologyManager ();

        /**
         * return:  TopologyManager *   // pointer to single instance
         **/
        static TopologyManager * get_intstance ();

        /**
         * Delete the instance
         **/
        static void delete_instance ();

    private:
        TopologyManager ();

        static TopologyManager *topology_manager_;
};

}

#endif
