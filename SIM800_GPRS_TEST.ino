#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CFUN=1"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CPIN?"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();

  /*Setup GPRS*/
  
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"ppwap\""); //Set APN
  updateSerial();
  mySerial.println("AT+SAPBR=1,1"); //Start GPRS Connection 
  updateSerial();
  delay(2000);
  mySerial.println("AT+SAPBR=2,1"); //Test IP
  updateSerial();

  /*Start http COnnection */

  mySerial.println("AT+HTTPINIT"); //Start http
  updateSerial();
  mySerial.println("AT+HTTPPARA=\"CID\",1"); //Set connection type 
  updateSerial();
  
  //mySerial.println("AT+HTTPSSL=1"); //Uncomment this if your URL is https 
  //updateSerial();
  
  mySerial.println("AT+HTTPPARA=\"URL\",\"http://sandro.awardspace.info/php/hola.php?hello_world\""); //Set URL
  updateSerial();
  mySerial.println("AT+HTTPACTION=1"); //Download data
  updateSerial();
  delay(5000);
  mySerial.println("AT+HTTPREAD"); //Read data
  updateSerial();
  delay(5000);
  mySerial.println("AT+HTTPTERM"); //Terminate http connection
  updateSerial();
  mySerial.println("AT+SAPBR=0,1"); //Terminate gprs connection
  updateSerial();
  
 
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
