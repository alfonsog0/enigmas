#include <iostream>
#include <cctype>
#include "playfair.h"

using namespace std;

void prepare(const char* input, char* output) {
    const char* input_ptr = input;

    while (*input_ptr != '\0') {
        if (isalnum(*input_ptr)) {
            *output = toupper(*input_ptr);
            output++;
        }
        input_ptr++;
    }
    *output = 'X';
    output++;
    *output = '\0';
}