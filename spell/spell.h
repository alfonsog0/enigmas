/* you may assume a maximum word length of 512 characters*/
#define MAX_LENGTH 512

/* insert your function prototypes here */

/* takes as its parameter a target
word and which returns the number of times the target word appears in the corpus (by
looking this up in words.dat). If the word cannot be found in words.dat then the function
should return 0.*/
int frequency(const char* target);