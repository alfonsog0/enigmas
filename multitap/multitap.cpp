#include <iostream>
#include <fstream>
#include <cctype>
#include "multitap.h"

using namespace std;

static const char* LETTER_CODES[26] = {
    "2", "22", "222",   // a, b, c
    "3", "33", "333",   // d, e, f
    "4", "44", "444",   // g, h, i
    "5", "55", "555",   // j, k, l
    "6", "66", "666",   // ...
    "7", "77", "777", "7777",
    "8", "88", "888",
    "9", "99", "999", "9999"
};

const char* letter_code(char c) {
    c = toupper(static_cast<unsigned char>(c));
    return LETTER_CODES[c - 'A'];
}

const char* punctuation_code(char c) {
    switch (c) {
    case ' ': return "0";
    case '.': return "1";    
    case ',': return "11";
    case '!': return "111";
    case '?': return "1111";
    default: return nullptr;
    }
}

int encode_character(char ch, char* multitap) {
    char* multitap_ptr = multitap;
    if (isdigit(ch)) {
        *multitap_ptr = '*';
        multitap_ptr++;
        *multitap_ptr = ch;
        multitap_ptr++;
        *multitap_ptr = '\0';
        return 2;
    }
    if (isalpha(ch)) {
        strcpy(multitap, letter_code(ch));
        return strlen(multitap);
    }
    if (ispunct(ch) || ch == ' ') {
        strcpy(multitap, punctuation_code(ch));
        return strlen(multitap);
    }
    else 
        return 0;
}   

void encode(const char* plaintext, char* multitap) {
    const char* plaintext_ptr_front = plaintext;
    plaintext_ptr_front++;
    const char* plaintext_ptr_back = plaintext;

    char* multitap_ptr = multitap;


    // check if first one is uppercase
    if (isupper(*plaintext_ptr_back)) {
        *multitap_ptr = '#';
        multitap_ptr++;
    }

    while (*plaintext_ptr_back != '\0') {
        int size = encode_character(*plaintext_ptr_back, multitap_ptr);
        multitap_ptr += size;

        // if it's not the last character
        if(*plaintext_ptr_front != '\0') {
            // encode the forward char
            char forward_char[2];
            int size_forward = encode_character(*plaintext_ptr_front, forward_char);
            // check if the capitalisation changes (toggle) --> add '#' key
            if (isupper(*plaintext_ptr_back) && !isupper(*plaintext_ptr_front) ||
            !isupper(*plaintext_ptr_back) && isupper(*plaintext_ptr_front)) {
                *multitap_ptr = '#';
                multitap_ptr++;
            }
            
            // check if the code of consecutive letters is of the same number encoding and so needs spacing
            if (*(multitap_ptr - 1) == forward_char[0]) {
                *multitap_ptr = '|';
                multitap_ptr++;
            }
        }

        plaintext_ptr_back+=1;
        plaintext_ptr_front+=1;
    }
    *multitap_ptr = '\0';
}

