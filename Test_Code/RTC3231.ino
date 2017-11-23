#include <Wire.h>
#include "ds3231.h" //External library
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7); 

#define BUFF_MAX 128

uint8_t time[8];
char recv[BUFF_MAX];
unsigned int recv_size = 0;
unsigned long prev, interval = 1000;

void setup() //Serial communication with computer
{
    Serial.begin(9600); //Opens serial port, sets data rate to 9600 bps
    Wire.begin(); //Initiate the Wire library and join the I2C bus
    DS3231_init(DS3231_INTCN);
    memset(recv, 0, BUFF_MAX);
    Serial.println("GET time");
    lcd.begin(20, 4); //Initialise the 20x4 lcd screen
    lcd.clear(); //Clear 20x4 lcd screen
    
    Serial.println("Setting time"); //Comment these two lines once the time has been set
    parse_cmd("T300021426102017",16); //Time string
}

void loop()
{
    char in;
    char tempF[6];
    float temperature;
    char buff[BUFF_MAX];
    unsigned long now = millis();
    struct ts t;

    //Display time once every second (1000ms interval)
    if ((now - prev > interval) && (Serial.available() <= 0)) {
        DS3231_get(&t); //Gets updated time
        parse_cmd("C",1); //Temperature string
        temperature = DS3231_get_treg(); //Get temperature
        dtostrf(temperature, 5, 1, tempF); //Convert temperature into a string

        lcd.clear(); //Clear 20x4 lcd every second
        lcd.setCursor(1,0); //Set cursor to 1st line of 20x4 lcd
        
        lcd.print(t.mday); //Print day of month
        
        printMonth(t.mon); //Print month, this goes to printMonth function below
        
        lcd.print(t.year); //Print year
        
        lcd.setCursor(0,1); //Set cursor to 2nd line of 20x4 lcd
        lcd.print(t.hour); //Print hour
        lcd.print(":");
        if(t.min<10) //If min is less than 10, program will print 0 first then the single digit minute. Otherwise it prints double digit minute as is
        {
          lcd.print("0");
        }
        lcd.print(t.min);
        lcd.print(":");
        if(t.sec<10) //If seconds is less than 10, program will print 0 first then the single digit second. Otherwise it prints double digit second as is
        {
          lcd.print("0");
        }
        lcd.print(t.sec);
        
        lcd.print(' ');
        lcd.print(tempF); //Print temperature with appropriate formating
        lcd.print((char)223);
        lcd.print("C ");
        prev = now;
    }

    
    if (Serial.available() > 0) { //Check if there is new data in there is new data in the serial communication
        in = Serial.read();

        if ((in == 10 || in == 13) && (recv_size > 0)) {
            parse_cmd(recv, recv_size);
            recv_size = 0;
            recv[0] = 0;
        } else if (in < 48 || in > 122) {;
        } else if (recv_size > BUFF_MAX - 2) { //Drops the lines that are too long for the 20x4 lcd using the BUFF_MAX, which was set to 128
            // drop
            recv_size = 0;
            recv[0] = 0;
        } else if (recv_size < BUFF_MAX - 2) {
            recv[recv_size] = in;
            recv[recv_size + 1] = 0;
            recv_size += 1;
        }

    }
}

void parse_cmd(char *cmd, int cmdsize)
{ // unsigned integers of 8 bits used
    uint8_t i;
    uint8_t reg_val;
    char buff[BUFF_MAX];
    struct ts t;

    //snprintf(buff, BUFF_MAX, "cmd was '%s' %d\n", cmd, cmdsize);
    //Serial.print(buff);

    // Time is set according to the string provided above in the form T ss mm hh W DD MM YYYY
    if (cmd[0] == 84 && cmdsize == 16) {
        //T300021426102017
        t.sec = inp2toi(cmd, 1);
        t.min = inp2toi(cmd, 3);
        t.hour = inp2toi(cmd, 5);
        t.wday = inp2toi(cmd, 7);
        t.mday = inp2toi(cmd, 8);
        t.mon = inp2toi(cmd, 10);
        t.year = inp2toi(cmd, 12) * 100 + inp2toi(cmd, 14);
        DS3231_set(t);
        Serial.println("OK");
    }
    // Calculates time to appropriate 24 hour clcok format 
    else if (cmd[0] == 49 && cmdsize == 1) {  // "1" get alarm 1
        DS3231_get_a1(&buff[0], 59);
        Serial.println(buff);
    } else if (cmd[0] == 50 && cmdsize == 1) {  // "2" get alarm 1
        DS3231_get_a2(&buff[0], 59);
        Serial.println(buff);
    } else if (cmd[0] == 51 && cmdsize == 1) {  // "3" get aging register
        Serial.print("aging reg is ");
        Serial.println(DS3231_get_aging(), DEC);
    } else if (cmd[0] == 65 && cmdsize == 9) {  // "A" set alarm 1
        DS3231_set_creg(DS3231_INTCN | DS3231_A1IE);
        //A SS MM HH DD
        for (i = 0; i < 4; i++) {
            time[i] = (cmd[2 * i + 1] - 48) * 10 + cmd[2 * i + 2] - 48; // Sets the ss, mm, hh, dd format 
        }
        byte flags[5] = { 0, 0, 0, 0, 0 };
        DS3231_set_a1(time[0], time[1], time[2], time[3], flags);
        DS3231_get_a1(&buff[0], 59);
        Serial.println(buff);
    } else if (cmd[0] == 66 && cmdsize == 7) {  // "B" Set Alarm 2
        DS3231_set_creg(DS3231_INTCN | DS3231_A2IE);
        //B MM HH DD
        for (i = 0; i < 4; i++) {
            time[i] = (cmd[2 * i + 1] - 48) * 10 + cmd[2 * i + 2] - 48; // mm, hh, dd
        }
        byte flags[5] = { 0, 0, 0, 0 };
        DS3231_set_a2(time[0], time[1], time[2], flags);
        DS3231_get_a2(&buff[0], 59);
        Serial.println(buff);
    } else if (cmd[0] == 67 && cmdsize == 1) {  // "C" Gets temperature register
        Serial.print("temperature reg is ");
        Serial.println(DS3231_get_treg(), DEC);
    } else if (cmd[0] == 68 && cmdsize == 1) {  // "D" Reset status register alarm
        reg_val = DS3231_get_sreg();
        reg_val &= B11111100;
        DS3231_set_sreg(reg_val);
    } else if (cmd[0] == 70 && cmdsize == 1) {  // "F" Custom function
        reg_val = DS3231_get_addr(0x5);
        Serial.print("orig ");
        Serial.print(reg_val,DEC);
        Serial.print("month is ");
        Serial.println(bcdtodec(reg_val & 0x1F),DEC);
    } else if (cmd[0] == 71 && cmdsize == 1) {  // "G" Set aging status register
        DS3231_set_aging(0);
    } else if (cmd[0] == 83 && cmdsize == 1) {  // "S" Get status register
        Serial.print("status reg is ");
        Serial.println(DS3231_get_sreg(), DEC);
    } else {
        Serial.print("unknown command prefix ");
        Serial.println(cmd[0]);
        Serial.println(cmd[0], DEC);
    }
}

void printMonth(int month)
{
  switch(month) //Prints the appropriate month on 20x4 lcd depending on case 
  {
    case 1: lcd.print(" January ");break;
    case 2: lcd.print(" February ");break;
    case 3: lcd.print(" March ");break;
    case 4: lcd.print(" April ");break;
    case 5: lcd.print(" May ");break;
    case 6: lcd.print(" June ");break;
    case 7: lcd.print(" July ");break;
    case 8: lcd.print(" August ");break;
    case 9: lcd.print(" September ");break;
    case 10: lcd.print(" October ");break;
    case 11: lcd.print(" November ");break;
    case 12: lcd.print(" December ");break;
    default: lcd.print(" Error ");break;
  } 
}
