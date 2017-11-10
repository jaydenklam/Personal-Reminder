int simonBoolean = 1, patternNum = 1;
int placePattern, simonPattern, answer;
long randNum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         //Setup Serial functions
  randomSeed(analogRead(0));  //New random seed each time
}

void loop() {
  delay(1000);
  if (simonBoolean == 1){
    int simonAlarm[patternNum];
    simonPattern = 0;
  
    placePattern = pow(10, patternNum - 1);
    
    for (int i = 0; i < patternNum; i++){    //Generate a random pattern
      randNum = random(1, 4);
      simonAlarm[i] = randNum;
      Serial.print(simonAlarm[i]);
      Serial.print(" ");
      simonPattern += simonAlarm[i] * placePattern;
      placePattern /= 10;
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
    } else {
      Serial.println("Incorrect!");
      Serial.print("You reached ");
      Serial.print(patternNum);
      Serial.println(" sequences!");
      simonBoolean = 0;
    }
  
    patternNum++;
    delay(1000);
  }
}
