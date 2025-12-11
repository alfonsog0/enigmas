#include <iostream>
#include "spell.h"
#include <fstream>
#include <string>

using namespace std;

/* insert your function definitions here */
int frequency(const char* target) {
    // open words.dat
    ifstream input("words.dat");
    string word;
    int number;

    // loop through the file getting the lines
    while (input >> number >> word) {
        // check if the sencond word in the line matches the target
        if (word == target) {
            // if it does return the first part of the line
            return number;
        }   
    }
    // loop reads every line without finding target --> return 0
    return 0;
}