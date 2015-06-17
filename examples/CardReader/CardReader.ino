/*
Example for TI MSP430 LaunchPads and Energia that reads a card number 
using a RC522 MIFARE module, takes action depending on the card number,
and prints it to the serial monitor.
https://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm

Based on code and ideas from Eelco Rouw (www.43oh.com), Grant Gibson
(www.grantgibson.co.uk), Dr.Leong (www.b2cqshop.com), and
Craig Thompson/Aaron Norris at Addicore.

Minor modifications to above by Frank Milburn 10 June 2015
Released into the public domain

Tested on MSP-EXP430G2 LaunchPad
          MSP-EXP430F5529 LaunchPad
          MSP-EXP430FR5969 LaunchPad
 
Pin Connections
===================================      
RFID Module       MSP430 LaunchPads        
--------------    -----------------
Pin 1  (SDA)      Pin 8  (CS)
Pin 2  (SCK)      Pin 7  (SCK)
Pin 3  (MOSI)     Pin 15 (MOSI)
Pin 4  (MISO)     Pin 14 (MISO)
Pin 5  (IRQ)      Not connected
Pin 6  (GND)      GND
Pin 7  (RST)      Pin 10
Pin 8  (3V3)      3V3

Addicore has a very good introduction to this module, written for Arduino.
Try the site below for additional detail on the module and examples
which include writing to a card, dumping detailed information, changing
the card user ID, etc.  It will run on LaunchPads or Arduinos with the
correct pin connections:  https://github.com/miguelbalboa/rfid
*/

#include "Mfrc522.h"
#include <SPI.h>

int CS = 8;                                 // chip select pin
int NRSTDP = 5;
Mfrc522 Mfrc522(CS,NRSTDP);
unsigned char serNum[5];

void setup() 
{             
  Serial.begin(9600);                        
  Serial.println("Starting RFID-RC522 MIFARE module demonstration...\n");

  SPI.begin();
  digitalWrite(CS, LOW);                    // Initialize the card reader
  pinMode(RED_LED, OUTPUT);                 // Blink LED if card detected
  Mfrc522.Init();  
}

void loop()
{
  unsigned char status;
  unsigned char str[MAX_LEN];
  	
  status = Mfrc522.Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    Serial.print("Card detected: ");
    Serial.print(str[0],BIN);
    Serial.print(" , ");
    Serial.print(str[1],BIN);
    Serial.println("");
  }

  status = Mfrc522.Anticoll(str);
  memcpy(serNum, str, 5);
  if (status == MI_OK)
  {
    digitalWrite(RED_LED, HIGH);              // Card or tag detected!
    Serial.print("The card's number is: ");
    Serial.print(serNum[0]);
    Serial.print(" , ");
    Serial.print(serNum[1]);
    Serial.print(" , ");
    Serial.print(serNum[2]);
    Serial.print(" , ");
    Serial.print(serNum[3]);
    Serial.print(" , ");
    Serial.print(serNum[4]);
    Serial.println("");
 
 // Additional cards can be recognized by running the program and noting the 5 card specific numbers
 // and then adding an "else if" statement below.
    if(serNum[0] == 148 && serNum[1] == 176 && serNum[2] == 135 && serNum[3] == 240 && serNum[4] == 83) 
    {
      Serial.println("Hello 007\n");
    }
    else if (serNum[0] == 148 && serNum[1] == 217 && serNum[2] == 159 && serNum[3] == 240 && serNum[4] == 34)
    {
      Serial.println("Hello Moneypenny\n");
    }
    else
    {
      Serial.println("SPECTRE attempting entry!\n");    
    }  
    delay(1000);
    digitalWrite(RED_LED, LOW);
  }
  Mfrc522.Halt();	                        
}


