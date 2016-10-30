//
// Created by lbowley on 10/30/16.
//

#ifndef SERIAL_SERIAL_H
#define SERIAL_SERIAL_H
#include <iterator>
#include <algorithm>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/ios_base.h>
#include <ios>
#include "Initializer.h"
#include "Port.h"
#include "BinaryIO.h"

enum RecordMode {
    RECORD_FINITE = 0,
    RECORD_INDEFINITE = 1
};

class Serial {
public:
    Serial();
    template<typename T>
    void run();
    void setPort(int);
    void setPort(std::string);
    void setDirectory(std::string);
    void setBaudRate(int);
    void setDimensions(int);
    void setRecordMode(RecordMode);
    void setNumberOfRecordings(int);

private:
    std::string directory;
    std::string portName;
    BinaryIO* binIO;
    Port* port;
    int dimensions;
    int baudRate;
    RecordMode recordMode;
    int nRecordings;
};

template<typename T>
void Serial::run() {

    int fileNumber = 0;

    while(recordMode == RECORD_INDEFINITE || fileNumber < nRecordings) {
        std::vector<std::vector<T>> imuData = port->listen<T>();
        binIO->writeMultiVector<std::vector<std::vector<T>>>(imuData, fileNumber);
        fileNumber++;
    }
}

#endif //SERIAL_SERIAL_H
