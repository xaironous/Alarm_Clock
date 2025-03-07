#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2); // Display  I2C 
RTC_DS1307 RTC;

//*****Button******//
int P1=6; // Button SET MENU'
int P2=7; // Button +
int P3=8; // Button -
int P4=9; // SWITCH Alarm

//*****Alarm******//
#define buzzer 10

//*****Variables*****//
int hourupg;
int minupg;
int yearupg;
int monthupg;
int dayupg;
int menu =0;
int setAll =0;

uint8_t alarmHours = 0, alarmMinutes = 0;  // Holds the current alarm time

byte bell[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100
};

void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, bell);

  pinMode(P1,INPUT_PULLUP);
  pinMode(P2,INPUT_PULLUP);
  pinMode(P3,INPUT_PULLUP);
  pinMode(P4,INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); // Set buzzer as an output
  printAllOff();
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
 
void loop()
{ 
  if(digitalRead(P1)== LOW) 
  {
   menu=menu+1;
  }
  if((digitalRead(P2)== LOW)&&(digitalRead(P3)== LOW))                                                                                                                                                                     
  { 
    DisplaySetHourAll();
    DisplaySetMinuteAll();
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("ALARM");
    lcd.setCursor(5,1);
    if (alarmHours <= 9)
    {
      lcd.print("0");
    }
    lcd.print(alarmHours, DEC);
    lcd.print(":");
    if (alarmMinutes <= 9)
    {
      lcd.print("0");
    }
    lcd.print(alarmMinutes, DEC);
    delay(1000);
    lcd.clear();
  }
  if (menu==0)
    {
     DisplayDateTime(); 
     Alarm(); 
          }
  if (menu==1)
    {
    DisplaySetHour();
    }
  if (menu==2)
    {
    DisplaySetMinute();
    }
  if (menu==3)
    {
    DisplaySetYear();
    }
  if (menu==4)
    {
    DisplaySetMonth();
    }
  if (menu==5)
    {
    DisplaySetDay();
    }
  if (menu==6)
    {
    StoreAgg(); 
    delay(500);
    menu=0;
    }
    delay(100);
}

void DisplayDateTime ()
{
  DateTime now = RTC.now();

  lcd.setCursor(0, 0);
  if (now.hour()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  hourupg=now.hour();
  lcd.print(":");
  if (now.minute()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  minupg=now.minute();
  lcd.print(":");
  if (now.second()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);

  char DOW[][6]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  lcd.setCursor(0, 1);
  lcd.print(DOW[now.dayOfTheWeek()]);
  
  lcd.setCursor(6, 1);
  if (now.day()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  dayupg=now.day();
  lcd.print("/");
  if (now.month()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  monthupg=now.month();
  lcd.print("/");
  lcd.print(now.year(), DEC);
  yearupg=now.year();
}

void DisplaySetHour()
{
  lcd.clear();
  DateTime now = RTC.now();
  if(digitalRead(P2)==LOW)
  {
    if(hourupg==23)
    {
      hourupg=0;
    }
    else
    {
      hourupg=hourupg+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if(hourupg==0)
    {
      hourupg=23;
    }
    else
    {
      hourupg=hourupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Hour:");
  lcd.setCursor(0,1);
  lcd.print(hourupg,DEC);
  delay(200);
}

void DisplaySetMinute()
{
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if (minupg==59)
    {
      minupg=0;
    }
    else
    {
      minupg=minupg+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (minupg==0)
    {
      minupg=59;
    }
    else
    {
      minupg=minupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0,1);
  lcd.print(minupg,DEC);
  delay(200);
}
  
void DisplaySetYear()
{
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {    
    yearupg=yearupg+1;
  }
   if(digitalRead(P3)==LOW)
  {
    yearupg=yearupg-1;
  }
  lcd.setCursor(0,0);
  lcd.print("Set Year:");
  lcd.setCursor(0,1);
  lcd.print(yearupg,DEC);
  delay(200);
}

void DisplaySetMonth()
{
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if (monthupg==12)
    {
      monthupg=1;
    }
    else
    {
      monthupg=monthupg+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (monthupg==1)
    {
      monthupg=12;
    }
    else
    {
      monthupg=monthupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Month:");
  lcd.setCursor(0,1);
  lcd.print(monthupg,DEC);
  delay(200);
}

void DisplaySetDay()
{
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if (dayupg==31)
    {
      dayupg=1;
    }
    else
    {
      dayupg=dayupg+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (dayupg==1)
    {
      dayupg=31;
    }
    else
    {
      dayupg=dayupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Day:");
  lcd.setCursor(0,1);
  lcd.print(dayupg,DEC);
  delay(200);
}

void StoreAgg()
{
// Variable saving
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
  RTC.adjust(DateTime(yearupg,monthupg,dayupg,hourupg,minupg,0));
  delay(200);
  lcd.clear();
}
void DisplaySetHourAll()// Setting the alarm minutes
{
  while(digitalRead(P1)==HIGH){
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if(alarmHours==23)
    {
      alarmHours=0;
    }
    else
    {
      alarmHours=alarmHours+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if(alarmHours==0)
    {
      alarmHours=23;
    }
    else
    {
      alarmHours=alarmHours-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set HOUR Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmHours,DEC);
  delay(200);
 }
 delay(200);
}

void DisplaySetMinuteAll()// Setting the alarm minutes
 {
  while(digitalRead(P1)==HIGH){ 

  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if (alarmMinutes==59)
    {
      alarmMinutes=0;
    }
    else
    {
      alarmMinutes=alarmMinutes+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (alarmMinutes==0)
    {
      alarmMinutes=59;
    }
    else
    {
      alarmMinutes=alarmMinutes-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set MIN. Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmMinutes,DEC);
  delay(200);
 }
 delay(200);
}

void printAllOn(){
   lcd.setCursor(10,0);
  if (alarmHours <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmHours, DEC);
  
  lcd.print(":");
  if (alarmMinutes <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmMinutes, DEC); 
  lcd.write(0);
}

void printAllOff() {
  lcd.setCursor(10, 0);
  lcd.print("   Off");  
}

void Alarm(){
   if(digitalRead(P4)== LOW)
  {
   setAll=setAll+1;
  }
  
  if (setAll==0)
    {
     printAllOff();
     noTone (buzzer);
     }
  if (setAll==1)
    {
     printAllOn();    
  
     DateTime now = RTC.now();
     if (now.hour() == alarmHours && now.minute() == alarmMinutes )
        {
         lcd.noBacklight();
         DateTime now = RTC.now();
         tone(buzzer,880); //play the note "A5" (LA5)
         delay (300);
         tone(buzzer,698); //play the note "F6" (FA5)
         lcd.backlight();
        }
    else{
         noTone (buzzer);
        }
    } 
  if (setAll==2)
    {
     setAll=0;
    }
    delay(200);
}