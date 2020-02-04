// Grove - Gas Sensor(O2) test code
// Note:
// 1. It need about about 5-10 minutes to preheat the sensor
// 2. modify VRefer if needed
    float Vout =0;
    int calibrateO2 = 93;        //////////////////////////////////////////////change the value and the line 6 lines lower for manual calibration
void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Grove - Gas Sensor Test Code...");
    calibrateO2 = analogRead(Vout);          ///////////////////////////////////////make this line a comment for manual calibration
}

void loop() 
{
    // put your main code here, to run repeatedly:
    Vout = analogRead(A0);
    Serial.print("Vout =");
    Serial.print(Vout);
    Serial.print(" V, Concentration of O2 is ");
    Vout = map(Vout, 0, calibrateO2, 0, 208);
    Serial.println(Vout/10);
    delay(500);
}
