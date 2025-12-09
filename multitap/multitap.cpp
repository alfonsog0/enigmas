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
    "7", "77", "777", "7777"
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
