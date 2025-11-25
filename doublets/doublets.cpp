#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */
bool valid_step(const char* current_word, const char* next_word) {
   // rule 2: only one letter changes
   // same lenght
   size_t len_current = strlen(current_word);
   size_t len_next = strlen(next_word);
   if (len_current != len_next) return false;

   // one letter changes
   const char* current_word_ptr = current_word;
   const char* next_word_ptr = next_word;
   int divergencies = 0;
   while (*current_word_ptr != '\0') {
      if (*current_word_ptr != *next_word_ptr) divergencies++;
      current_word_ptr++;
      next_word_ptr++;
   }
   if (divergencies != 1) return false;

   // rule 4: next_word must be present in the dict
   if (!dictionary_search(next_word)) return false;

   return true;
}