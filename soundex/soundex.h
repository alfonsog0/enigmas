/* input: letter
    output: soundex encoding number */
char letter_to_soundex(const char letter);

/* produces the Soundex encoding
corresponding to a given surname. The first parameter to the function (i.e. surname) is
an input string containing the surname that should be encoded. The second parameter
(i.e. soundex) is an output string into which the Soundex encoding for the string should
be placed. */
void encode(const char* surname, char* soundex);

/* compares two Soundex codes
(where one and two are strings representing the Soundex codes being compared). If the
Soundex codes are the same, the function should return 1, else it should return 0. */
int compare(const char* one, const char* two);

/* returns the number of words in a
given sentence that have the same Soundex encoding as the given surname.
For example, the function call
count("Leeson", "Linnings, Leasonne, Lesson and Lemon.")
should return the value 2. */
int count(const char* surname, const char* sentence);