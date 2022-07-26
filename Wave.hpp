#pragma once

#include "Utilities.hpp"
#include "Fourier.hpp"
#include "Maxima.hpp"
#include "Logger.hpp"
#include "Parser.hpp"

class Wave {

    typedef std::pair <complex, complex> pair;

    public:
        static Logger wavLog;

        int sampleRate;
        int bitDepth; 
        int fileSize;
        float duration;
        
        std::vector<complex> audioData;
        std::vector<complex> time;

        std::vector<complex> audioFourier;
        std::vector<complex> frequency;
        
        std::vector<pair> freqValPair;
        std::vector<int> maximaIndices;

        std::vector<complex> finalData;

    public:
        
        Wave();
        ~Wave();

        void extractSound(FILE*);
        void timeIntervals();
        void getFrequencies();
        void applyFFT();
        void applyInverseFFT();
        void writeToFile(int, std::ofstream&);
        void applyFrequency(float, float, int);
        void findPeaks();
};