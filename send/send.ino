/* KODEA v2.1
 *  
 *  
 *  parentesi artean frogatu gabe
 *  kortxete implementatu gabe
 *  normal, frogatua
 *  
 *  2bmp batera martxan
 *  apc bidaltzen
 *  sd gordetzen
 *  (O2 sensor)
 *  
 *  Katea:
 *  presin, tempin, altin, denb1, abia1, presout, tempout, altout, denb2, abia2, oxygenV, oxygenC, ident
 * 
 */
#include <Adafruit_Sensor.h>  //Adafruit_Sensor.h libreria gehitu
#include "Adafruit_BMP280.h"  //Adafruit_BMP280.h libreria gehitu
#include <SoftwareSerial.h>   //SoftwareSerial libreria gehitu
#include <SPI.h>              //SPI libreria gehitu
#include <Wire.h>             //Wire libreria gehitu
Adafruit_BMP280 bmp1;         //I2C (A4(SDA), A5(SCL))
Adafruit_BMP280 bmp2;         //I2C (A4(SDA), A5(SCL))
float i = 0;                  //i float gehitu, identifikadore bezala erabiltzeko
float denbora = 0;            //Denbora float gehitu, arduino piztuta dagoen denbora kalkulatzeko
float denboraz = 0;           //Denbora zaharra gorde, abiadura eta denbora diferentzia kalkulatzeko
float presionin;              //Barruko presio atmosferikoa gordetzeko float gehitu
float temperaturain;          //Barruko tenperatura gordetzeko float gehitu
float altitudin;              //Barruko altuera gordetzeko float gehitu
float altuerainz = 0;         //Barruko altuera zaharra gordetzeko float gehitu. Honekin, altuera diferentzia kalkulatu daiteke
float abiadurain = 0;         //Barruko abiadura gordetzeko float gehitu
float presionout;             //Kanpoko presio atmosferikoa gordetzeko float gehitu
float temperaturaout;         //Lanpoko tenperatura gordetzeko float gehitu
float altitudout;             //Kanpoko altuera gordetzeko float gehitu
float altueraoutz = 0;        //Kanpoko altuera zaharra gordetzeko float gehitu. Honekin, altuera diferentzia kalkulatu daiteke
float abiaduraout = 0;        //Kanpoko abiadura gordetzeko float gehitu
float Vout =0;                //Oxigeno sentsorearen balioa gordetzeko float gehitu
int calibrateO2 = 93;         //Oxigeno sentsorea kalibratzeko float gehitu
SoftwareSerial sd(9, 10);     //SD. RX, TX
/////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:

  sd.begin(115200);        //SD-a abiarazi
  Serial.begin(19200);     //APC-ak abiarazi
  if (!bmp1.begin(0x77)) { //BMP Sentsorea abiarazi
    Serial.println(F("Ez da BMP(1, barrukoa) aurkitu!"));
    while (1);
  }
  if (!bmp2.begin(0x76)) { //BMP Sentsorea abiarazi
    Serial.println(F("Ez da BMP(2, kanpokoa) aurkitu!"));
    while (1);
  }
  calibrateO2 = analogRead(Vout); //Oxigeno sentsorea kalibratu
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
  //String bat sortu:
  
  String stringOne;

  //BBarruko BMP irakurri
  
  presionin = bmp1.readPressure() / 100; //Presioa Irakurri
  temperaturain = bmp1.readTemperature();
  altuerainz = altitudin;
  altitudin = bmp1.readAltitude (1015); //Ajustar con el valor local
  stringOne += String(presionin, 2);
  stringOne += F(",");
  stringOne += String(temperaturain, 2);
  stringOne += F(",");
  stringOne += String(altitudin, 2);
  stringOne += F(",");
  denboraz = denbora;
  denbora = millis();
  denbora = denbora/1000;
  stringOne += String(denbora, 2);
  stringOne += F(",");
  abiadurain = (altitudin - altuerainz)/(denbora - denboraz);
  stringOne += String(abiadurain, 2);
  stringOne += F(",");
  
  //Kanpoko BMP irakurri
  
  presionout = bmp2.readPressure() / 100; //Presioa Irakurri
  temperaturaout = bmp2.readTemperature();
  altueraoutz = altitudout;
  altitudout = bmp2.readAltitude (1015); //Ajustar con el valor local
  stringOne += String(presionout, 2);
  stringOne += F(",");
  stringOne += String(temperaturaout, 2);
  stringOne += F(",");
  stringOne += String(altitudout, 2);
  stringOne += F(",");
  denboraz = denbora;
  denbora = millis();
  denbora = denbora/1000;
  stringOne += String(denbora, 2);
  stringOne += F(",");
  abiaduraout = (altitudout - altueraoutz)/(denbora - denboraz);
  stringOne += String(abiaduraout, 2);
  stringOne += F(",");
  
  //Oxigenoa irakurri

  Vout = analogRead(A0); //Oxigenoa irakurri
  stringOne += String(Vout, 2); //Oxigenoaren sentsorearen sarrera bidali
  Vout = map(Vout, 0, calibrateO2, 0, 208); //Kalibratutako baliora mapeatu
  Vout = Vout/10; //Oxigenoa dezimaletara
  stringOne += String(Vout, 2); //Oxigenoa bidali
  stringOne += F(",");
  
  //Identifikadorea kalkulatu +1
  
  i=i+1;
  stringOne += String(i, 2);

  //SD-an gorde, eta bidali
  
  sd.listen();
  sd.println(stringOne);
  Serial.println(stringOne);
  delay(100);
}
