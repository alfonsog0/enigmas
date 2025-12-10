#ifndef MULTITAP_H
#define MULTITAP_H

const char* letter_code(char c);

const char* punctuation_code(char c);

int encode_character(char ch, char* multitap);

void encode(const char* plaintext, char* multitap);

#endif
