#include <iostream>
#include "substring.h"

using namespace std;

int substring_position(const char* sub_string, const char* string) {
    if (*sub_string == '\0') return 0;
    const char* string_ptr = string;
    const char* sub_string_ptr = sub_string;

    int index = -1;
    int counter = 0;

    while (*sub_string_ptr != '\0' && *string_ptr != '\0') {
        if (*sub_string_ptr == *string_ptr) {
            sub_string_ptr++;
            if (index == -1) {
                index = counter;
            }
        }
        else {
            index = -1;
            sub_string_ptr = sub_string;
            if (*sub_string_ptr == *string_ptr) {
                sub_string_ptr++;
                index = counter + 1;
            }
        }
        
        string_ptr++;
        counter++;
    }
    if (*sub_string_ptr != '\0') index = -1;
    return index;
}