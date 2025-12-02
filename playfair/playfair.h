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

/* produces the 6x6
Playfair square (encoding grid) corresponding to a given code
word. The first parameter to the function (i.e. codeword) is an
input string containing a code word (e.g. IMPERIAL). You may assume
that the code word consists of upper case letters and digits
only. The second parameter (i.e. square) is an output parameter
which takes the form of a two-dimensional array of characters
representing the encoding grid. */
void grid(const char* codeword, char square[6][6]);

/* encodes a single bigram (two letter pair) using
a given encoding grid. The parameters are as follows:
 square is the encoding grid to be used to encode the bigram.
 inchar1 and inchar2 are two character input parameters
making up the bigram to be encoded.
 outchar1 and outchar2 are two character output (reference)
parameters representing the encoded bigram.
For example, the code:
char playfair[6][6];
grid("IMPERIAL",playfair);
char out1, out2;
bigram(playfair,’C’,’O’,out1,out2);
should result in out1 and out2 having the values ’F’ and ’K’
respectively. */
void bigram(char square[6][6],const char inchar1, const char inchar2, char& outchar1, char& outchar2);

/* encodes a prepared input string using a given encoding grid. The
parameters are as follows:
 square is the encoding grid to be used.
 prepared is the prepared input string containing an even number
of upper case letters and/or digits.
 encoded is an output parameter containing the encoded sentence.
For example, the code:
char playfair[6][6];
grid("IMPERIAL",playfair);
char encoded[100];
encode(playfair,"COMETOTHEQUEENSTOWERAT7OCLOCKX",encoded);
should result in the string encoded having the value:
FKEMWJSJANVPENTSOWREMX8NLCKFQU */
void encode(char square[6][6], const char* prepared, char* encoded);

#endif