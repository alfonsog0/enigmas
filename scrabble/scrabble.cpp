#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */
int tile_score(char letter) {
    switch (toupper(letter)) {
    case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U':
        return 1;
    case 'D': case 'G':
        return 2;
    case 'B': case 'C': case 'M': case 'P':
        return 3;
    case 'F': case 'H': case 'V': case 'W': case 'Y':
        return 4;
    case 'K':
        return 5;
    case 'J': case 'X':
        return 8;
    case 'Z': case 'Q':
        return 10;
    case ' ': case '?':
        return 0;    
    default:
        return -1;
    }
}

bool can_form_word_from_tiles(char* word, char* tiles, char* played_tiles) {
    char* word_ptr = word;
    char tiles_copy[80];
    strcpy(tiles_copy, tiles);
    
    // base case
    if (*word_ptr == '\0') {
        *played_tiles = '\0';
        return true;
    }
    int bonus = 0;
    char* tiles_ptr1 = tiles;
    while (*tiles_ptr1 != '\0') {
        if (*tiles_ptr1 == '?') {
            bonus++;
        }
        tiles_ptr1++;
    }

    if (*word_ptr != '\0') {
        char* tiles_ptr = tiles_copy;
        while (*tiles_ptr != '\0' && *word_ptr != '\0') {
            if (*word_ptr == *tiles_ptr) {
                // make the used tile unavail for next turns
                *tiles_ptr = '*';

                *played_tiles = *word_ptr;
                bool ok = can_form_word_from_tiles(word + 1, tiles_copy, played_tiles + 1);
                if (ok) return true;
            } 
            tiles_ptr++;
        }
        if (*tiles_ptr == '\0' && bonus > 0) {
            // make the used tile unavail for next turns
            *tiles_ptr = '*';
            *played_tiles = '?';
            char* tiles_ptr2 = tiles_copy;
            while (*tiles_ptr2 != '\0') {
                if (*tiles_ptr2 == '?') {
                    *tiles_ptr2 = '*';
                }
                tiles_ptr2++;
            }
            bool ok1 = can_form_word_from_tiles(word + 1, tiles_copy, played_tiles + 1);
            bonus--;
            if (ok1) return true;
        }
        return false;
    }
    *played_tiles = '\0';
    return true;
}