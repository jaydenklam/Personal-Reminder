#include <LiquidCrystal.h>
#include <DS3231.h> // Library from http://www.rinkydinkelectronics.com/library.php?id=73
#include <Keypad.h> // Library from https://playground.arduino.cc/Code/Keypad#Download

//Wire Configurations
 /*The LCD circuit:
 * LCD GND pin to GND pin
 * LCD VCC pin to 5V pin
 * LCD RS pin to digital pin 13
 * LCD Enable pin to digital pin 12
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
   * Buzzer I/O pin to pin 7
   * Buzzer VCC pin to 5V pin
   */

  /*The Keypad Module (from left to right):
   * Row1 to D11
   * Row2 to D10
   * Row3 to D9
   * Row4 to D8
   * Col1 to D6
   * Col2 to A2
   * Col3 to A3
   */
 
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // The pin address for the lcd screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // lcd pinning
DS3231 rtc(SDA, SCL); // DS3231 pinning
Time t;
const int buzzerPin = 7; // The pin address for Piezo Buzzer
long randNum; //For SIMON
int count = 0;
int shortNote = 400, longNote = 800;  //For tunes

// keypad type definitions
const byte ROWS = 4; //four rows //Buzzer UCC to D7
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = //Button mapping
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {
  11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  6, A2, A3}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Initialize a keypad
 
void setup(){
   //Serial.begin(9600); //Debugging
   rtc.begin(); // Activate DS3231 for track time and record temperature
   lcd.begin(20,4); // Activate lcd to display
   pinMode(buzzerPin, OUTPUT); // Piezo Buzzer pinning
   //rtc.setDOW(THURSDAY); // Initial Setting Day Of Week on DS3231          //SETTING INITIAL TIME----------------------------------------
   //rtc.setTime(01, 05, 55); // Initial Setting Time                  
   //rtc.setDate(23, 11, 2017); // Initial Setting Date DD/MM/YYYY
   randomSeed(analogRead(A0));  //New random seed each time (for SIMON)
  
   delay(500);  //Intro screen
   lcd.setCursor(7,0);
   lcd.print("Anish");
   lcd.setCursor(7,1);
   lcd.print("Jayden");
   lcd.setCursor(6,2);
   lcd.print("Shisheer");
   lcd.setCursor(0,3);
   lcd.print("Fall 2017 SE Project");
  
   tone(buzzerPin, 1046, 200);  //Intro jingle
   delay(300);
   tone(buzzerPin, 1318, 200);
   delay(300);
   tone(buzzerPin, 1568, 200);
   delay(300);
   tone(buzzerPin, 2093, 200);
   delay(300);
   
   delay(1000);
   lcd.clear();
} 
  
void loop(){
  lcd.clear();  //Clear screen of any leftover text
  t = rtc.getTime(); // t is assigned the current time from the DS3231.
  //The 26 if statements below compare the current time of DS3231 to the reminder time of each event in a continuous loop. 
  //If match is found then the loop is broken and code enters the corresponding function.
  //MONDAY
  if(t.hour == 7 && t.min == 00 && t.sec == 00 && t.dow == MONDAY)Morning();
  if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH117Tutorial();
  if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH135Lecture();
  if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)ECE105Lecture();
  if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)MATH117Lecture();
  if(t.hour == 15 && t.min == 20 && t.sec == 00 && t.dow == MONDAY)CS137Lecture();
  if(t.hour == 00 && t.min == 00 && t.sec == 00 && t.dow == TUESDAY)Night();

  //TUESDAY
  if(t.hour == 7 && t.min == 00 && t.sec == 00 && t.dow == TUESDAY)Morning();
  if(t.hour == 9 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)CS137Tutorial();
  if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)MATH135Lecture();
  if(t.hour == 12 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)SE101Lecture();
  if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)SE101Lecture();
  if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == TUESDAY)MATH115Lecture();
  if(t.hour == 00 && t.min == 00 && t.sec == 00 && t.dow == WEDNESDAY)Night();

  //WEDNESDAY
  if(t.hour == 7 && t.min == 00 && t.sec == 00 && t.dow == WEDNESDAY)Morning();
  if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH115Tutorial();
  if(t.hour == 9 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH115Lecture();
  if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH135Lecture();
  if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)ECE105Lecture();
  if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)CS137Lecture();
  if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == WEDNESDAY)MATH117Lecture();
  if(t.hour == 00 && t.min == 00 && t.sec == 00 && t.dow == THURSDAY)Night();

  //THURSDAY
  if(t.hour == 7 && t.min == 00 && t.sec == 00 && t.dow == THURSDAY)Morning();
  if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)ECE105Lab();
  if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)SE101Lab();
  if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == THURSDAY)MATH115Lecture();
  if(t.hour == 00 && t.min == 00 && t.sec == 00 && t.dow == FRIDAY)Night();

  //FRIDAY
  if(t.hour == 7 && t.min == 00 && t.sec == 00 && t.dow == FRIDAY)Morning();
  if(t.hour == 8 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)ECE105Tutorial();
  if(t.hour == 10 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH135Lecture();
  if(t.hour == 11 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)ECE105Lecture();
  if(t.hour == 13 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)CS137Lecture();
  if(t.hour == 14 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH117Lecture();
  if(t.hour == 15 && t.min == 20 && t.sec == 00 && t.dow == FRIDAY)MATH115Lecture();
  if(t.hour == 00 && t.min == 00 && t.sec == 00 && t.dow == SATURDAY)Night();
  
  // Below is the display template.
  // The time is displayed first and is center aligned on the screen.
  lcd.setCursor(6,0);
  lcd.print(rtc.getTimeStr());
  // The Day Of Week is displayed second and is left aligned.
  lcd.setCursor(0,1);
  lcd.print(rtc.getDOWStr());
  // The Date is displayed third and is right aligned.
  lcd.setCursor(10,1);
  lcd.print(rtc.getDateStr());
  //The room tmperature is displayed last.
  lcd.setCursor(0,2);
  lcd.print("Room Temp: ");
  lcd.print(rtc.getTemp());
  lcd.print(" C");
  // Screen is refreshed after every second.
  delay(1000);
  lcd.clear();
}


//Reminder tone function
void reminderTone(){
  tone(buzzerPin, 1568, 100);
  delay(100);
  tone(buzzerPin, 1319, 100);
  delay(100);
  tone(buzzerPin, 1568, 100);
  delay(100);
  tone(buzzerPin, 1319, 100);
  delay(100);
}

// Below are 12 functions that correspond to the 26 if statements in the loop.
void Morning(){  //Morning alarm function which displays a "wake-up" message and sounds the buzzer endlessly until the alarm is deactivated by completing the 4 digit SIMON game.
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Rise and Shine!"); //Initial display message
  lcd.setCursor(2,2); 
  lcd.print("Press # to wake");

  while (true){   //Check for pressing #
    tone(buzzerPin, 1318);  //Alarm tone
    delay(50);
    noTone(buzzerPin);
    char key = keypad.getKey();
  
    if (key == '#'){
      noTone(buzzerPin);  //Snooze alarm
      lcd.clear();
      lcd.setCursor(3,0); 
      lcd.print("Good Morning!"); //Game introduction
      lcd.setCursor(0,1);
      lcd.print("Follow the pattern!");
      delay(2000);
      lcd.clear();

      int simonAlarm[4];  //Simon alarm array

      for (int i = 0; i < 4; i++){  //Generate and display a random four number pattern on screen of the interval [1,9]
        randNum = random(1,10);
        simonAlarm[i] = randNum;
        lcd.setCursor(10,i);
        lcd.print(randNum);
        delay(900); //Delay between numbers, change to change difficulty
        lcd.clear();
      }

      int simonAnswer[4]; //User answer array
      count = 0;

      while (count < 4){ //Takes in user-inputted pattern
        char key = keypad.getKey();

        if (key){
          simonAnswer[count] = key - '0';
          lcd.setCursor(10, count);
          lcd.print(key);
          count++;
        }
      }

      delay(300);
      lcd.clear();

      if ((simonAlarm[0] == simonAnswer[0]) && (simonAlarm[1] == simonAnswer[1]) && (simonAlarm[2] == simonAnswer[2]) && (simonAlarm[3] == simonAnswer[3])){
        tone(buzzerPin, 2637, 200);
        delay(200);
        tone(buzzerPin, 3136, 200);
        delay(200);
        tone(buzzerPin, 4186, 200);
        delay(200);
        return;
      } else {
        lcd.setCursor(6,0);
        lcd.print("Incorrect!");
        lcd.setCursor(0,3);
        lcd.print("Press # to try again");
        delay(1000);  //Short lockout
      }
    }
  }
}

void Night(){ //Twinkle Twinkle Little Star
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("It's 12:00!");
  lcd.setCursor(4,1);  
  lcd.print("Good night!");
  lcd.setCursor(0,2);  
  lcd.print("*      *     *     *");
  lcd.setCursor(0,3);  
  lcd.print(" *    *     *     * ");
  
  tone(buzzerPin, 1046, shortNote); //C6
  delay(shortNote);
  tone(buzzerPin, 1046, shortNote); //C6
  delay(shortNote);
  tone(buzzerPin, 1568, shortNote); //G6
  delay(shortNote);
  tone(buzzerPin, 1568, shortNote); //G6
  delay(shortNote);
  tone(buzzerPin, 1760, shortNote); //A6
  delay(shortNote);
  tone(buzzerPin, 1760, shortNote); //A6
  delay(shortNote);
  tone(buzzerPin, 1568, longNote);  //G6
  delay(longNote);
  tone(buzzerPin, 1397, shortNote); //F6
  delay(shortNote);
  tone(buzzerPin, 1397, shortNote); //F6
  delay(shortNote);
  tone(buzzerPin, 1319, shortNote); //E6
  delay(shortNote);
  tone(buzzerPin, 1319, shortNote); //E6
  delay(shortNote);
  tone(buzzerPin, 1175, shortNote); //D6
  delay(shortNote);
  tone(buzzerPin, 1175, shortNote); //D6
  delay(shortNote);
  tone(buzzerPin, 1046, shortNote); //C6
  delay(shortNote);

  delay(500);
  lcd.clear();
}

// In general, these functions clear the previously displayed data from the lcd screen, then print the approriate message according to the event.
// These functions also sounds the buzzer twice as an alarm while the event message is displayed.
void MATH117Tutorial(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("MATH 117 Tutorial");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();           
}

void MATH135Lecture(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("MATH 135 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();       
}

void ECE105Lecture(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("ECE 105 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void MATH117Lecture(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("MATH 117 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void CS137Lecture(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("CS 137 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void CS137Tutorial(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("CS 137 Tutorial");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void SE101Lecture(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SE 101 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();       
}

void MATH115Lecture(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("MATH 115 Lecture");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();       
}

void MATH115Tutorial(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("MATH 115 Tutorial");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void ECE105Lab(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("ECE 105 Lab");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void SE101Lab(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SE 101 Lab");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();      
}

void ECE105Tutorial(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("ECE 105 Tutorial");
  lcd.setCursor(4,2);  
  lcd.print("Begins now!");
  reminderTone();
  delay(2000);
  lcd.clear();
  loop();        
}
