#include "crypt.h"

//using namespace crypt;
// using namespace std;

// QUICK THOUGHT: YOU MAY NEED TO ADD CRYPT:: BEFORE ALL "INPUT"S

void crypt::start(char **argv, const enums::block_stream& block_stream, const enums::encdec& encdec) {

    // std::cout << "Checking type and mode\n";
    if (block_stream == enums::BLOCK) {
        if (encdec == enums::DECRYPT) {
            // std::cout << "Calling to decblock\n";
            crypt::begin_dec_block(argv);
        }
        else {
            // std::cout << "Calling to encblock\n";
            crypt::begin_enc_block(argv);
        }
    }
    else {
        // std::cout << "Calling to stream\n";
        crypt::begin_stream(argv);
    }
}

void crypt::begin_enc_block (char **argv) { // if the operation is a block encryption run this
    crypt::getInput(argv[2]);
    crypt::set_key(argv[4]);
    crypt::add_extra_characters();
    crypt::xOr();
    crypt::swap();
    crypt::write(argv[3]);
    // std::cout << "Complete encryption of " << argv[2] << " can be found in output file " << argv[3] << "\n";
}

void crypt::begin_dec_block (char **argv) { // if the operation is a block decryption run this
    crypt::getInput(argv[2]);
    crypt::set_key(argv[4]);
    crypt::swap();
    crypt::xOr();
    crypt::remove_extra_characters();
    crypt::write(argv[3]);
    // std::cout << "Complete decryption of " << argv[2] << " can be found in output file " << argv[3] << "\n";
}

void crypt::begin_stream (char **argv) { // if the operation is a stream cipher run this
    crypt::getInput(argv[2]);
    crypt::set_key(argv[4]);
    crypt::xOr();
    crypt::write(argv[3]);
    // std::cout << "Complete encryption of " << argv[2] << " can be found in output file " << argv[3] << "\n";
}

void crypt::swap () { // used in the block cipher to swap out the blocks
    int start = 0;
    int end = input.length() - 1;
    long unsigned int key_index = 0;

    while (start <= end) {
        if (key_index == key.size()) key_index = 0;

        if ((int)key.at(key_index) % 2 != 0) {
            char tmp = input.at(end);
            input.at(end) = input.at(start);
            input.at(start) = tmp;
            start++;
            end--;
            key_index++;
        } else {
            start++;
            key_index++;
        }
    }
}

void crypt::xOr () { // performs XOR operations on necessary bits
    char z;
    long unsigned int key_index = 0;
    char new_z;

    for (unsigned int i = 0; i < input.size(); i++) {
        if (key_index >= key.size()) key_index = 0;
        z = input.at(i);

        new_z = z ^ key.at(key_index);
        input.at(i) = new_z;
        key_index++;
    }
}

void crypt::set_key (const std::string& file) { // grab the key from the input file and place it into the global "key"
    std::ifstream fOpen(file);
    char z;
    while (fOpen.get(z)) {
        key += z;
    }
}

void crypt::add_extra_characters () {
    if (input.size() % 16 != 0) {
        unsigned int r = 16 - (input.size() % 16);
        for (unsigned int i = 0; i < r; i++) {
            input += char(129);
        }
    }
}

void crypt::remove_extra_characters () {
    char z = input.back();
    while (z == char(129)) {
        input.pop_back();
        z = input.back();
    }
}

void crypt::write (const std::string& file) {
    std::ofstream os(file);
    os << input;
}