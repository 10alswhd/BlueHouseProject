#include <OneWire.h>
#include <LiquidCrystal.h>

// For every sensor found it outputs to serial:
// SensorID,CurrentTemp,Readout time,Current time
// Info at: http://wiki.spodeli.org/Хаклаб/Температура

OneWire ds(12);  // on pin 12
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

struct SensorData {
  byte addr[8];
  float temp;
  unsigned long time;
};

SensorData Senzori[8];
byte currentSensor = 0;
byte attachedSensors = 0;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  float celsius;

  //Search for the sensors  
  if ( !ds.search(addr)) {
    currentSensor = 0;
    ds.reset_search();
    delay(250);
    return;
  }
 
  //CRC is not valid exit loop
  if (OneWire::crc8(addr, 7) !=   addr[7]) {
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(1000);                          // maybe 750ms is enough, maybe not
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);                       // Read Scratchpad

  //Get the temperature
  for ( i = 0; i < 9; i++) {            // we need 9 bytes
    data[i] = ds.read();
  }
  

  // convert the data to actual temperature
  unsigned int raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
   
  celsius = (float)raw / 16.0;
  
  Senzori[currentSensor].time = millis();
  Senzori[currentSensor].temp = celsius;
  memcpy(Senzori[currentSensor].addr, addr, 8);
  currentSensor++;
  if (attachedSensors < currentSensor)
    attachedSensors = currentSensor;
  
  //Print current temp on LCD static for 3 sensors
  lcd.setCursor(0,0);
  lcd.print("Lounge: ");
  lcd.print(Senzori[0].temp);
  
  lcd.setCursor(0,1);
  lcd.print("Outside: ");
  lcd.print(Senzori[1].temp);
  
  lcd.setCursor(0,2);
  lcd.print("HW room: ");
  lcd.print(Senzori[2].temp);
  
  lcd.setCursor(0,3);
  lcd.print("Random: ");
  lcd.print(Senzori[3].temp);

  //Print current temp on LCD
  //for (i=0; i<attachedSensors; i++) {
  //  lcd.setCursor(0,i);
  //  for (byte j = 0; j < 8; j++) {
  //     lcd.print(Senzori[i].addr[j],HEX);   
  //  }
  //  lcd.print(": ");
  //  lcd.print(Senzori[i].temp);
  //}
  
  if (Serial.available()) {
    byte a = Serial.read();
    for (i=0; i<attachedSensors; i++) {
      // First line is the address
      for( byte j = 0; j < 8; j++) {
        Serial.print(Senzori[i].addr[j], HEX);
      }
      Serial.print(',');
      Serial.print(Senzori[i].temp);
      Serial.print(',');
      Serial.print(Senzori[i].time);
      Serial.print(',');      
      Serial.print(millis());
      Serial.println();          
    }
    Serial.println(); 
  }
}
