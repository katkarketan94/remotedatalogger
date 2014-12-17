
#include <glcd.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <fonts/allFonts.h>
#include "bitmaps/First.h"
#include <SD.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

SoftwareSerial mySerial(10, 3); //pin23,pin7  on 2560
int sensorPin = A0; //pin97 on 2560
const int chipSelect = 53;
 
void setup()
  {
    // Initialize the GLCD 
   GLCD.Init();

 // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  mySerial.begin(9600);  // the GPRS baud rate   
  Serial.begin(9600);    // the Serial Monitor baud rate 
  delay(500);
  
  Serial.print("Initializing SD card...");
  pinMode(53, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  
  }
 
void loop()
{
  
tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(3000);
  }
  delay(1000);

 
  
  GLCD.DrawBitmap(First, 0,0, BLACK); 
  delay(2500);
  GLCD.ClearScreen();
  

  //countdown(5); 
  //GLCD.ClearScreen();  
  //GLCD.DrawRoundRect(0,0,1,67, 1); //Rounded Rectangle
  GLCD.DefineArea( 0, 0, 107, 63, SCROLL_UP);
  GLCD.DrawLine( 108, 0, 108, 63, BLACK);
  
  //GLCD.DrawLine( 110, 2, 113, 10, BLACK);
  //GLCD.DrawLine( 108, 0, 108, 63, BLACK);
  //GLCD.DrawLine( 108, 0, 108, 63, BLACK);

  
  mySerial.println("AT+CREG?");
  Serial.println("AT+CREG?");
  GLCD.println("Reg Status");
  delay(1000); 
  ShowSerialData();
    
  mySerial.println("AT+CGATT?");
  Serial.println("AT+CGATT?");
  GLCD.println("GPRS status");
  delay(500);
  ShowSerialData();
  
  mySerial.println("AT+CIPSHUT");//bring up wireless connection
  Serial.println("AT+CIPSHUT");
  GLCD.println("Begin Wireless");
  delay(3000);
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  Serial.println("AT+CSTT=\"airtelgprs.com\"");
  GLCD.println("APN");
  delay(1000);
  ShowSerialData();
   
  mySerial.println("AT+CIICR");//bring up wireless connection
  Serial.println("AT+CIICR");
  GLCD.println("Bring up wireless");
  delay(3000);
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  Serial.println("AT+CIFSR");
  delay(2000);
  ShowSerialData();


    /*for(int counter=0; counter < 5;){ 
    int sensorValue = analogRead(sensorPin); 
        String datastring =;
         
        datastring += String(sensorValue);
        datastring += ",";
        datastring += String (tm.Hour);
        datastring += ":";
        datastring += String (tm.Minute);
        datastring += ":";
        datastring += String (tm.Second);
        datastring += ":";
        datastring += String (tm.Day);
        datastring += "/";
        datastring += String (tm.Year);
        
        GLCD.println(datastring);
        mySerial.println(datastring);
        
      
        File dataFile = SD.open("datalog.txt", FILE_WRITE);

        if (dataFile) {
          dataFile.println(datastring);
          dataFile.close();
          Serial.println(datastring);
                      }  
        else {
          Serial.println("error opening datalog.txt");
          Serial.println(datastring);
          GLCD.println(datastring);
          ShowSerialData();
              } 
      */  
  
  mySerial.println("AT+CIPSPRT=0");
  Serial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();

  mySerial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"8081\"");//start up the connection
  Serial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"8081\"");
  delay(2000);
 
  ShowSerialData();
   
 
  while(1){ 
  int sensorValue = analogRead(sensorPin); 
   if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
  
  //int sensorValue = analogRead(sensorPin); 
        String datastring;
         
        datastring += String(sensorValue);
        datastring += ",";
        datastring += String (tm.Hour);
        datastring += ":";
        datastring += String (tm.Minute);
        datastring += ":";
        datastring += String (tm.Second);
        datastring += ":";
        datastring += String (tm.Day);
        datastring += "/";
        datastring += String (tmYearToCalendar(tm.Year));
        
        GLCD.println(datastring);
        mySerial.println(datastring);
        
      
        File dataFile = SD.open("datalog.txt", FILE_WRITE);

        if (dataFile) {
          dataFile.println(datastring);
          dataFile.close();
          Serial.println(datastring);
                      }  
        else {
          Serial.println("error opening datalog.txt");
          Serial.println(datastring);
          GLCD.println(datastring);
          ShowSerialData(); 
        }
  
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  Serial.println("AT+CIPSEND");
  delay(1000);
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
  
  mySerial.print("[{\"id\": \"Pot\",\"current_value\" : \"");mySerial.print(sensorValue);mySerial.println("\"}]}}");
  delay(500);
  ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(6000);//waitting for reply, important! the time is base on the condition of internet 
  if(mySerial.read()==0)
   mySerial.println();
   ShowSerialData();
  }
  
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  ShowSerialData();
   
}
 
           void ShowSerialData() {
              String content = "";
              char character;
              for(int i=0; i<40; i++){
              character = mySerial.read();
              content.concat(character);
              delay(50);
                                }
              if (content != ""){
              GLCD.println(content);
                                }  
                            }

          void print2digits(int number) {
              if (number >= 0 && number < 10) {
              Serial.write('0');
                                              }
              Serial.print(number);
                                         }
