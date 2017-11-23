int count = 0, simonAlarm[100], simonBoolean = 1;
int simonPattern = 0, answer;
long randNum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         //Setup Serial functions
  randomSeed(analogRead(0));  //New random seed each time
}

void loop() {
  delay(1000);
  if (simonBoolean == 1){ //Checks user has not lost
    randNum = random(1,4);
    simonAlarm[count] = randNum;
    simonPattern += randNum;
    count++;
    
    for (int i = 0; i < count; i++){    //Generate a random pattern
      Serial.print(simonAlarm[i]);
      Serial.print(" ");
      delay(300);
    }

    delay(750);                     //"Clear Screen"
   
    for (int i = 0; i < 30; i++){
      Serial.println("");
    }
    
    while(Serial.available() == 0);{  //Wait for user input
      answer = Serial.parseInt();
    }
    
    if (answer == simonPattern){    //Check if pattern is correct
      Serial.println("Correct!");
      delay(1000);
      for(int i = 0; i < 30; i++){
        Serial.println();
      }
    } else {
      Serial.println("Incorrect!");
      Serial.print("You reached ");
      Serial.print(count);
      Serial.println(" sequences!");
      simonBoolean = 0;
    }

    simonPattern = simonPattern * 10;
    delay(1000);
  }
}
