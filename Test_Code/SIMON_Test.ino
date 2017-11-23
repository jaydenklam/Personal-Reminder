int oneSimon;
int simonPattern, answer;
long randNum;

void setup() {
  // put your setup code here, to run once:
  oneSimon = 0;
  Serial.begin(9600);         //Setup Serial functions
  randomSeed(analogRead(0));  //New random seed each time
}

void loop() {
  if (oneSimon == 0){
    int simonAlarm[5];
    delay(500);
    
    for (int i = 0; i < 5; i++){    //Generate a random pattern
      randNum = random(1, 4);
      simonAlarm[i] = randNum;
      Serial.print(simonAlarm[i]);
    }

    delay(600);                     //"Clear Screen"
   
    for (int i = 0; i < 30; i++){
      Serial.println("");
    }

    simonPattern = 10000*simonAlarm[0] + 1000*simonAlarm[1] + 100*simonAlarm[2] + 10*simonAlarm[3] + simonAlarm[4];

    while(Serial.available() == 0);{  //Wait for user input
      answer = Serial.parseInt();
    }
    
    if (answer == simonPattern){    //Check if pattern is correct
      Serial.println("Correct!");
    } else {
      Serial.println("Incorrect!");
    }

    oneSimon++; //Ensure SIMON game runs once
  }
}
