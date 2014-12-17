#include <SoftwareSerial.h>
#include <String.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
SoftwareSerial mySerial(10, 3);
int sensorPin = A0;
 
void setup()
{
  lcd.begin(16, 2);
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  delay(500);
}
 
void loop()
{
  mySerial.println("AT+CREG?");
  delay(500);
  if(mySerial.available()==0)
  {
    lcd.print("MT is not currently searching a new operator to register to"); 
    mySerial.println("AT+CREG?");
    delay(500);
  }
 if(mySerial.available()==1)
  {
  lcd.print("Registered, Home Network !!!");
  mySerial.println("AT+CGATT?");
  delay(1500);
  ShowSerialData();
 
  mySerial.println("AT+CIPSHUT");//bring up wireless connection
  delay(3000);
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
  ShowSerialData();
   
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000); 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000); 
  ShowSerialData();
   
  mySerial.println("AT+CIPSPRT=0");
  delay(3000); 
  ShowSerialData();
 
  mySerial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"8081\"");//start up the connection
  delay(2000);
  ShowSerialData();
  
  while(1)
  { 
   int sensorValue = analogRead(sensorPin);  
    
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
    
  mySerial.print("{\"method\": \"put\",\"resource\": \"/feeds/1198901478.json/\",\"params\"");//here is the feed you apply from pachube
  delay(500);
  ShowSerialData();
  mySerial.print(": {},\"headers\": {\"X-ApiKey\":");//in here, you should replace your pachubeapikey
  delay(500);
  ShowSerialData();
  mySerial.print("\"RxDtavgd84MKtJIMK1R4xZ4jwANT6z25XA0DYV3GYOeOaYsR\"");//pachubeapikey
  delay(500);
  ShowSerialData();
  mySerial.print("},\"body\":");
  delay(500);
  ShowSerialData();
  mySerial.print(" {\"version\": \"1.0.0\",\"datastreams\":");
  delay(500);
  ShowSerialData();
  mySerial.print("[{\"id\": \"Pot\",\"current_value\" : \"");
  mySerial.print(sensorValue);
  mySerial.println("\"}]}}");
  delay(500);
  ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(6000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
  ShowSerialData();
 }
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  ShowSerialData();
 }
 }

 
void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}
