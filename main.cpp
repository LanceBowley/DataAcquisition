#include <iterator>
#include <algorithm>
#include <iostream>
#include "BinaryIO.h"
#include "Serial.h"

using namespace std;

int main() {

    string outputDirectory = "/your/output/directory/here";
    BinaryIO binIO(outputDirectory);

    Serial serial;
    serial.setPort(0);
    serial.setBaudRate(9600);
    serial.setDirectory(outputDirectory);
    serial.setDimensions(3);
    serial.setRecordMode(RECORD_FINITE);
    serial.setNumberOfRecordings(5);
    serial.run<int>();

    vector<int> dimensionality = {100, 3};
    vector<vector<int>> data0 = binIO.read2dVector<int>(dimensionality, 0);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 3; j++) {
            cout << data0[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}


