/*Note: this code is a demo for how to using gprs shield to send sms message, dial a voice call and 
  send a http request to the website, upload data to pachube.com by TCP connection,
 
  The microcontrollers Digital Pin 7 and hence allow unhindered
  communication with GPRS Shield using SoftSerial Library. 
  IDE: Arduino 1.0 or later
  Replace the following items in the code:
  1.Phone number, don't forget add the country code
  2.Replace the Access Point Name
  3. Replace the Pachube API Key with your personal ones assigned
  to your account at cosm.com
  */
 
 
#include <SoftwareSerial.h>
#include <String.h>
 
SoftwareSerial mySerial(10, 3);
 
void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  delay(500);
}
 
void loop()

{
  mySerial.println("AT+CREG?");
  Serial.println("AT+CREG?");
  delay(500);
 
  ShowSerialData();
 
  
  mySerial.println("AT+CGATT?");
  Serial.println("AT+CGATT?");
  delay(500);
 
  ShowSerialData();
 
  
 
 
///send2Pachube()///
///this function is to send the sensor data to the pachube, you can see the new value in the pachube after execute this function///

  mySerial.println("AT+CGATT?");
  Serial.println("AT+CGATT?");
  delay(1000);
 
  ShowSerialData();
 
 mySerial.println("AT+CIPSHUT");//bring up wireless connection
  Serial.println("AT+CIPSHUT");
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  Serial.println("AT+CSTT=\"bsnlnet\"");
  delay(1000);
 
  ShowSerialData();
  
  
  
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  Serial.println("AT+CIICR");
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  Serial.println("AT+CIFSR");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  Serial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"80\"");//start up the connection
  Serial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"80\"");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  Serial.println("AT+CIPSEND");
  delay(4000);
  ShowSerialData();
  
  String pot = "103";
  
  mySerial.print("{\"method\": \"put\",\"resource\": \"/feeds/1198901478/\",\"params\"");//here is the feed you apply from pachube
  delay(500);
  ShowSerialData();
  mySerial.print(": {},\"headers\": {\"X-PachubeApiKey\":");//in here, you should replace your pachubeapikey
  delay(500);
  ShowSerialData();
  mySerial.print(" \"RxDtavgd84MKtJIMK1R4xZ4jwANT6z25XA0DYV3GYOeOaYsR");//pachubeapikey
  delay(500);
  ShowSerialData();
 
  mySerial.print(" {\"version\": \"1.0.0\",\"datastreams\": ");
  delay(500);
  ShowSerialData();
  mySerial.println("{\"id\": \"Pot\",\"current_value\": \"" + pot + "\"}]},\"token\": \"lee\"}");
 
 
  delay(500);
  ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
 
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  ShowSerialData();
}
 
void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}
