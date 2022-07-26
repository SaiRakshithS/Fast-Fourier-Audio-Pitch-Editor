#pragma once

#include <cmath>
#include <vector>
#include "Utilities.hpp"
#include "Logger.hpp"


class Sine {

    private:
        static Logger sineLog;

        int bitDepth;
        int sampleRate;

        float amplitude;
        float frequency;
        float offset;
        float duration;
        float phase;

        //std::vector<double> holdTime;

    public: 

        // Parametrized constructor with default values
        Sine(const float&, const float& = 1.0, const float& = 10.0, 
        const int& = 48000, const float& = 0, const int& = 16);

        //The .wav file is made of many "chunks"
        void writeAudio (std::ofstream&);
};

