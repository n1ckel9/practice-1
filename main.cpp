#include <iostream>
#include <fstream>
#include <cstring>
namespace {

const char* kWordArg = "--word";
const char* kFileArg = "--file";
const int kMaxWordLength = 32;
const int kBufferSize = 4096;

bool stringEquals(const char* first, const char* second) {
    return std::strcmp(first, second) == 0;
}

bool parseArgs(int argc, char** argv, char** word, char** filename) {

    bool wordProvided = false;
    bool fileProvided = false;
    for (int i = 1; i < argc; i++) {
        if (stringEquals(kWordArg, argv[i])) {
            if (i + 1 < argc) {
                *word = argv[++i];
                wordProvided = true;
            }
            else {
                std::cerr << "Error: Missing value for --word\n";
                return false;
            }
        }
        else if (stringEquals(kFileArg, argv[i])) {
            if (i + 1 < argc) {
                *filename = argv[++i];
                fileProvided = true;
            }
            else {
                std::cerr << "Error: Missing value for --file\n";
                return false;
            }
        }
        else {
            std::cerr << "Error: Unknown argument: " << argv[i] << "\n";
            return false;
        }
    }
    return wordProvided && fileProvided;
}

int countWords(const char* filename, const char* word) {
    std::fstream file(filename, std::ios::in);
    if (!file.is_open()) {
        return -1;
    }
    int count = 0;
    char buffer[kBufferSize];

    bool matches[kMaxWordLength] = {false};

    while (file.read(buffer, kBufferSize) || file.gcount() > 0) {
        int bytes_read = file.gcount();
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || buffer[i] == ' ') {
                int ind = 0;
                bool flag = true;
                while (word[ind] != '\0') {
                    flag = flag && matches[ind];
                    ind++;
                }
                if (flag) {
                    count++;
                }
                for (int j = 0; j < kMaxWordLength; j++) {
                    matches[j] = false;
                }
                continue;
            }
            int ind = 0;
            while (word[ind] != '\0') {
                if (word[ind] == buffer[i]) {
                    matches[ind] = true;
                    break;
                }
                ind++;
            }
        }

    }
    return count;
}

}
int main(int argc, char** argv) {
    char* word;
    char* file_name;
    
    if (!parseArgs(argc, argv, &word, &file_name)) {
        std::cerr << "Error: Incorrect usage! Use " << argv[0] << 
        " --file <file name> --word <word> ";
        return 1;
    }
    
    //std::cout << word << " " << file_name;

    if (std::strlen(word) > 32) {
        std::cerr << "Error: Invalid word length. Max length is 32 symbols";
        return 3;
    }

    int count = countWords(file_name, word);

    if (count < 0) {
        std::cerr << "Error: File not opened!";
        return 2;
    }

    std::cout << count;

    
    return 0;
}
