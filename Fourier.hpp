#pragma once

#include <vector>
#include <complex>
#include "Utilities.hpp"

typedef std::complex<double> complex;

inline int closestPow(int num, int pow) {
    int now = pow;

    while (now < num) {
        now *= pow;
    }

    return now;
}

//Single radix Fourier Transform
inline std::vector<std::complex<double>> Radix2FFT(std::vector<std::complex<double>> discreteSeq, bool invert = false) {
    int size = discreteSeq.size();

    if (size == 1) {
        return discreteSeq;
    }

    std::vector<std::complex<double>> holdFFT(size); 
    std::vector<std::complex<double>> odd(size/2), even(size/2);

    //Decimation
    for (int i = 0; 2*i < size; i++) { 
        odd[i] = discreteSeq.at(2*i); 
        even[i] = discreteSeq.at(2*i + 1);
    } 
    
    odd = Radix2FFT(odd, invert);
    even = Radix2FFT(even, invert); 

    double angle = 2 * (pi/size) * (invert? -1 : 1);
    std::complex<double> omega(1, 0), omegaN( cos(angle), sin(angle) );

    for (int i = 0; 2*i < size; i++) {
        holdFFT[i] = odd.at(i) + omega*even.at(i); 
        holdFFT[i + size/2] = odd.at(i) - omega*even.at(i);

        if (invert) {
            holdFFT.at(i) /= 2;
            holdFFT.at(i + size/2) /= 2;
        }

        omega *= omegaN;
    } 

    return holdFFT;
}

// If the size of the data is not a power of two, then extend it with zeroes and apply Radix2FFT.
inline std::vector<std::complex<double>> FFT(std::vector<std::complex<double>> discreteSeq, bool invert = false) {
    int origSize = discreteSeq.size();
    int newSize = closestPow(origSize, 2);

    if (origSize != newSize) {
        std::vector<std::complex<double>> newSeq(newSize);

        int i = 0;
        for (; i < origSize; i++) { 
            newSeq[i] = discreteSeq.at(i);
        }

        for (; i < newSize; i++) {
            newSeq[i] = 0;
        }

        return Radix2FFT(newSeq, invert);
    }

    else 
        return Radix2FFT(discreteSeq, invert);
}

