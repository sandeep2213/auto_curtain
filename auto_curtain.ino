// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int temprature;

#define IR_SENSOR D6
int ir=0;

#define PIR_SENSOR D5
int pir=0;

void setup() {
  
  Serial.begin(9600);
  pinMode(IR_SENSOR,INPUT_PULLUP);
  
  sensors.begin();
  
}

void loop() {

  sensors.requestTemperatures();
  temprature=sensors.getTempCByIndex(0);
  ir=digitalRead(IR_SENSOR);
  pir=digitalRead(PIR_SENSOR);


  

}
