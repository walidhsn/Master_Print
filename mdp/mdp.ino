#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9

String rfid;
String data;
char data2;
String content;

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}
String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)
  return String(data);
}

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create instance of our reader
String readRFID()
{
  String content;
 for( byte i = 0; i < mfrc522.uid.size; i++ ){
 content.concat(String(mfrc522.uid.uidByte[i], HEX));
 if( i < mfrc522.uid.size-1 ) content+="-";
 }
 return content;
}

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
 Serial.begin(9600);
 SPI.begin();
 mfrc522.PCD_Init();
 //Serial.println("Arduino RFID lock");
 lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Inserer carte");
  
}
void loop(){
 //Look for new cards
 if ( ! mfrc522.PICC_IsNewCardPresent() ){
 return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial() ) {
 return;
 }
// If a card is detected, execute the following:
 //Serial.println("Time to open");
// Print the card's ID
 content= "";
 String code=readRFID();
 code.toUpperCase();
 while(Serial.available()==0){}
  rfid=Serial.readString();
  data2=rfid.charAt(11);
  data=rfid.substring(12);
  rfid=rfid.substring(0,11);
  
  if(code == rfid){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Carte correcte");
    if(data2=='a')
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Affichage en cours ...");
      String retrievedString = readStringFromEEPROM(0);
      Serial.print(retrievedString);
    }
    if(data2=='b')
    {
      writeStringToEEPROM(0,data); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MDP sauvegarde");
    }
 }
 else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Carte incorrecte");
 } 
}
