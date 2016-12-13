/*James Sappington; Mini Automatic Aquaponic Code for 24 hour use*/
/*-----( Import needed libraries )-----*/
#include <LiquidCrystal.h> // http://arduino.cc/en/Tutorial/LiquidCrystalDisplay
#include <Stepper.h>
#include <OneWire.h>
#include <SoftwareSerial.h> // we have to include the SoftwareSerial library, for pH.
// code for pH sensor adapted from seller: https://www.atlas-scientific.com/_files/code/Arduino_pH_sample_code.pdf

/*-----( Declare Constants, Pin Numbers )-----*/

#define STEPS 100               // Number of steps per revolution
#define RELAY_ON 0              // relay on
#define RELAY_OFF 1             // relay off

/*-----( Declare Variables )-----*/

#define PumpRelay_1 8         // Arduino Digital I/O pin number pump
#define LightRelay_2 9        // Arduino Digital I/O pin number lights

#define rx 15             // define what pin rx is going to be for pH.
#define tx 14             // define what pin tx is going to be for pH.
SoftwareSerial myserial(rx, tx); // define how the soft serial port is going to work.

int Water_Pin = 2;              // DS18S20 Signal pin on digital 2
int Air_Pin = 4;                // DS18S20 Signal pin on digital 4

char ph_data[20]; // 20 byte character array to hold incoming data from the pH sensor.
char computerdata[20]; // 20 byte character array to hold incoming data.

byte received_from_computer = 0; // we need to know how many characters have been received.
byte received_from_sensor = 0; // we need to know how many characters have been received.

// if you would like to operate the pH Circuit with the Arduino only and not use the
// serial monitor to send it commands set this to 1. The data will still come out on the byte startup=0;
// serial monitor, so you can see it working.

byte arduino_only = 1; // used to make sure the Arduino takes over control of the pH Circuit properly.
byte startup = 0;
float ph = 0;  // used to hold a floating point number that is the pH.
byte string_received = 0; // used to identify when we have received a string from the pH circuit.

// Temperature chip i/o
OneWire water(Water_Pin);
OneWire air(Air_Pin);

// The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper FishFeedersmall_stepper(STEPS, 10, 12, 11, 13);

int Steps2Take;

LiquidCrystal lcd(5, 6, 32, 34, 36, 38); // LCD pin setup

void setup() /****** SETUP: RUNS ONCE ******/ {
   /* set the speed of the stepper motor  */
    FishFeedersmall_stepper.setSpeed(200);

    lcd.begin(16, 2);
    lcd.print("Water Temp:");
    lcd.setCursor(0, 1);       // sets cursor to second line first row
    lcd.print("");             // last name on second line
    lcd.setCursor(0, 0);       // cursor to first position first line

    Serial1.begin(38400);       // for pH sensor
    Serial2.begin(9600);        // for normal serial communication

    /* COMMENT OUT 9600
     * Serial.begin(38400);
     * enable the hardware serial port
     * myserial.begin(38400);
     * enable the hardware serial port
     */
    /* -------( Initialize Pins so relays are inactive at reset)---- */
    digitalWrite(PumpRelay_1, RELAY_OFF);
    digitalWrite(LightRelay_2, RELAY_OFF);
    /* ---( THEN set pins as outputs )---- */
    pinMode(PumpRelay_1, OUTPUT);
    pinMode(LightRelay_2, OUTPUT);
    delay(4000);        // Check that all relays are inactive at Reset
} // --(end setup )---

void loop() /****** LOOP: RUNS CONSTANTLY ******/ {

    lcd.noDisplay();            // LCD display loop
    delay(250);
    /* Turn on the display: */
    lcd.display();
    delay(2500);

    if (Serial1.available())    // picks up available serial rate
        Serial2.write(Serial1.read());

    /************************************************PUMP OUT TANK********************************************************************
    **********************************unhook hose from back of tank and put it in a bucket*******************************************
    // pumpOutTank();pumps out tank 
    ************************************************PUMP OUT TANK********************************************************************
    *********************************************************************************************************************************/
    pHtesting();
    testFunction();             // runs system tests
    theMidnightHour();          // 00:00-03:00
    threeToSixAM();             // 03:00-06:00
    sixToNineAM();              // 06:00-09:00
    nineToNoon();               // 09:00-12:00
    noonToThree();              // 12:00-15:00
    threeToSixPM();             // 15:00-18:00
    sixToNinePM();              // 18:00-21:00
    nineToMidnight();           // 21:00-23:59:59
} // --(end main loop )---

// here are some functions you might find useful
// these functions are not enabled
// calibrate to a pH of 7
// send the "s" command to calibrate to a pH of 7.00
void f_cal() {
    myserial.print("f\r");
}
// calibrate to a pH of 4
// send the "f" command to calibrate to a pH of 4.00
void t_cal() {
    myserial.print("t\r");
}
// calibrate to a pH of 10
// send the "t" command to calibrate to a pH of 10.00
void phFactoryDefault() {
    myserial.print("X\r");
}
void read_info() {
    myserial.print("I\r");
}
// factory defaults the pH circuit
// send the "X" command to factory reset the device
// get device info
// send the "I" command to query the information
void phSetLEDs(byte enabled) {
    if (enabled)
        myserial.print("L1\r");
    else
        myserial.print("L0\r");
}
// turn the LEDs on or off
// if enabled is > 0
// the LED's will turn ON
// if enabled is 0
// the LED's will turn OFF

void pHtesting() {
    Serial.begin(38400);        // enable the hardware serial port

    myserial.begin(38400);      // enable the hardware serial port
    delay(5000);

    Serial.println("If serial input is available, pH data will follow.\n");
    if (myserial.available() > 0) {
        received_from_sensor = myserial.readBytesUntil(13, ph_data, 20);
        ph_data[received_from_sensor] = 0;
        string_received = 1;
        Serial.println(ph_data);

    }
    if (arduino_only == 1) {
        Arduino_Control();
    }
    delay(250);
}

void testFunction() {  // tests all functions of MicroAquaponic System
    lcd.print("Testing, testing.");
    lcd.setCursor(0, 1);       // sets cursor to second line first row

    Serial.println("Testing, testing.\n");
    delay(250);
    FishFeedersmall_stepper.setSpeed(75);
    Steps2Take = -100;          // Rotate CCW
    FishFeedersmall_stepper.step(Steps2Take);

    if ((Steps2Take) >= -99) {
        Serial.println("Fish Feeder fails test!!\n");
    } else if ((Steps2Take) < -99) {
        Serial.println("Fish Feeder takes -100 steps Counter Clock Wise.\n");
        delay(250);
    }

    FishFeedersmall_stepper.setSpeed(75);
    Steps2Take = 100;           // Rotate CW
    FishFeedersmall_stepper.step(Steps2Take);

    if ((Steps2Take) <= 99) {
        Serial.println("Fish Feeder fails test!!\n");
    } else if (Steps2Take > 99) {
        lcd.print("Fish Feeder");
        lcd.setCursor(0, 1);   // sets cursor to second line first row
        lcd.print("100 steps CW"); // last name on second line
        lcd.setCursor(0, 0);    // cursor to first position first line
        delay(250);
        Serial.println("Fish Feeder takes 100 steps Clock Wise.\n");
        delay(250);
    }

    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    if (LightRelay_2, RELAY_ON) {
        Serial.println("Lights ON fails test!!\n");
    } else if (LightRelay_2, RELAY_ON == false) {
        Serial.println("Lights ON for 2.5 seconds.");
    }
    delay(5000);

    digitalWrite(LightRelay_2, RELAY_OFF); // set the Relay On
    if (LightRelay_2, !RELAY_OFF) {
        Serial.println("Lights OFF fail test!!.\n");
    } else if (LightRelay_2, RELAY_OFF == true) {
        Serial.println("Lights OFF.\n");
        delay(500);
    }

    digitalWrite(PumpRelay_1, RELAY_ON); // set the Relay On

    if (PumpRelay_1, RELAY_ON) {
        Serial.println("Pump ON fails test!!\n");
    } else if (PumpRelay_1, !RELAY_ON) {
        Serial.println("Pump ON for 2.5 seconds.\n");
    }
    delay(2500);

    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay On

    if (PumpRelay_1, !RELAY_OFF) {
        Serial.println("Pump OFF fails test!!\n");
    } else if (PumpRelay_1, RELAY_OFF) {
        Serial.println("Pump OFF for 2.5 seconds.\n");
        delay(2500);
    }

    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    Serial.println("Pump and Light ON together for 5 seconds.\n");
    digitalWrite(PumpRelay_1, RELAY_ON); // set the Relay On

    delay(5000);

    digitalWrite(LightRelay_2, RELAY_OFF); // set the Relay On
    Serial.println("Pump and Light OFF together.\n");
    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay On
    delay(250);
    Serial.println("Get initial sensor readings: \n");
    delay(250);
    getWaterTemp();
    delay(250);
    getAirTemp();
    delay(250);
    Serial.println("Accurate temperature readings will be given when system starts.\n");
    delay(250);
    Serial.println("Testing has concluded.\n");
    Serial.println("The MicroAquaponic System will begin 24 hour cycle in 5 seconds...\n");
    delay(5000);
}

void Arduino_Control() {
    if (startup == 0) {
        myserial.print("e\r");
        delay(50);
        myserial.print("e\r");
        delay(50);
        startup = 1;
    }
    delay(800);
    myserial.print("R\r");
    if (string_received == 1) {
        ph = atof(ph_data);
        if (ph >= 7.5) {
            Serial.println("high\r");
        } else {
            Serial.println("low\r");
        }
        string_received = 0;
    }
}

void pumpOutTank() {
    digitalWrite(PumpRelay_1, RELAY_ON); // set the Relay On
    delay(600000000);           // pump 10 minutes; pump out tank
}

void theMidnightHour() {
    Serial.println(" // ---(00:00 hours - pump 2 minutes: 120,000ms)---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(PumpRelay_1, RELAY_ON);  // set the Relay ON
    delay(120000);                        // pump for 2 minutes 
    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay OFF
    Serial.println("00:02\n");
    getWaterTemp();
    getAirTemp();
    delay(10798000);            // delay ~3 hours
}
void threeToSixAM() {
    Serial.println("// ---(03:00 hours - pump 2 minutes: 120,000ms)---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(PumpRelay_1, RELAY_ON);  // set the Relay ON
    delay(120000);                        // pump for 2 minutes 
    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay OFF
    Serial.println("03:02");
    getWaterTemp();
    getAirTemp();
    delay(10798000);            // delay ~3 hours
}

void sixToNineAM() {

    Serial.println("// ---(06:00 hours - pump 2 minutes: 120,000ms, Lights ON, Camera takes picture. )---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(PumpRelay_1, RELAY_ON);  // set the Relay ON
    delay(120000);                        // pump 2 minutes
    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay ON 
    Serial.println("06:02");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    delay(10798000);                      // lights on for 3 hours 
}

void nineToNoon() {
    Serial.println("---(09:00 - pump 2 minutes: 120,000ms, Lights ON)---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_OFF); // light off
    digitalWrite(PumpRelay_1, RELAY_ON);   // set the Relay ON
    delay(120000);                         // pump 2 minutes
    digitalWrite(PumpRelay_1, RELAY_OFF);  // set the Relay ON 
    Serial.println("09:02");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    delay(10798000);                      // lights on for 3 hours 
}

void noonToThree() {
    Serial.println("// ---(12:00 hours - pump 4 minutes: 120,000ms, Lights ON, Feed fish: -1500 CCW, LUNCH TIME!!. )---\n");

    getWaterTemp();
    getAirTemp();
                                // small_stepper.setSpeed(75);
    //*************************************************************************************************************************
                                //  Steps2Take  =  -1500;
                                // Rotate CCW
                                // small_stepper.step(Steps2Take);

    digitalWrite(LightRelay_2, RELAY_OFF); // light off at 12 Noon for 2 minutes while pump runs
    digitalWrite(PumpRelay_1, RELAY_ON);   // set the Relay ON
    delay(120000);                         // pump 2 minutes
    digitalWrite(PumpRelay_1, RELAY_OFF);  // set the Relay ON 
    Serial.println("12:02\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_ON); // set the light Relay On
    delay(10798000);                      // lights on for 3 hours
}

void threeToSixPM() {
    Serial.println("// ---(15:00 hours - pump 2 minutes: 120,000ms, Lights ON. )---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_OFF); // light off at 15:00 for 2 minutes while pump runs
    digitalWrite(PumpRelay_1, RELAY_ON);   // set the Relay ON
    delay(120000);                         // pump 2 minutes
    digitalWrite(PumpRelay_1, RELAY_OFF);  // set the Relay ON 
    Serial.println("15:00\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    delay(10798000);                      // lights on for 3 hours
}

void sixToNinePM() {
    Serial.println("// ---(18:00 hours - pump 4 minutes: 120,000ms, Lights ON. )---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_OFF); // light off at 18:00 for 2 minutes while pump runs
    digitalWrite(PumpRelay_1, RELAY_ON);   // set the Relay ON
    delay(120000);                         // pump 2 minutes
    digitalWrite(PumpRelay_1, RELAY_OFF);  // set the Relay OFF 
    Serial.println("18:02");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay On
    delay(10798000);                      // lights on for 3 hours 
}

void nineToMidnight() {

    Serial.println("// ---(21:00 hours - pump 2 minutes: 120,000ms, Lights ON. Lights OFF at 00:00)---\n");
    getWaterTemp();
    getAirTemp();
    digitalWrite(LightRelay_2, RELAY_OFF); // light off
    digitalWrite(PumpRelay_1, RELAY_ON);   // set the Relay ON
    delay(120000);                         // pump 2 minutes
    Serial.println("21:02");
    getWaterTemp();
    getAirTemp();
    digitalWrite(PumpRelay_1, RELAY_OFF); // set the Relay OFF
    digitalWrite(LightRelay_2, RELAY_ON); // set the Relay ON
    delay(10798000);                      // lights on for 3 hours

    // ---(00:00 hours - Lights OFF. )---

    digitalWrite(LightRelay_2, RELAY_OFF); // set the Relay OFF

}
void getAirTemp() {
  /* adapted from http://bildr.org/2011/07/ds18b20-arduino/ prints the
     air temperature from one DS18S20 in degrees Celsius and
     Fahrenheit */

    float AirTemperatureSum;
    byte data[12];
    byte addr[8];

    if (!air.search(addr)) {
        air.reset_search();  // no more sensors on chain, reset search
        AirTemperatureSum = -1000;
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!\n");
        AirTemperatureSum = -1000;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28) {
        Serial.print("Device is not recognized\n");
        AirTemperatureSum = -1000;
    }

    air.write(0x44, 1); // start conversion, with parasite power on at the end

    air.reset();
    air.select(addr);
    air.write(0x44, 1); // start conversion, with parasite power on at the end

    byte present = air.reset();

    air.select(addr);
    air.write(0xBE);            // Read Scratchpad

    for (int j = 0; j < 9; j++) { // we need 9 bytes
        data[j] = air.read();
    }

    air.reset_search();

    byte MSB = data[1];
    byte LSB = data[0];

    float tempRead = ((MSB << 8) | LSB); // using two's complement
    AirTemperatureSum = tempRead / 16;

    float AirTemperatureCelsius = AirTemperatureSum; // getAirTemp();
    float AirTemperatureFahrenheit = ((AirTemperatureCelsius * 9) / 5) + 32;

    Serial.print("Air Temp: \n");
    Serial.print(AirTemperatureCelsius);
    Serial.println(" degrees C");
    Serial.print(AirTemperatureFahrenheit); // Multiply by 9, then divide by 5, then add 32
    Serial.println(" degrees F\n");
}

void getWaterTemp() {
                                // returns the temperature from one DS18S20 in degree Celsius and Fahrenheit

    float WaterTemperatureSum;
    byte data[12];
    byte addr[8];

    if (!water.search(addr)) {
        water.reset_search(); // no more sensors on chain, reset search
        WaterTemperatureSum = -1000;
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!\n");
        WaterTemperatureSum = -1000;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28) {
        Serial.print("Device is not recognized.\n");
        WaterTemperatureSum = -1000;
    }

    water.reset();
    water.select(addr);
    water.write(0x44, 1); // start conversion, with parasite power on at the end

    byte present = water.reset();

    water.select(addr);
    water.write(0xBE);          // Read Scratchpad

    for (int i = 0; i < 9; i++) { // we need 9 bytes
        data[i] = water.read();
    }

    water.reset_search();

    byte MSB = data[1];
    byte LSB = data[0];

    float tempRead = ((MSB << 8) | LSB); // using two's complement
    WaterTemperatureSum = tempRead / 16;

    float WaterTemperatureCelsius = WaterTemperatureSum; // getWaterTemp();
    float WaterTemperatureFahrenheit = ((WaterTemperatureCelsius * 9) / 5) + 32;

    Serial.print("Water Temp: \n");
    Serial.print(WaterTemperatureCelsius);
    Serial.println(" degrees C");
    Serial.print(WaterTemperatureFahrenheit); // Multiply by 9, then divide by 5, then add 32
    Serial.println(" degrees F\n");
}
//*********( THE END )***********

/*  LocalWords:  PumpRelay Arduino LightRelay SoftwareSerial
 */
/*  LocalWords:  MicroAquaponic
 */
