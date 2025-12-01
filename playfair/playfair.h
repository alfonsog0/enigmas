#ifndef PLAYFAIR_H
#define PLAYFAIR_H
/* produces an output
string suitable for Playfair encoding from some input string
by:
 copying the alphanumerical (i.e. letters and digits) characters
(but not any space or punctuation characters) from the input
string to the output string
 making the letters in the output string all uppercase
 adding an ’X’ to the output string if it contains an odd number
of characters
The first parameter to the function (i.e. input) is a read-only
string containing an input sentence. The second parameter (i.e.
output) is the prepared output sentence. */
void prepare(const char* input, char* output);



#endif