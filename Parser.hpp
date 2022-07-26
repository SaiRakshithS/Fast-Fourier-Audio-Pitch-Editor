#pragma once

#include <iostream>
#include <vector>
#include <complex>

//Wav Header
struct Header {

    char chunkID[4];             //"RIFF" = 0x46464952
    unsigned long chunkSize;     //28 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes] + sum(sizeof(chunk.id) + sizeof(chunk.size) + chunk.size)
    char format[4];              //"WAVE" = 0x45564157
    char subChunk1ID[4];         //"fmt " = 0x20746D66
    unsigned long subChunk1Size; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned long sampleRate;
    unsigned long byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    //[WORD wExtraFormatBytes;]
    //[Extra format bytes]
};

//Chunks
struct Data {

    char ID[4];         //"data" = 0x61746164
    unsigned long size; //Chunk data bytes
};

inline Header WavReader(FILE* file, std::vector<std::complex<double>>& data) {

    //Reading header
    Header header;
    fread(&header, sizeof(header), 1, file);

    //Reading data chunk
    Data chunk;
    while (true) {

        fread(&chunk, sizeof(chunk), 1, file);

        if (*reinterpret_cast<unsigned int*> (&chunk.ID) == 0x61746164)
            break;

        fseek(file, chunk.size, SEEK_CUR);
    }

    //Number of samples
    int sample_size = header.bitsPerSample / 8;
    int samples_count = chunk.size * 8 / header.bitsPerSample;

    data.resize(samples_count);

    //Reading data
    for (int i = 0; i < samples_count; i++)  {

        fread(&data[i], sample_size, 1, file);
    }

    return header;
}
