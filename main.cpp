#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int button = 13;
int buttonOld=0;
unsigned long previousMil = 0;
unsigned long currentMil =0;
const long period = 3000;

bool tr=false;
bool trinfo=false;
bool eng=false;
bool enginfo=false;

String s;
int days=0;
int day=8;
int month=4;
int year=2020;
int hour=23;
int min=59;
int sec=0;

void setup()
{
  lcd.begin(16,2);
  pinMode(button,INPUT);
  Serial.begin(9600);
}
void loop()
{ 
  if(sec==60){
    min+=1;
    sec=0;
    if(min==60){
      hour+=1;
      min=0;
      if(hour==24){
        day+=1;
        days+=1;
        hour=0;
        if(day==31){
          month+=1;
          day=1;
          if(month==13){
            year+=1;
            month=1;
          }  
        }
      }
    }
  }
  
  if(eng==false && tr==false){ //sadece ilk durum
     eng=true;
  }
  
  currentMil = millis();
  //3 sn lik period gerçekleşti mi kontrolü
  if (currentMil - previousMil >= period) {
    previousMil = currentMil;
    lcd.clear();
    if(tr==true && trinfo==false){trinfo=true;}
    else if(tr==true && trinfo==true){trinfo=false;}
    else if(eng==true && enginfo==false){enginfo=true;}
    else if(eng==true && enginfo==true){enginfo=false;}
  }
  
  if(push(button)&& buttonOld==0){
    previousMil = currentMil;
    buttonOld=1;
    lcd.clear();
    if(tr==true){
      eng=true;
      enginfo=false;
      tr=false;
    }
    else if(eng==true){
      tr=true;
      trinfo=false;
      eng=false;
    }
  }
  else if(push(button)==false && buttonOld==1){
    buttonOld=0;
  }
  
  if(tr==true && trinfo==true){
      showInfoTUR();
  }
  else if(tr==true && trinfo==false){
      s=DOW("TUR",days);
      showDefaultTUR(s);
  }
  else if(eng==true && enginfo==true){
      showInfoENG();
  }
  else if(eng==true && enginfo==false){
      s=DOW("ENG",days);
      showDefaultENG(s);
  }
  delay(1000); 
  sec+=1;
}
bool push(int b){
  int x= digitalRead(b);
  if(x==1){return (true);}  
}
void showDefaultENG(String dow){
  
    int hourtemp=0;
    if(hour>12) {hourtemp=(hour-12);}
    else if(hour==0){hourtemp=12;} 
  
    if(hourtemp<10){
      lcd.setCursor(0,0); lcd.print(0);
      lcd.setCursor(1,0); lcd.print(hourtemp);
    }
    else {
      lcd.setCursor(0,0); lcd.print(hourtemp);
    }
    lcd.setCursor(2,0); lcd.print(":");
  
    if(min<10){
      lcd.setCursor(3,0); lcd.print(0);
      lcd.setCursor(4,0); lcd.print(min);
    }
    else {
      lcd.setCursor(3,0); lcd.print(min);
    }
    lcd.setCursor(5,0); lcd.print(":");
  
    if(sec<10){
      lcd.setCursor(6,0); lcd.print(0);
      lcd.setCursor(7,0); lcd.print(sec);
    }
    else {
      lcd.setCursor(6,0); lcd.print(sec);
    }
   
    if(hour<12){
   	  lcd.setCursor(9,0); lcd.print("AM");

  	}
    else{
      lcd.setCursor(9,0); lcd.print("PM");
  	}
    lcd.setCursor(11,0); lcd.print(" ");
    lcd.setCursor(13,0); lcd.print("ENG");
    
    if(day<10){
      lcd.setCursor(0,1); lcd.print(0);
      lcd.setCursor(1,1); lcd.print(day); 
    }
    else {
      lcd.setCursor(0,1); lcd.print(day); 
    }
    lcd.setCursor(2,1); lcd.print(":");
  
    if(month<10){
      lcd.setCursor(3,1); lcd.print(0);
      lcd.setCursor(4,1); lcd.print(month);
    }
    else {
      lcd.setCursor(3,1); lcd.print(month);
    }
    lcd.setCursor(5,1); lcd.print(":");
    lcd.setCursor(6,1); lcd.print(year);
    lcd.setCursor(13,1); lcd.print(dow);
}
void showDefaultTUR(String dow){
   
    if(hour<10){
      lcd.setCursor(0,0); lcd.print(0);
      lcd.setCursor(1,0); lcd.print(hour);
    }
    else {
      lcd.setCursor(0,0); lcd.print(hour);
    }
    lcd.setCursor(2,0); lcd.print(":");
  
    if(min<10){
      lcd.setCursor(3,0); lcd.print(0);
      lcd.setCursor(4,0); lcd.print(min);
    }
    else {
      lcd.setCursor(3,0); lcd.print(min);
    }
    lcd.setCursor(5,0); lcd.print(":");
  
    if(sec<10){
      lcd.setCursor(6,0); lcd.print(0);
      lcd.setCursor(7,0); lcd.print(sec);
    }
    else {
      lcd.setCursor(6,0); lcd.print(sec);
    }
    
    lcd.setCursor(9,0); lcd.print("   ");
    lcd.setCursor(13,0); lcd.print("TUR");
    
    if(day<10){
      lcd.setCursor(0,1); lcd.print(0);
      lcd.setCursor(1,1); lcd.print(day); 
    }
    else {
      lcd.setCursor(0,1); lcd.print(day); 
    }
    lcd.setCursor(2,1); lcd.print(":");
  
    if(month<10){
      lcd.setCursor(3,1); lcd.print(0);
      lcd.setCursor(4,1); lcd.print(month);
    }
    else {
      lcd.setCursor(3,1); lcd.print(month);
    }
    lcd.setCursor(5,1); lcd.print(":");
    lcd.setCursor(6,1); lcd.print(year);
    lcd.setCursor(13,1); lcd.print(dow);
}
void showInfoENG(){
  
    lcd.setCursor(0,0); lcd.print("HH:MM:SS");	
    lcd.setCursor(9,0); lcd.print("12H");
  	lcd.setCursor(13,0); lcd.print("LNG");
  
    lcd.setCursor(0,1); lcd.print("DD.MM.YYYY");
    lcd.setCursor(13,1); lcd.print("DOW");
}
void showInfoTUR(){
   
    lcd.setCursor(0,0); lcd.print("HH:MM:SS");	
    lcd.setCursor(9,0); lcd.print("24H");
  	lcd.setCursor(13,0); lcd.print("LNG");
  
    lcd.setCursor(0,1); lcd.print("DD.MM.YYYY");
    lcd.setCursor(13,1); lcd.print("DOW");
}
String DOW(String lng,int days){
  
  String thisDay;
  if(lng=="ENG"){
    if(days%7==0){thisDay="WED";}
    else if(days%7==1){thisDay="THU";}  
    else if(days%7==2){thisDay="FRI";}
    else if(days%7==3){thisDay="SAT";} 
    else if(days%7==4){thisDay="SUN";}  
    else if(days%7==5){thisDay="MON";}
    else if(days%7==6){thisDay="TUE";}
  }
  if(lng=="TUR"){
    if(days%7==0){thisDay="CAR";}
    else if(days%7==1){thisDay="PER";}  
    else if(days%7==2){thisDay="CUM";}
    else if(days%7==3){thisDay="CMT";} 
    else if(days%7==4){thisDay="PZR";}  
    else if(days%7==5){thisDay="PZT";}
    else if(days%7==6){thisDay="SAL";}
  }
  return thisDay;
}