#include <Wire.h>
#include <LiquidCrystal.h>
#include <DS3231.h> // Library from http://www.rinkydinkelectronics.com/library.php?id=73
#include <Time.h> // Library downloaded from Arduino IDE

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
 * wiper to LCD VO pin (pin 3)
 */
 
 /*The DS3231 circuit:
  * DS3231 GND pin to GND pin
  * DS3231 VCC pin to 5V pin
  * DS3231 SDA pin to A4 pin
  * DS3231 SCL pin to A5 pin
  */
  
  /*The Piezo Buzzer circuit:
   * Buzzer GND pin to GND pn
   * Buzzer I/O pin to pin 9
   * Buzzer VCC pin to 5V pin
   */
 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // The pin address for the lcd screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // lcd pinning
DS3231 rtc(SDA, SCL); // DS3231 pinning
Time t;
const int buzzerPin = 9; // The pin address for Piezo Buzzer
 
  void setup(){
   rtc.begin(); // Activate DS3231 for track time and record temperature
   lcd.begin(20,4); // Activate lcd to display
   pinMode(buzzerPin, OUTPUT); // Piezo Buzzer pinning
    rtc.setDOW(MONDAY); // Setting Day Of Week on DS3231
    rtc.setTime(14, 19, 45); // Setting Time
    rtc.setDate(20, 11, 2017); // Setting Date DD/MM/YYYY
  } 
  
  void loop(){
    t = rtc.getTime(); // t is assigned the current time from the DS3231
    //The 26 if statements below compare the current time of DS3231 to the reminder time of each event in a continuous loop. 
    //If match is found then the loop is broken and code enters the corresponding function.
    if(t.hour == 7 && t.min == 30 && t.sec == 00 && t.dow == MONDAY)Morning();
    if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH117Tutorial();
    if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH135Lecture1();
    if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)ECE105Lecture1();
    if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH117Lecture1();
    if(t.hour == 15 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)CS137Lecture1();
    if(t.hour == 9 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)CS137Tutorial();
    if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)MATH135Lecture2();
    if(t.hour == 12 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)SE101Lecture1();
    if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)SE101Lecture1();
    if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)MATH115Lecture1();
    if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH115Tutorial();
    if(t.hour == 9 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH115Lecture2();
    if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH135Lecture3();
    if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)ECE105Lecture2();
    if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)CS137Lecture2();
    if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH117Lecture2();
    if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)ECE105Lab();
    if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)SE101Lab();
    if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)MATH115Lecture3();
    if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)ECE105Tutorial();
    if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH135Lecture4();
    if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)ECE105Lecture3();
    if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)CS137Lecture3();
    if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH117Lecture3();
    if(t.hour == 15 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH115Lecture3();
    // Below is the display template.
    // The time is displayed first and is center aligned on the screen.
    lcd.setCursor(6,0);
    lcd.print(rtc.getTimeStr());
    // The Day Of Week is displayed second and is left aligned.
    lcd.setCursor(0,1);
    lcd.print(rtc.getDOWStr());
    // The Date is displayed third and is right aligned
    lcd.setCursor(10,1);
    lcd.print(rtc.getDateStr());
    //The room tmperature is displayed last
    lcd.setCursor(0,2);
    lcd.print("Room Temp: ");
    lcd.print(rtc.getTemp());
    lcd.print(" C");
    // Screen is refreshed after every second
    delay(1000);
    lcd.clear();
  }
// Below are 26 functions that correspond to the 26 if statements in the loop.
// In general, these functions clear the previously displayed data from the lcd screen, then print the approriate message according to the event.
// These functions then enter the Buzz function, where the message for the particular event contiues to display for 5 seconds and is accompanied by an Alarm sound for the same duration.
void Morning(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rise and Shine!");
  Buzz();    
}

void MATH117Tutorial(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 117 Tutorial");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");
  Buzz();           
}
void MATH135Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 135 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz();  
}
void ECE105Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ECE 105 Lecture");
  lcd.setCursor(0,2);   
  lcd.print("begins now!");           
  Buzz();  
}
void MATH117Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MATH 117 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");   
  Buzz(); 
}
void CS137Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MATH 117 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz();  
}

void CS137Tutorial(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CS 137 Tutorial"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz();  
}
void MATH135Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 135 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz();  
}
void SE101Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SE 101 Lecture"); 
  lcd.setCursor(0,2);   
  lcd.print("begins now!");          
  Buzz();  
}
void SE101Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SE101 Lecture");
  lcd.setCursor(0,2);     
  lcd.print("begins now!");         
  Buzz(); 
}
void MATH115Lecture1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MATH 115 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz();  
}

void MATH115Tutorial(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 115 Tutorial");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz(); 
}
void MATH115Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 115 Lecture");
  lcd.setCursor(0,2);   
  lcd.print("begins now!");           
  Buzz();  
}
void MATH135Lecture3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 135 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz(); 
}
void ECE105Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ECE 105 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz();  
}
void CS137Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CS 137 Lecture"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz(); 
}
void MATH117Lecture2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 117 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");            
  Buzz(); 
}

void ECE105Lab(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ECE 105 Lab"); 
  lcd.setCursor(0,2);   
  lcd.print("begins now!");          
  Buzz(); 
}
void SE101Lab(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SE 101 Lab"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz(); 
}
void MATH115Lecture3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 115 Lecture");
  lcd.setCursor(0,2);   
  lcd.print("begins now!");           
  Buzz();  
}

void ECE105Tutorial(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ECE 105 Tutorial"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz(); 
}
void MATH135Lecture4(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 135 Lecture"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz();   
}
void ECE105Lecture3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ECE 105 Lecture");
  lcd.setCursor(0,2);   
  lcd.print("begins now!");           
  Buzz(); 
}
void CS137Lecture3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CS 137 Lecture"); 
  lcd.setCursor(0,2);  
  lcd.print("begins now!");           
  Buzz(); 
}
void MATH117Lecture3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 117 Lecture");
  lcd.setCursor(0,2);    
  lcd.print("begins now!");          
  Buzz();  
}
void MATH115Lecture4(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Math 115 Lecture");
  lcd.setCursor(0,2);  
  lcd.print("begins now!");          
  Buzz(); 
}
// This is the Buzz function where the message from the previous function continues to display on the lcd screen with simultaneous pulse of alarm sound for total of 5 seconds.
void Buzz(){
  tone(buzzerPin, 1000, 1000);
  noTone(buzzerPin);
  delay(1000);
  tone(buzzerPin, 1000, 1000);
  noTone(buzzerPin);
  delay(1000);
  tone(buzzerPin, 1000, 1000);
  lcd.clear();
  loop();
}
