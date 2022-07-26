#include "FrequencyToSound.hpp"

//Static member, so will be initialised outside.
Logger Sine::sineLog("sineLog.log", "Class: Sine");

Sine::Sine(const float &Frequency, const float &Amplitude, const float &Duration,
    const int &SampleRate, const float &Phase, const int &BitDepth) :

    frequency(Frequency), amplitude(Amplitude), duration(Duration),
    sampleRate(SampleRate), phase(Phase), bitDepth(BitDepth) {

    offset = 2 * pi * frequency / sampleRate;
    //holdTime = {};
    sineLog.LogToFileAndConsole("Sine wave was made", info);
}

void Sine::writeAudio(std::ofstream &file) {

        //Header Chunk:
        file << "RIFF"; //ID
        file << "----"; //Size: Come back to this later
        file << "WAVE";

        //Format Chunk:
        file << "fmt ";                                 //ID
        writeToWav(file, 16, 4);                        //Size : 16
        writeToWav(file, 1, 2);                         // Compression Code : uncompressed.
        writeToWav(file, 1, 2);                         //No of channels : 1
        writeToWav(file, sampleRate, 4);                //Sample rate
        writeToWav(file, sampleRate * bitDepth / 8, 4); //SampleRate * bitDepth = "bytes per second"
        writeToWav(file, bitDepth / 8, 2);              //Block align
        writeToWav(file, bitDepth, 2);                  //Bit Depth

        //Data Chunk:
        file << "data"; //ID
        file << "----"; //Size: Come back to this later.

        int preAudioPosition = file.tellp(); // Will use this to fill size we left.

        //Audio Sample:
        int maxAmplitude = pow(2, bitDepth - 1) - 1;
        for (int i = 0; i < sampleRate * duration; i++)  {
            //holdTime.push_back(phase);

            float result = amplitude * sin(phase);
            int intVal = static_cast<int>(maxAmplitude * result);

            writeToWav(file, intVal, 2);
            phase += offset;
        }

        int postAudioPosition = file.tellp(); // Will use this to fill size we left.

        file.seekp(preAudioPosition - 4);                          //Go to 4 positions before pre audio.
        writeToWav(file, postAudioPosition - preAudioPosition, 4); // Size of audio is post - pre.

        file.seekp(4, std::ios::beg);               //Go to 4 positions after begining.
        writeToWav(file, postAudioPosition - 8, 4); // Size in Header is everything, except Header ID and Size tags, which each take 4.

        sineLog.LogToFileAndConsole("Sound wave with frequency: " + std::to_string(frequency) + " was made", info);
    }