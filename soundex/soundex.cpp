#include <iostream>
#include <cctype>
#include <cstring>
#include "soundex.h"

using namespace std;

char letter_to_soundex(const char letter) {
    switch (toupper(letter)) {
    case 'B': case 'F': case 'P': case 'V':
        return '1';
    case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
        return '2';
    case 'D': case 'T':
        return '3';
    case 'L':
        return '4';
    case 'M': case 'N':
        return '5';
    case 'R':
        return '6';
    case 'A': case 'E': case 'H': case 'I': case 'O': case 'U': case 'W': case 'Y':
        return ' ';
    default:
        return ' ';
    }
}

void encode(const char* surname, char* soundex) {
    if (*surname == '\0') return;

    char* soundex_ptr = soundex;
    const char* surname_ptr = surname;
    int soundex_len = 0;
    
    // 1st letter maiusc
    *soundex_ptr = toupper(*surname_ptr);
    soundex_ptr++;
    surname_ptr++;
    soundex_len++;

    // loop from second letter to \0
    while (*surname_ptr != '\0' && soundex_len < 4) {
        const char* letter_precedent = surname_ptr - 1;
        const char* letter = surname_ptr;
        // if adjecient letters dont convert to the same number
        if (letter_to_soundex(*letter) != ' ' && letter_to_soundex(*letter) != letter_to_soundex(*letter_precedent)) {
            // convert letter
            *soundex_ptr = letter_to_soundex(*letter);
            soundex_ptr++;
            soundex_len++;
        }

        surname_ptr++;
    }
    // count length of soundex
    while (soundex_len < 4) { 
        *soundex_ptr = '0';
        soundex_ptr++;
        soundex_len++;
    }
    if (soundex_len == 4) {
        *soundex_ptr = '\0';
    }
}

int compare(const char* one, const char* two) {
	// base case
	if (*one == '\0' && *two == '\0') return 1;
	//if (*one == '\0' && *two != '\0' || *one != '\0' && *two == '\0') return 0;

	if (*one == *two) {
		if (compare(one + 1, two + 1)) return 1;
	}
	return 0;
}

int count(const char* surname, const char* sentence) {
	// encode the surname
	char soundex[5];
	encode(surname, soundex);
	char word[16];
	int word_idx = 0;
	char word_soundex[5];
	int same_soundex_counter = 0;

	// encode every word in the sentence
	const char* sentence_ptr = sentence;

	while (*sentence_ptr != '\0') {
		if (*sentence_ptr != ' ' && *sentence_ptr != ',') {
			word[word_idx] = *sentence_ptr;
			word_idx++;
		}
		else if (word_idx != 0) {
			word[word_idx] = '\0';
			word_idx = 0;
			encode(word, word_soundex);
			if (compare(soundex, word_soundex)) same_soundex_counter++;
		}
		sentence_ptr++;
	}
	return same_soundex_counter;

	// compare with what is surname encoded
}