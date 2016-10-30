//
// Created by lbowley on 10/30/16.
//

#include "Serial.h"

Serial::Serial() {
    directory = "/your/output/directory/here";
    portName = "/dev/ttyACM0";
    baudRate = 9600;
    recordMode = RECORD_FINITE;
    dimensions = 1;
    nRecordings = 1;
    port = new Port(portName, baudRate, dimensions);
    binIO = new BinaryIO(directory);
}

void Serial::setPort(int portNumber) {
    if (portNumber == 0) {
        portName = "/dev/ttyACM0";
    }
    if (portNumber == 1) {
        portName = "/dev/ttyACM1";
    }
}

void Serial::setPort(std::string _portName) {
    portName = _portName;
}

void Serial::setBaudRate(int _baudRate) {
    baudRate = _baudRate;
    port->setBaudRate(baudRate);
}

void Serial::setDimensions(int _dimensions) {
    dimensions = _dimensions;
    port->setDimensions(dimensions);
}

void Serial::setDirectory(std::string _directory) {
    directory = _directory;
    binIO->setDirectory(directory);
}

void Serial::setRecordMode(RecordMode _recordMode) {
    recordMode = _recordMode;
}

void Serial::setNumberOfRecordings(int _nRecordings) {
    nRecordings = _nRecordings;
}