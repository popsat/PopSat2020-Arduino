/* KODEA v1
 *  
 *  parentesi artean frogatu gabe
 *  normal, frogatua
 *  
 *  2bmp batera martxan
 *  apc bidaltzen
 *  (sd gordetzen)
 *  
 * 
 */
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
float i = 0;
float denbora = 0;
Adafruit_BMP280 bmp1; // I2C (A4(SDA), A5(SCL))
Adafruit_BMP280 bmp2; //I2C (A4(SDA), A5(SCL))
float presionin; // Almacena la presion atmosferica (Pa)
float temperaturain; // Almacena la temperatura (oC)
float altitudin; // Almacena la altitud (m) (se puede usar variable float)
float altuerainz = 0;
float abiadurain = 0;
float presionout; // Almacena la presion atmosferica (Pa)
float temperaturaout; // Almacena la temperatura (oC)
float altitudout; // Almacena la altitud (m) (se puede usar variable float)
float altueraoutz = 0;
float abiaduraout = 0;
float denboraz = 0;
SoftwareSerial sd(9, 10); // RX, TX
/////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:

  sd.begin(115200); // Inicia comunicacion serie SD
  Serial.begin(19200); //Radio
      if (!bmp1.begin(0x77)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  if (!bmp2.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280(2) sensor, check wiring!"));
    while (1);
  }// Inicia el sensor

  // see if the card is present and can be initialized:
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  String stringOne;
  presionin = bmp1.readPressure() / 100; //Presioa Irakurri
  temperaturain = bmp1.readTemperature();
  altuerainz = altitudin;
  altitudin = bmp1.readAltitude (1015); // Ajustar con el valor local
  //stringOne += F("Presioa(IN): ");
  stringOne += String(presionin, 2);
  stringOne += F(", ");
  stringOne += String(temperaturain, 2);
  stringOne += F(", ");
  stringOne += String(altitudin, 2);
  denboraz = denbora;
  denbora = millis();
  denbora = denbora/1000;
  stringOne += F(", ");
  stringOne += String(denbora, 2);
  abiadurain = (altitudin - altuerainz)/(denbora - denboraz);
  stringOne += F(", ");
  stringOne += String(abiadurain, 2);
  
  //BMP OUT
  
  presionout = bmp2.readPressure() / 100; //Presioa Irakurri
  temperaturaout = bmp2.readTemperature();
  altueraoutz = altitudout;
  altitudout = bmp2.readAltitude (1015); // Ajustar con el valor local
  stringOne += F(", ");
  stringOne += String(presionout, 2);
  stringOne += F(", ");
  stringOne += String(temperaturaout, 2);
  stringOne += F(", ");
  stringOne += String(altitudout, 2);
  denboraz = denbora;
  denbora = millis();
  denbora = denbora/1000;
  stringOne += F(", ");
  stringOne += String(denbora, 2);
  abiaduraout = (altitudout - altueraoutz)/(denbora - denboraz);
  stringOne += F(", ");
  stringOne += String(abiaduraout, 2);
  i=i+1;
  stringOne += F(", ");
  stringOne += String(i, 2);
  sd.listen();
  sd.println(stringOne);
  Serial.println(stringOne);
  delay(100);
}
