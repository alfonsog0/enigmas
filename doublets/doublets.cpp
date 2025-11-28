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

bool display_chain(const char* chain[], ostream& output_stream) {
   // malformed input
   if (chain == nullptr) return false;

   int len = 0;
   while (chain[len] != NULL) len++;

   for (int i = 0; i < len; i++) {
      const char* word = chain[i];

      // if NULL appears before the end -> malformed chain
      if (word == NULL) return false;

      if (i == 0 || i == len - 1) {
         output_stream << word;
      } else {
         for (int j = 0; word[j] != '\0'; j++) {
            output_stream << char(tolower(word[j]));
         }
      }
      output_stream << endl;
   }
   return true;
}

bool valid_chain(const char* chain[]) {
   int len = 0;
   while(chain[len] != NULL) len++;

   // chain must have at least 3 words
   if (len < 2) return false;

   for (int i = 0; i < len - 1; i++) {
      if(!valid_step(chain[i], chain[i+1])) return false;
      // chack repeated words
      if (strcmp(chain[i], chain[i+1]) == 0) return false;
   }
   return true;
}

void get_neighbours(const char* current_word, char neighbours[][MAX_WORD_LEN + 1], int& count) {
   count = 0;

   int len = strlen(current_word);
   if (len > MAX_WORD_LEN) return;  // safety

   char buffer[MAX_WORD_LEN + 1];

   for (int i = 0; i < len; i++) {
      strcpy(buffer, current_word);
      char original = buffer[i];

      for (char letter_option = 'A'; letter_option <= 'Z'; letter_option++){
         if (letter_option == original) continue;

         buffer[i] = letter_option;
         if (dictionary_search(buffer)) {
            strcpy(neighbours[count], buffer);
            count++;
         }
      }
   }
}

bool dfs(const char* current, const char* target) {
   // base case
   if (strcmp(current, target) == 0) return true;
   char neighbours[MAX_NEIGHBOURS][MAX_WORD_LEN + 1];
   int count = 0;
   get_neighbours(current, neighbours, count);
   for (int i = 0; i < count; i++) {
      if (dfs(neighbours[i], target)) {
         return true;
      }
   }
   return false;
}

bool dfs(const char* current, const char* target, int remaining_steps) {
   if (remaining_steps <= 0) return false;
   // base case
   if (strcmp(current, target) == 0) return true;
   char neighbours[MAX_NEIGHBOURS][MAX_WORD_LEN + 1];
   int count = 0;
   get_neighbours(current, neighbours, count);
   for (int i = 0; i < count; i++) {
      if (dfs(neighbours[i], target, remaining_steps - 1)) {
         return true;
      }
   }
   return false;
}

bool dfs(const char* current, const char* target, char answer_chain[][MAX_WORD_LEN + 1], int current_len, int remaining_steps) {
   // base case
   if (strcmp(current, target) == 0) return true;
   if (remaining_steps <= 0) return false;

   char neighbours[MAX_NEIGHBOURS][MAX_WORD_LEN + 1];
   int count = 0;
   get_neighbours(current, neighbours, count);


   for (int i = 0; i < count; i++) {
      bool already_checked = false;
      for (int j = 0; j < current_len; j++) {
         if (strcmp(neighbours[i], answer_chain[j]) == 0) 
            already_checked = true;
      }
      if (!already_checked) {
         strcpy(answer_chain[current_len], neighbours[i]); 
         if (dfs(neighbours[i], target, answer_chain, current_len + 1 , remaining_steps - 1)) {
            return true;
         }
      }
   }
   return false;
}

bool find_chain(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps) {
   //char answer_chain_ch[max_steps][MAX_WORD_LEN+1];
   strcpy(chain_storage[0], start_word);
   // clear it and make unused rows null terminated
   for (int i = 1; i < MAX_CHAIN_LEN; i++) {
      chain_storage[i][0] = '\0';
   }

   bool ok = dfs(start_word, target_word, chain_storage, 1, max_steps);

   if (!ok) return false;

   int len = 0;
   while (len < MAX_CHAIN_LEN && chain_storage[len][0] != '\0') len++;

   for (int i = 0; i < len; i++) {
      answer_chain[i] = chain_storage[i];
   }
   answer_chain[len] = NULL;

   return true;
}