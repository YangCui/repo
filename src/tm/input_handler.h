#ifndef TM_INPUT_HANDER_H_
#define TM_INPUT_HANDER_H_

namespace adv_db_proj_tm {

/**
 * Used to get input command for TM. This class is singleton.
 **/
class InputHandler {
    public:
        virtual ~InputHandler ();

        /**
         * return:  status_t
         *      SUCCESS:    successfully read a line from stream_
         *      N_END:      reach the EOF
         *
         * Read one line from stream_, parse the line to several opera-
         * tions, push each operation into corresponding transaction's
         * operation queue by calling:
         *     Transaction::push_operation(operation_t *operation);
         **/
        status_t get_one_step ();

        /**
         * return:  InputHandler *  // pointer to single instance.
         **/
        static InputHandler * get_instance ();

        /**
         * Delete the instance.
         **/
        static void delete_instance ();
    private:
        /**
         * input:   char *file      // input file path, NULL for stdin
         **/
        InputHandler (char *file);

        FILE *stream_; /** input stream, file handler to get input */

        static InputHandler *input_handler_;
};

}

#endif
