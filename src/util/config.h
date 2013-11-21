#include <string>

#ifndef UTIL_CONFIG_H_
#define UTIL_CONFIG_H_

namespace adv_db_proj_util {

class Config {
    public:
        virtual ~Config ();

        /**
         * input:   const std::string path    // configuration file path
         * return:  Config *        // single config_ instance
         * Initialize single instance config_
         **/
        static Config *create_instance (const std::string path);

        /**
         * return:  Config *        // single config_ instance
         * get single instance config_
         **/
        static Config *get_instance ();

        /**
         * delete single instance
         **/
        static void delete_instance ();

        /**
         * input:   const std::string key     // a key in config file
         * return:  std::string     // value in config file
         *
         * Get config value for key
         **/
        std::string get_string (const std::string key);

        /**
         * input:   const std::string key     // a key in config file
         * return:  ing     // value in config file
         *
         * Get config value for key
         **/
        int get_int (const std::string key);
    private:
        Config (const std::string path);

        static Config *config_;
};

}

#endif
