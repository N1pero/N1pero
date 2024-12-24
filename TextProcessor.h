#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>

class TextProcessor {
public:
    char* swapAdjacentWords(const char* line);
    void processFile(const char* inputFile);
    void display(const char* inputFile);
};

#endif // TEXTPROCESSOR_H
