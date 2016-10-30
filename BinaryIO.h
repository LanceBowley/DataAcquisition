//
// Created by lbowley on 10/28/16.
//

#ifndef SERIAL_BINARYIO_H
#define SERIAL_BINARYIO_H

#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <type_traits>

class BinaryIO {
public:
    BinaryIO(std::string);
    void setDirectory(std::string);

    template<typename T>
    void writeMultiVector(T & v, int fileNumber);
    template<typename T>
    void writeMultiVector(T & v, std::string fileName);
    template<typename T>
    void unpackMultiVector(std::vector<std::vector<T>> &v);
    template<typename T>
    void unpackMultiVector(std::vector<T> &v);
    template<typename T>
    void unpackMultiVector(T &i);

    template<typename T>
    std::vector<std::vector<T>> read2dVector(std::vector<int> dimensionality, int fileNumber);
    template<typename T>
    std::vector<std::vector<T>> read2dVector(std::vector<int> dimensionality, std::string fileName);
    template<typename T>
    std::vector<T> read1dVector(int size, int fileNumber);
    template<typename T>
    std::vector<T> read1dVector(int size, std::string fileName);

private:
    std::string directory;
    std::ifstream* iFile;
    std::ofstream* oFile;
    bool iStreamOpen;
    int highestDimension;

    std::string intToFileName(int);
    void manageifstream(int, std::string);

    template <typename T>
    struct base_type {
        using type = T;
    };

    template<typename T>
    struct base_type<std::vector<T>>
            : base_type<T>
    { };
};

template<typename T>
void BinaryIO::writeMultiVector(T & v, int fileNumber) {
    std::string fileName = intToFileName(fileNumber);
    writeMultiVector<T>(v, fileName);
}

template<typename T>
void BinaryIO::writeMultiVector(T & v, std::string fileName) {
    std::string sPath = directory + (std::string) fileName;
    const char* cPath = sPath.c_str();
    oFile = new std::ofstream(cPath, std::ios::out | std::ios::binary);
    unpackMultiVector<typename base_type<T>::type>(v);
    oFile->close();
}

template<typename T>
void BinaryIO::unpackMultiVector(std::vector<std::vector<T>> &v) {
    unsigned long length = v.size();
    for (int i = 0; i < length; i++) {
        unpackMultiVector<T>(v[i]);
    }
}

template<typename T>
void BinaryIO::unpackMultiVector(std::vector<T> &v) {
    unsigned long length = v.size();
    for (int i = 0; i < length; i++) {
        unpackMultiVector<T>(v[i]);
    }
}

template<typename T>
void BinaryIO::unpackMultiVector(T &i) {
    oFile->write((char*)&i, sizeof(T));
}

template<typename T>
std::vector<std::vector<T>> BinaryIO::read2dVector(std::vector<int> dimensionality, int fileNumber) {
    std::string fileName = intToFileName(fileNumber);
    std::vector<std::vector<T>> v = read2dVector<T>(dimensionality, fileName);
    return v;
}

template<typename T>
std::vector<std::vector<T>> BinaryIO::read2dVector(std::vector<int> dimensionality, std::string fileName) {
    std::vector<std::vector<T>> v;
    std::vector<T> vi;
    std::string path = directory + fileName;
    manageifstream(2, path);
    for (int i = 0; i < dimensionality[0]; i++) {
        vi = read1dVector<T>(dimensionality[1], fileName);
        v.push_back(vi);
    }
    manageifstream(2, path);
    return v;
}

template<typename T>
std::vector<T> BinaryIO::read1dVector(int size, int fileNumber) {
    std::string fileName = intToFileName(fileNumber);
    std::vector<T> v = read1dVector<T>(size, fileName);
    return v;
}

template<typename T>
std::vector<T> BinaryIO::read1dVector(int size, std::string fileName) {
    std::string path = directory + fileName;
    manageifstream(1, path);
    std::vector<T> v((unsigned long) size);
    iFile->read(reinterpret_cast<char*>(v.data()), v.size()*sizeof(T));
    manageifstream(1, path);
    return v;
}



#endif //SERIAL_BINARYIO_H
