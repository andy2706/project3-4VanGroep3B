#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const byte ROWS = 4; 
const byte COLS = 4; 

int incomingByte;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2, 14}; 

int yesorno = 'Y';

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

}
void rfid(){
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();

  content.toUpperCase();
  }

void keys(){
  char customKey = customKeypad.getKey();
  if(customKey){
    Serial.println(customKey);
  }
}
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    yesorno = incomingByte;
    }
    if(yesorno == 'Y'){
      rfid();
    }
    if(yesorno == 'N'){
      keys();
    }
  }
  
