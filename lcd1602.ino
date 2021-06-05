#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
LiquidCrystal_PCF8574 lcd(0x27); 
// set the LCD address to 0x27
#include <SoftwareSerial.h>
SoftwareSerial BT (8, A0);
String bufferr="";

char msg;
int i;
void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  lcd.begin(16, 2); // initialize the lcd  
  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();
} // setup()
void loop(){
  while(BT.available()){
    lcd.clear();
    msg=char(BT.read());
    if(msg=='#'){
      bufferr="";
    }
    else{
      bufferr=bufferr+msg;
    }
    //Serial.println(bufferr);
    
  }    
 
  //lcd.print(bufferr.length());
  if(bufferr.length()<=16){
    lcd.print(bufferr);
    lcd.setCursor(0, 0);
  }
  else if(bufferr.length()>=16 && bufferr.length()<=32){
    lcd.setCursor(0, 0);
    for(i=0;i<bufferr.length();i++){
      if(i<16){
       lcd.print(bufferr[i]);
       lcd.setCursor(i, 0); 
      }
      else{
        lcd.print(bufferr[i]);
        lcd.setCursor(i-16, 1); 
      }
    }
  }
  else{
    lcd.setCursor(0, 0);
    bufferr+=" ";
    lcd.print(bufferr);
    for(i=0;i<50;i++){
      lcd.scrollDisplayLeft();
      delay(1000);
    }
  }
  delay(200);
  //電腦傳給藍牙
  if(Serial.available())
    BT.write(Serial.read()); 
    
} 

