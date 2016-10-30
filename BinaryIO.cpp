//
// Created by lbowley on 10/28/16.
//

#include "BinaryIO.h"

BinaryIO::BinaryIO(std::string _directory) {
    iStreamOpen = false;
    directory = _directory;
};

void BinaryIO::setDirectory(std::string _directory) {
    directory = _directory;
}

void BinaryIO::manageifstream(int _dimensions, std::string path) {
    bool initializing = false;
    if (!iStreamOpen) {
        iFile = new std::ifstream(path);
        iStreamOpen = true;
        highestDimension = _dimensions;
        initializing = true;
    }
    if (!initializing && _dimensions == highestDimension) {
        iFile->close();
        iStreamOpen= false;
    }
}

std::string BinaryIO::intToFileName(int fileNumber) {
    char cFileName[128];
    sprintf(cFileName, "/%06d.bin", fileNumber);
    std::string sFileName = (std::string) cFileName;
    return sFileName;
}
