#include <iostream>
#include <cctype>
#include "playfair.h"

using namespace std;

void prepare(const char* input, char* output) {
    const char* input_ptr = input;

    int count_char = 0;
    while (*input_ptr != '\0') {
        if (isalnum(*input_ptr)) {
            *output = toupper(*input_ptr);
            output++;
        }
        input_ptr++;
        count_char++;
    }
    if (count_char % 2) {
        *output = 'X';
        output++;
    }
    *output = '\0';
}

void grid(const char* codeword, char square[6][6]) {
    // create an array containing on one row all letters and numbers and on the other a bitmap
    char alphanum[2][36];
    int counter = 0;
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        alphanum[0][letter - 'A'] = letter;
        counter++;
    }
    for (char num = '0'; num <= '9'; num++) {
        alphanum[0][counter + num - '0'] = num;
    }
    for ( int bitmap = 0; bitmap < 36; bitmap++) {
        alphanum[1][bitmap] = '0';
    }

    const char* codeword_ptr = codeword;
    char* alphanum_ptr = alphanum[0];
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            bool flag = false;
            const char* letter = nullptr;
            // when codeword was all written read from alphabet and numbers
            if (*codeword_ptr != '\0') {
                letter = codeword_ptr;
                codeword_ptr++;
            }
            else {
                letter = alphanum_ptr;
                alphanum_ptr++;
            }

            // check if it is letter or number and if it was already written
            if (isnumber(*letter)) {
                if (alphanum[1][static_cast<char>(*letter) - 22] == '0') {
                    square[r][c] = *letter;
                    alphanum[1][static_cast<char>(*letter) - 22] = '1';
                    flag = true;
                }
            }
            else if (isalpha(*letter)) {
                if (alphanum[1][static_cast<char>(*letter) - 'A'] == '0') {
                    square[r][c] = *letter;
                    alphanum[1][static_cast<char>(*letter) - 'A'] = '1';
                    flag = true;
                }
            }
            if (!flag) {
                c--;
            }
        }
    }
}

void bigram(char square[6][6], const char inchar1, const char inchar2, char& outchar1, char& outchar2) {
    int r1, c1, r2, c2;

    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            if (square[r][c] == inchar1) {
                r1 = r;
                c1 = c;
            }
            else if (square[r][c] == inchar2) {
                r2 = r;
                c2 = c;
            }
        }
    }
    
    outchar1 = square[r1][c2];
    outchar2 = square[r2][c1];
}

void encode(char square[6][6], const char* prepared, char* encoded) {

}