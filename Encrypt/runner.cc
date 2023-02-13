//general, useful includes
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//inlcudes for files
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

//personal file includes
#include "crypt.cc"

using namespace std;

int fileExists(const string& file) { // method to make my life easier when checking files
    ifstream fOpen(file);
    if (fOpen.fail()) {
        // cerr << "File " << file << " could not be opened\n";
        return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 6) cerr << "Wrong number of arguments. Looking for 5, found " << argc - 1 << "\n";


    if (*argv[1] != 'B' && *argv[1] != 'S' && *argv[1] != 'b' && *argv[1] != 's') { cerr << "First argument must be either \'B\' or \'S\'. Found: \'" << argv[1] << "\'.\n"; return -1;}
    if (*argv[5] != 'E' && *argv[5] != 'D' && *argv[5] != 'e' && *argv[5] != 'd') { cerr << "Fifth argument must be either \'E\' or \'D\'. Found: \'" << argv[5] << "\'.\n"; return -1;}
    if (fileExists(argv[2]) < 0) {
        cerr << "Input file does not exist. Exiting with error...\n";
        return -1;
    }
    if (fileExists(argv[4]) < 0) {
        cerr << "Key file does not exist. Exiting with error...\n";
        return -1;
    }
    // if (fileExists(argv[3]) < 0);// cout << "No output file with the name " << argv[2] << " exists. Creating one now...\n";

    string input_file;
    string output_file;
    string key_file;
    string string_for_type = argv[1];
    string string_for_encdec = argv[5];

    // cout << "Checking file 1\n";
    ifstream open_file(argv[2]);
    if(open_file.peek() == EOF){
        ofstream output_file(argv[3]);
        return 0;
    }
    // cout << "Checking file 2\n";
    ifstream open_file2(argv[4]);
    if(open_file2.peek() == EOF){
        cerr << "Key file is empty!\n";
        return -1;
    }
    // cout << "Check files was successful\n";

    enums::block_stream bs = enums::STREAM;
    enums::encdec ed = enums::DECRYPT;
    // cout << "Checking type and mode\n";
    string bsmode = argv[1];
    if (bsmode == "B" || bsmode == "b")
        bs = enums::BLOCK;
    
    // cout << "Comparing " << bs << " against " << "E and e\n";
    string type = argv[5];
    if (type == "E" || type == "e") {
        // cout << "Found an E in the area for it and now I am changing it\n";
        ed = enums::ENCRYPT;
    }

    if (bs == enums::BLOCK) {
        // cout << "Running block\n";
        ifstream fOpen(argv[4]);
        char z;
        string keyTemp;
        // cout << "Opened file\n";
        while(fOpen.get(z)){
            // cout << "getting key\n";
            keyTemp += z;
        }
        // cout << "finished loop\n";

        if(keyTemp.size() != 16){ // HAS TO TAKE INTO ACCOUNT FOR NEWLINE
            cerr << "Key size is incorrect! Found size to be: " << keyTemp.size() << " and found the key to be " << keyTemp << "\n";
            return -1;
        }
    }

    crypt test;
    // cout << "Starting process...\n";
    // cout << "Process contains arguments passed, type: " << bs << ", mode: " << ed << "\n";
    test.crypt::start(argv, bs, ed);
    return 0;





}