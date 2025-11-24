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

void apply_modifier(ScoreModifier score_modifier, const char* played_tiles, int index, int& score) {
    switch (score_modifier)
    {
    case NONE:
        return;
    case DOUBLE_LETTER_SCORE:
        score += tile_score(played_tiles[index]);
        break;
    case TRIPLE_LETTER_SCORE:
        score += (tile_score(played_tiles[index]) * 2);
        break;
    case DOUBLE_WORD_SCORE:
        score *= 2;
        break;
    case TRIPLE_WORD_SCORE:
        score *= 3;
        break;
    default:
        break;
    }
}

int compute_score(const char* played_tiles, ScoreModifier score_modifiers[]) {
    const char* played_tiles_ptr = played_tiles;
    // compute len of the array played tiles
    size_t len = strlen(played_tiles);
    
    int total = 0;
    // loop through played tiles and for every tile compute score and add score modifier values
   for (int letter = 0; letter < len; letter++) {
        total += tile_score(*played_tiles_ptr);
        played_tiles_ptr++;
    } 
    for (int mod = 0; mod < len; mod++) {
        apply_modifier(score_modifiers[mod], played_tiles, mod, total);
    }
    if (len >= 7) {
        total += 50;
    }
    return total;
}