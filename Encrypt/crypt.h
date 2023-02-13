#include "enums.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class crypt {
    public:
    std::string input;
    std::string key;

        void start(char **argv, const enums::block_stream& block_stream, const enums::encdec& encdec);
        void begin_enc_block(char **argv);
        void begin_dec_block(char **argv);
        void swap();
        void xOr();


        void begin_stream(char **argv);
        void set_key(const std::string& file);

        void getInput(const std::string& file) { // gets the input from whatever is paseed to it and places it in global "input"
            char z;
            std::ifstream is(file);
            while(is.get(z)) {
                input += z;
                // std::cout << "Fuck you\n";
            }

        } //MAY NEED SEMICOLON HERE

        void remove_extra_characters();
        void add_extra_characters();

        void write(const std::string& file);
        
};


// ./test B input.txt output.txt key.txt E