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
    // for (int i = 0; i < 36; i++)
    //     cout << alphanum[0][i] << endl;

    const char* codeword_ptr = codeword;
    char* alphanum_ptr = alphanum[0];
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            bool flag = false;
            const char* letter = nullptr;
            if (*codeword_ptr != '\0') {
                letter = codeword_ptr;
                codeword_ptr++;
            }
            else {
                letter = alphanum_ptr;
                alphanum_ptr++;
            }
            if (isnumber(*letter)) {
                if (alphanum[1][static_cast<char>(*letter) - '0'] == '0') {
                    square[r][c] = *letter;
                    alphanum[1][static_cast<char>(*letter) - '0'] = 1;
                    flag = true;
                }
            }
            else if (isalpha(*letter)) {
                if (alphanum[1][static_cast<char>(*letter) - 'A'] == '0') {
                    square[r][c] = *letter;
                    alphanum[1][static_cast<char>(*letter) - 'A'] = 1;
                    flag = true;
                }
            }
            else if (!flag) {
                c--;
            }
            // while (alphanum[1][static_cast<char>(*letter) - '0'] == '0' || alphanum[1][static_cast<char>(*letter) - 'A'] == '0') {
            //     if (isnumber(*letter)) {
                
            //         square[r][c] = *letter;
            //         alphanum[1][static_cast<char>(*letter) - '0'] = 1;
            //         break;
            //     }
            //     else if (isalpha(*letter)) {
                
            //         square[r][c] = *letter;
            //         alphanum[1][static_cast<char>(*letter) - 'A'] = 1;
            //         break;
            //     }
            //     if (*(++letter) != '\0') continue;
            // }
            // if la bit map è 0
         
                //aggiungi a square

                // modifica bitmap = 1
            // else bitmap 
        }
    }
}