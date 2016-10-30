#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
      
Adafruit_BNO055 bno = Adafruit_BNO055(55);
    
void setup() {
  Serial.begin(9600);
  bno.begin();
  delay(1000);
  bno.setExtCrystalUse(true);
}

const char nullData = 0; 
bool listening = true;
bool recording = false;
const int startStopPin = 2;
int pin2 = 0;
float orientations[3] = {0,0,0}; 

void loop() {

  while(listening) {

    delay(100); // Seems to prevent "noise" from interfering with initialization
    
    pin2 = digitalRead(startStopPin);
    if (pin2 == 1) {
      recording = true;
      delay(1000);
    }
    
    while (recording) {
  
      sensors_event_t event; 
      bno.getEvent(&event);
      orientations[0] = (int) event.orientation.x;
      orientations[1] = (int) event.orientation.y;
      orientations[2] = (int) event.orientation.z;
      for (int i = 0; i < 3; i++) {
        Serial.print(orientations[i]);
        delay(5);
        Serial.print(" ");
        delay(5);
      }
      Serial.print("\n");
      pin2 = digitalRead(startStopPin);
      if (pin2 == 1) {
        recording = false;
        delay(1000);
      }
    }
    Serial.print(nullData);
  }
}

// BUGS -> Holding the start/stop button long enough so that it rapidly enters and exits the recording loop will cause a premature termination on the next run
