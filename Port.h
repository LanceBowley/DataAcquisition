//
// Created by lbowley on 10/26/16.
//

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "Initializer.h"

enum CharacterCode {
    CAPTURE_TERMINATOR = 10,
    NUMBER_TERMINATOR = 32,
    RECORD_TERMINATOR = 0
};

class Port {
public:
    Port(std::string, int, int);
    void setName(const char *);
    void setBaudRate(int);
    void setDimensions(int);
    template<typename T>
    std::vector<std::vector<T>> listen();

    int charToFormat(int &n);
    float charToFormat(float &f);
    double charToFormat(double &d);

private:
    int fd;
    const char* portName;
    unsigned char buf[1];
    int nDimensions;
    int dimensionsWritten;
    char numberAsArray[20];
    int characterIndex;
    bool recording;
    Initializer* initializer;

};

template<typename T>
std::vector<std::vector<T>> Port::listen() {
    bool listening = true;
    std::vector<std::vector<T>> data;
    std::vector<T> dataCapture;
    T number;
    T n;
    while (listening) {
        read(fd, buf, sizeof(buf));
        char input = buf[0];
        if (input != RECORD_TERMINATOR) {
            recording = true;
            int emptyDimensions;
            switch(input) {
                case CAPTURE_TERMINATOR: // A new line signifies a data capture termination
                    if (dimensionsWritten < nDimensions) { // Check for missing dimensions
                        emptyDimensions = nDimensions - dimensionsWritten;
                        for (int i = 0; i < emptyDimensions; i++) {
                            dataCapture.push_back(-1); // Default add -1 for missing dimensions
                        }
                    }
                    data.push_back(dataCapture);
                    dataCapture.clear();
                    memset(numberAsArray, '\0', 20*sizeof(char));
                    dimensionsWritten = 0;
                    break;
                case NUMBER_TERMINATOR: // A space signifies a single data point termination
                    if (dimensionsWritten < nDimensions) { // Don't add more dimensions than we should
                        numberAsArray[characterIndex + 1] = '\0';
                        characterIndex = 0;
                        number = charToFormat(n);
                        memset(numberAsArray, '\0', 20*sizeof(char)); // Resets the char array to empty
                        dataCapture.push_back(number);
                        dimensionsWritten++;
                    }
                    break;
                default: // Non null character data
                    numberAsArray[(unsigned long) characterIndex] = input;
                    characterIndex++;
            }
        }
        else {
            if (recording) {
                recording = false;
                listening = false;
            }
        }
    }
    return data;
}

#endif //SERIAL_PORT_H
