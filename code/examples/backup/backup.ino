//This script creates a backup of a folder

#include "Keyboard.h"

const int switch1 = 4;
const int switch2 = 8;
const int redLED = 5;
const int greenLED = 6;

void fastKey(int key){
  Keyboard.press(key);
  delay(12);
  Keyboard.release(key);
  delay(3);
}

void typeKey(int key){
  Keyboard.press(key);
  delay(30);
  Keyboard.release(key);
  delay(15);
}

void doubleKey(int keyA, int keyB){
  Keyboard.press(keyA);
  Keyboard.press(keyB);
  delay(5);
  Keyboard.release(keyB);
  Keyboard.release(keyA);
  delay(10);
}

void typeStr(String str){
  for (int i = 0; i < str.length(); i++){
    fastKey(str[i]);
  }
}

void setup(){
  //Set pin modes
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);

  if (digitalRead(switch1)) {
    //Flash both LEDs simultaniously
    while (true) {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, HIGH);
      delay(1000);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      delay(1000);
    }
  } else {
    //Set up keyboard
    digitalWrite(redLED, HIGH);
    delay(100);
    Keyboard.begin();
    delay(1750); //Delay to wait for the device to be recognised by the host
    digitalWrite(redLED, LOW);
  
  
    //Run payload
    //Open powershell
    doubleKey(KEY_LEFT_GUI, 'x');
    typeKey('i');
    delay(500);

    //Run backup command
    typeStr("cp -r ");
    typeStr("C:/folder"); //Folder to back up
    typeStr("C:/backup/folder"); //Backup destination
    typeKey(KEY_RETURN);
  
  
    //Let the user know the script is done
    digitalWrite(greenLED, HIGH);
  }
}

void loop(){}
