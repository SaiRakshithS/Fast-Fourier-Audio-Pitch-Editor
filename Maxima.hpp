#pragma once

#include <vector>
#include <complex>

typedef std::complex<double> complex;

inline float average(std::vector<complex> data) {
    float sum = 0;
    int size = data.size();

    for (complex i : data) {
        sum += i.real();
    }

    float avg = sum / (float) size;
    return avg;
}

inline float sigma(std::vector<complex> data) {
    float avg = average(data);
    float variation = 0;

    for (complex i : data) {
        variation += (i.real() - avg) * (i.real() - avg);
    }

    variation /= data.size();
    return sqrtf(variation);
}

inline std::vector<int> Maxima(std::vector<complex> data) {
    float stdDev = sigma(data);
    float avg = average(data);

    int size = data.size();
    std::vector<int> storeIndices = {};

    for (int i = 0; i < size; i++) {
        if (data.at(i).real() - avg > stdDev)
            storeIndices.push_back(i);
    }

    return storeIndices;
}