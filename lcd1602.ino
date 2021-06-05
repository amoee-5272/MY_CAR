#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
LiquidCrystal_PCF8574 lcd(0x27); 
// set the LCD address to 0x27
#include <SoftwareSerial.h>
SoftwareSerial BT (8, A0);
String bufferr="";
char msg;

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  lcd.begin(16, 2); // initialize the lcd  
} // setup()
void loop(){
  while(BT.available()){
    msg=char(BT.read());
    if(msg=='#'){
      bufferr="";
    }
    else{
      bufferr=bufferr+msg;
    }
    Serial.println(bufferr);
    
  }    
  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(bufferr);
  lcd.setCursor(0, 1);
  delay(200);
  //電腦傳給藍牙
  if(Serial.available())
    BT.write(Serial.read()); 
    
} 
