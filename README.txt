Serial manages all of the data entering a specified serial port, refactors the data and exports the data as a
binary file to a specified directory for further use.

Formatting Data for compatibility:
Serial assumes that data which is being received is in a character format. Data coming into the serial port must
be formatted correctly in order for the data to be understood.
    +A null character begins a recording
    +Data must be of basic types only and typecasted as characters
    +Send a space character to signify the end of a number
    +Send a carraige return to signify the end of a single collection of data which will be pushed to a larger vector
    +A null character ends a recording

setPort(int portNumber || string portName) -> takes in port numbers one or two to read from serial port
"/dev/ttyACM0" or "/dev/ttyACM1".  If another serial port is desired, you can manually enter anthoer serial port
directory as a string.  If no serial ports are connecting properly, open your terminal and type:$ sudo chmod 666
"your/port/directory" to allow access

setBaudRate(int baudRate) -> Sets the rate of data transmission. If data is not being transmitted correctly it
may be neccesary to implement a small delay between transmissions

setDirecory(string directory) -> Sets the destination of data files

setDimensions(int dimensions) -> Specifies the number of dimensions that are being read from the serial port,
which are meant to represnet a single instance of data from a moment in time for data acquisition.

setNumberOfRecordings(int recordings) -> Sets the number of files that will be saved if record mode is finite

setRecordMode(RecordMode recordMode) -> Sets the program to record a specific number of files or to record indefinitely
    +RECORD_FINITE->Records the specified number of data files. If a number is not specified, it will record one
    +RECORD_INDEFINITE->Will record until the program is manually ended, has an error, or an indefinite record
    terminator is implemented

run<inputDataType>run() -> Implements the above settings with a template input data type

The binaryIO class can be subsequently used to read the binary files back into a vector

ImuCollector is an example of how the serial port can be managed on the other end


