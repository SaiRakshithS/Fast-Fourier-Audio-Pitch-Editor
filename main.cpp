#include "Wave.hpp"
#include "FrequencyToSound.hpp"

#include <iostream>

int main() {

    FILE* file = fopen("sound.wav", "rb");

    if ( !file ) {

        std::cout << "Couldn't open file." << std::endl;
        exit(1);
    }

    Wave wav;
    wav.extractSound(file);

    std::cout << "SampleRate: " << wav.sampleRate << std::endl;
    std::cout << "BitDepth: " << wav.bitDepth << std::endl;
    std::cout << "FileSize: " << wav.fileSize << std::endl; 

    //wav.timeIntervals();

    fclose(file);
    return 0;
}