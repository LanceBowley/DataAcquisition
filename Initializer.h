//
// Created by lbowley on 10/26/16.
//

#ifndef SERIAL_INITIALIZER_H
#define SERIAL_INITIALIZER_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>

class Initializer {
public:
    int set_interface_attribs(int, int);
private:
};

#endif //SERIAL_INITIALIZER_H
