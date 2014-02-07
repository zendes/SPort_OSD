#include <SPort.h>
SPort sport(Serial);

#include <SPI.h>
#include "max7456.h"
Max7456 osd;
// Offset: 48,18
// Dimensions: 0,0 to 25,12

ISR(TIMER2_COMPA_vect) {
  sport.process();
}

void setup() {
  sport.begin();
  
  SPI.begin();
  osd.init(10);
  osd.setDisplayOffsets(48,18);
  osd.activateOSD();

  //consumption
  osd.print("0",              4, 10);
  osd.printMax7456Char(0x82,  6, 10);

  //current
  osd.print("0.00",           1, 11);
  osd.printMax7456Char(0x8F,  6, 11);

  //voltage
  osd.print("0.00",           1, 12);
  osd.printMax7456Char(0x8E,  6, 12);

  //velocity
  osd.print("0",             23, 10);
  osd.printMax7456Char(0x88, 25, 10);

  //altitude
  osd.print("0.0",           21, 11);
  osd.printMax7456Char(0x85, 25, 11);

  //time
  osd.print("00:00",         19, 12);
  osd.printMax7456Char(0xB3, 25, 12);
}


void loop() {
  //consumption
  if (sport.getVfasConsumption() < 10) {
    osd.print((int)sport.getVfasConsumption(), 4, 10, 1, 0);    
  } else if (sport.getVfasConsumption() < 100) {
    osd.print((int)sport.getVfasConsumption(), 3, 10, 2, 0);
  } else if (sport.getVfasConsumption() < 1000) {
    osd.print((int)sport.getVfasConsumption(), 2, 10, 3, 0);
  } else {
    osd.print((int)sport.getVfasConsumption(), 1, 10, 4, 0);
  }  

  //current
  if (sport.getVfasCurrent() < 10000) {
    osd.print(" ",                                  0, 11);
    osd.print((float)sport.getVfasCurrent() / 1000, 1, 11, 1, 2);
  } else {
    osd.print((float)sport.getVfasCurrent() / 1000, 0, 11, 2, 2);
  }

  //voltage
  if (sport.getVfasVoltage() < 10000) {
    osd.print(" ",                                  0, 12);
    osd.print((float)sport.getVfasVoltage() / 1000, 1, 12, 1, 2);
  } else {
    osd.print((float)sport.getVfasVoltage() / 1000, 0, 12, 2, 2);
  }

  //velocity

  //altitude
  osd.print("   ",                                   18, 11);
  if (sport.getVarioAltitude() < -1000) {
    osd.print((float)sport.getVarioAltitude() / 100, 19, 11, 2, 1);
  } else if (sport.getVarioAltitude() < 0) {
    osd.print((float)sport.getVarioAltitude() / 100, 20, 11, 1, 1);
  } else if (sport.getVarioAltitude() < 1000) {
    osd.print((float)sport.getVarioAltitude() / 100, 21, 11, 1, 1);
  } else if (sport.getVarioAltitude() < 10000) {
    osd.print((float)sport.getVarioAltitude() / 100, 20, 11, 2, 1);
  } else if (sport.getVarioAltitude() < 100000) {
    osd.print((float)sport.getVarioAltitude() / 100, 19, 11, 3, 1);
  } else {
    osd.print((float)sport.getVarioAltitude() / 100, 18, 11, 4, 1);
  } 

  //time
  long counter = millis()/1000;
  osd.print(int(counter/60), 19, 12, 2, 0);
  osd.print(int(counter%60), 22, 12, 2, 0);

  delay(100);
}
