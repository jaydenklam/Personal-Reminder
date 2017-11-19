#include <Wire.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

 /*The LCD circuit:
 * LCD GND pin to GND pin
 * LCD VCC pin to 5V pin
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2  
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/
 /*The DS3231 circuit:
  * DS3231 GND pin to GND pin
  * DS3231 VCC pin to 5V pin
  * DS3231 SDA pin to A4 pin
  * DS3231 SCL pin to A5 pin
  */
 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
DS3231 rtc(SDA, SCL);
  //int h = 11; 
  //int m = 59; 
  //int s = 45; 
  //int flag = h;  
  void setup() 
  {
   rtc.begin();
   lcd.begin(20,4);
    //rtc.setDOW(SUNDAY);
    //rtc.setTime(15, 13, 00);
    //rtc.setDate(19, 11, 2017);
  } 
  void loop() 
  { 
    lcd.setCursor(6,0);
    lcd.print(rtc.getTimeStr());
    lcd.setCursor(0,1);
    lcd.print(rtc.getDOWStr());
    lcd.setCursor(10,1);
    lcd.print(rtc.getDateStr());
    lcd.setCursor(0,2);
    lcd.print("Room Temp: ");
    lcd.print(rtc.getTemp());
    lcd.print(" C");
    delay(1000);
    lcd.clear();
    /*lcd.setCursor(0,0); 
    s = s + 1; 
    lcd.print("Time: ");
    if(h >= 13) 
    { 
     h = h - 12; 
    }
    if(h < 10){
      lcd.print("0");
      lcd.print(h);
    }
    else{
      lcd.print(h);
    }
    lcd.print(":");
    if(m < 10){
      lcd.print("0");
      lcd.print(m); 
    }
    else{
      lcd.print(m);
    }
    lcd.print(":");
    if(s < 10){
      lcd.print("0");
      lcd.print(s); 
    }
    else{
      lcd.print(s); 
    }
    if(flag < 12){
      lcd.print("AM"); 
    }
    if(flag == 12){
      lcd.print("PM"); 
    }
    if(flag == 24){
      lcd.print("AM");
      flag = 0;
    }
    if(flag > 12){
      lcd.print("PM"); 
    }
    delay(1000); 
    lcd.clear();
     
    if(s == 59){ 
     s = -1; 
     m = m + 1; 
    }
     
    if(m == 60){ 
     m = 0; 
     h = h + 1; 
     flag = flag + 1; 
    }  
    lcd.setCursor(0,1); 
    lcd.print("HAVE A NICE DAY");*/
  } 
