// LCD Thermostat
// www.hacktronics.com

#include <OneWire.h>

OneWire  ds(3);        // ds18b20 pin #2 (middle pin) to Arduino pin 8

byte i;
byte present = 0;
byte data[12];
byte addr[8];
  
int HighByte, LowByte, SignBit, Whole, Fract, TReading, Tc_100;

void setup(void) {
  
  if ( !ds.search(addr)) {
      delay(1000);
      ds.reset_search();
      return;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      delay(1000);
      return;
  }
  
  Serial.begin(9600);
}

void getTemp() {
  int foo, bar;
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);

  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  
  if (SignBit) {
    TReading = -TReading;
  }
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
  Whole = Tc_100 / 100;          // separate off the whole and fractional portions
}

void printTemp(void) {
  Serial.print("Temperature: ");
  Serial.print(Whole);
  Serial.print("\r\n");
}

void loop(void) {
  getTemp();
  printTemp();
  delay(1000);
}
