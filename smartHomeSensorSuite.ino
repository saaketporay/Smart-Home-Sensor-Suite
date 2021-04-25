//Saaket Poray
//Created for Comet Hack 2021
//4-25-2021

#include <dht.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

const int AOUTpin=0;
const int DOUTpin=8;
dht DHT;
int sensor=7;
float gas_value;
int limit;
int value;
double f = 0.00;

#define DHT11_PIN 3

void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000L);
  pinMode (sensor,INPUT);
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino

}

void loop(){
  #if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0
  oled.setFont(System5x7);
  oled.clear();
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  f = (DHT.temperature * (1.8)) + 32;
  oled.print("Temperature = ");
  oled.println(f);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  oled.print("Humidity = ");
  oled.println(DHT.humidity);
  gas_value=digitalRead(sensor);
  Serial.println(gas_value);
  if(gas_value > 0.999)
  {
     oled.println("No Combustible");
     oled.println("Gas Detected");
  }
  else
  {
     oled.println("Gas Detected");
  }
  value= analogRead(AOUTpin);
  limit= digitalRead(DOUTpin);
  Serial.print("Hydrogen value: ");
  Serial.println(value);
  Serial.print("Limit: ");
  Serial.println(limit);
  
  
  oled.print("CO Value: ");
  oled.println(value);
  delay(2000);
}
