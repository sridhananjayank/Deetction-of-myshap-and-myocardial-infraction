#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
SoftwareSerial mySerial(9, 10); /* 9-Tx and 10 -Rx of SIM800A*/
float checkx,checky,checkz;

void setup(void) 
{
   mySerial.begin(9600); //setting the baud rate for GSM module
   Serial.begin(9600); 
   delay(100); 
   if(!accel.begin())
   {
      Serial.println("Alert");
      while(1);
   }
}
void loop(void) 

{
   sensors_event_t event; 
   accel.getEvent(&event);
   checkx=event.acceleration.x;
   checky=event.acceleration.y;
   checkz=event.acceleration.z;
   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
   Serial.println("m/s^2 ");
   if((checkx<0)&&(checky<0)&&(checkz<0))
   {
    SendMessage();
   }
   delay(500);

}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919123456785\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}