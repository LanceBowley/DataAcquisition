//
// Created by lbowley on 10/26/16.
//

#include "Port.h"

Port::Port(std::string sName, int baudRate, int _nDimensions) {
    characterIndex = 0;
    nDimensions = _nDimensions;
    dimensionsWritten = 0;
    const char * cName = sName.c_str();
    initializer = new Initializer();
    setName(cName);
    initializer->set_interface_attribs(fd, baudRate);
}

void Port::setName(const char *cName) {
    portName = cName;
    fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portName, strerror(errno));
    }
}

void Port::setBaudRate(int baudRate) {
    initializer->set_interface_attribs(fd, baudRate);
}

void Port::setDimensions(int _nDimensions) {
    nDimensions = _nDimensions;
}

int Port::charToFormat(int &n) {
    sscanf(numberAsArray, "%d", &n);
    return n;
}

float Port::charToFormat(float &f) {
    sscanf(numberAsArray, "%f", &f);
    return f;
}

double Port::charToFormat(double &d) {
    sscanf(numberAsArray, "%lf", &d);
    return d;
}