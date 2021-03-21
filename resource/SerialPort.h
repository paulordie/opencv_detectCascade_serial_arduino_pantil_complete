//
// Created by pcorrea on 17/10/2020.
//

#ifndef CLION1_SERIALPORT_H
#define CLION1_SERIALPORT_H

////serial linux
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <string>

class SerialPort {
public:
    void portOpen();
    void erroPort();
    void setupPort();
    void writePort(const char* objectCharOut,const char* toLenght);
    void closePort();

private:
    int serial_port;
    struct termios tty;

};


#endif //CLION1_SERIALPORT_H
