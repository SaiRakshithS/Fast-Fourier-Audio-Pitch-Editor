#include <iostream>
#include "Wave.hpp"

//Static log file for wave class:
Logger Wave::wavLog("wavLog.log", "Class: Wave");

Wave::Wave() {

    wavLog.LogToFileAndConsole("Wave has started, editing of sound will begin", info);

    audioData = {};
    audioFourier = {};
    time = {};
    frequency = {};
    freqValPair = {};
    maximaIndices = {};
}

Wave::~Wave() {

    wavLog.LogToFileAndConsole("Wave has ended, editing of sound will stop", info);
}

void Wave::extractSound(FILE* input) {

    Header temp = WavReader(input, audioData);

    sampleRate = temp.sampleRate;
    bitDepth = temp.bitsPerSample;
    fileSize = temp.chunkSize;

    wavLog.LogToFileAndConsole("Sound Data was extracted", info);
}

void Wave::timeIntervals() {
    duration = (float) fileSize / (float) (sampleRate * bitDepth / 8);
    float delTime = duration / audioData.size();

    for (float phase = 0; phase <= duration; phase += delTime)
        time.push_back(phase);

    wavLog.LogToFileAndConsole("Time intervals from sound file were created", info);
}

void Wave::getFrequencies() {
    
    frequency = FFT(time);
    wavLog.LogToFileAndConsole("Frequencies in sound file were extracted", info);
}

void Wave::applyFFT() {

    audioFourier = FFT(audioData, false);
    wavLog.LogToFileAndConsole("Fourier Transform was applied", info);
}

void Wave::applyInverseFFT() {

    finalData = FFT(audioFourier, true);
    wavLog.LogToFileAndConsole("Inverse Fourier Transform was applied", info);
}

void Wave::writeToFile(int duration, std::ofstream& output) {

    while (finalData.size() != audioData.size())
        finalData.pop_back();

    //Header Chunk:
    output << "RIFF"; //ID
    output << "----"; //Size: Come back to this later
    output << "WAVE";

    //Format Chunk:
    output << "fmt ";                                 //ID
    writeToWav(output, 16, 4);                        //Size : 16
    writeToWav(output, 1, 2);                         // Compression Code : uncompressed.
    writeToWav(output, 1, 2);                         //No of channels : 1
    writeToWav(output, sampleRate, 4);                //Sample rate
    writeToWav(output, sampleRate * bitDepth / 8, 4); //SampleRate * bitDepth = "bytes per second"
    writeToWav(output, bitDepth / 8, 2);              //Block align
    writeToWav(output, bitDepth, 2);                  //Bit Depth

    //Data Chunk:
    output << "data"; //ID
    output << "----"; //Size: Come back to this later.

    int preAudioPosition = output.tellp(); // Will use this to fill size we left.

    //Audio Sample:
    int size = finalData.size();
    for (int i = 0; i < sampleRate * duration && i < size; i++) {
        int intVal = static_cast<int>(finalData.at(i).real());
        writeToWav(output, intVal, 2);
    }

    int postAudioPosition = output.tellp(); // Will use this to fill size we left.

    output.seekp(preAudioPosition - 4);                          //Go to 4 positions before pre audio.
    writeToWav(output, postAudioPosition - preAudioPosition, 4); // Size of audio is post - pre.

    output.seekp(4, std::ios::beg);               //Go to 4 positions after begining.
    writeToWav(output, postAudioPosition - 8, 4); // Size in Header is everything, except Header ID and Size tags, which each take 4.

    wavLog.LogToFileAndConsole("New Data was written", info);
}

void Wave::applyFrequency(float frequency, float amplitude, int duration) {
    float phase = 0;
    float offset = 2 * pi * frequency / sampleRate;

    for (int i = 0; i < sampleRate * duration; i++) {

        if (i > audioData.size()) 
            audioData.push_back(amplitude * sin(phase));

        else
            audioData.at(i) += amplitude * sin(phase);

        phase += offset;
    }

    phase = 0;
    wavLog.LogToFileAndConsole("New frequency was added to data", info);
}

void Wave::findPeaks() {
    maximaIndices = Maxima(audioFourier);

    for (int i : maximaIndices) {
        complex freq = frequency[i];
        complex val = audioFourier[i];
        pair now(freq, val);

        freqValPair.push_back(now);
    }

    wavLog.LogToFileAndConsole("Frequency peaks were found", info); 
}