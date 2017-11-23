#include <Keypad.h>
#include <LiquidCrystal.h>  

int count = 0, simonAlarm[100], simonBoolean = 1;
int simonPattern = 0, answer;
long randNum;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // The pin address for the lcd screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // lcd pinning

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));  //New random seed each time
  lcd.begin(20, 4);
  lcd.setCursor(2,0);
  lcd.print("WELCOME TO SIMON!");
  delay(2000);
  lcd.clear();
}
  
void loop(){
  delay(1000);
  if (simonBoolean == 1){ //Checks user has not lost
    randNum = random(1,4);
    simonAlarm[count] = randNum;
    simonPattern += randNum;
    count++;
    
    for (int i = 0; i < count; i++){    //Generate a random pattern
      lcd.setCursor(i,0);
      lcd.print(simonAlarm[i]);
      delay(300);
    }

    delay(750);                     //"Clear Screen"
    lcd.clear();
    answer = 0;
    lcd.setCursor(0,0);
    lcd.print("Test: ");
    lcd.setCursor(5,0);
    lcd.print(simonPattern);
    delay(500);
    lcd.clear();

      char customKey = customKeypad.getKey();
      
      if (customKey){
        lcd.print(customKey);
      }
    
    if (answer == simonPattern){    //Check if pattern is correct
      lcd.print("Correct!");
      delay(1000);
      lcd.clear();
    } else {
      lcd.print("Incorrect!");
      lcd.print("You reached ");
      lcd.print(count);
      lcd.println(" sequences!");
      simonBoolean = 0;
    }

    simonPattern = simonPattern * 10;
    delay(1000);
  }
}

