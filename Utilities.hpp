#pragma once

#include <fstream>
#define pi 3.14159

inline void writeToWav(std::ofstream &file, int value, int size) {

    const char *writtenVal = reinterpret_cast<const char *>(&value);
    file.write(writtenVal, size);
}