#ifndef MULTITAP_H
#define MULTITAP_H

const char* letter_code(char c);

const char* punctuation_code(char c);

int encode_character(char ch, char* multitap);

void encode(const char* plaintext, char* multitap);

/* takes a multitap encoded
input stream and writes a decoded plaintext version to
an output stream. The first parameter (i.e. input) is the input
stream (e.g. cin or a file input stream) and the second parameter
is the output stream (e.g. cout or a file output stream). */
void decode(ifstream& input, ofstream& output);

#endif
