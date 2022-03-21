//for wemos d1 mini wifi module
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "clsUnicode.h"
#include "clsSIM800L.h"


//Serial pins
#define TX_PIN 5  //D1  GPIO 5
#define RX_PIN 4  //D5 GPIO 14, D2  GPIO 4


#define RESET_PIN 0  //D3  GPIO 0

//LED
#define LED_BLUE 2  //D4  GPIO 2

#define LOOP_DELAY 1
#define GSM_SERIAL_SPEED 9600
#define UI_SERIAL_SPEED 4800

#define RELAY1_PIN    14  //D5
#define RELAY2_PIN    12  //D6
#define REMOTE_PIN    13  //D7

SIM800L *GSM;


void Blink() {
  digitalWrite(LED_BLUE, LOW);
  delay(100);
  digitalWrite(LED_BLUE, HIGH);
}

void hw_wdt_disable() {
  *((volatile uint32_t *)0x60000900) &= ~(1);  // Hardware WDT OFF
}

void hw_wdt_enable() {
  *((volatile uint32_t *)0x60000900) |= 1;  // Hardware WDT ON
}

void setup() {

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  /*
    ESP.wdtDisable();
    ESP.wdtEnable(60*1000);
  */
  //hw_wdt_disable();
  delay(10);
  //ESP.eraseConfig();

  Serial.begin(UI_SERIAL_SPEED);  // Serial for debug...  //
  Serial.println("start()");

  pinMode(LED_BLUE, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(RX_PIN, OUTPUT);


  digitalWrite(LED_BLUE, LOW);
  delay(3000);
  digitalWrite(LED_BLUE, HIGH);

  Serial.println("setup()");
  WiFi.mode(WIFI_OFF);

  uint64_t timeOld = millis();
  GSM = new SIM800L(GSM_SERIAL_SPEED, RX_PIN, TX_PIN);


  /*
  clsUnicode Unicode;
  //String uTxt = Unicode.ToUCS2("سلام");
  //Serial.println(uTxt);

  String msg = "11";
  String Txt = Unicode.FromUCS2(msg.c_str(), msg.length());
  //printf("Unicode: %s", Txt.c_str());
  Serial.println(Txt);
  //return;
*/

  /*
    //GSMSerial->onReceive(test);
    while (!GSMSerial)) {
    ; // wait for module for connect.
    }
  */

  
  

  /**/

  //GSMSerial->print("AT+CMGDA=?\r"); AT+CMGR=1
  //GSM->SendSMS("09192315738", "");

  // delay(1000);
  // Init module...
  
  
  Serial.print("GSM starrt after: ");
  Serial.println(millis() - timeOld);

  Serial.println("start looooooooooooooooooooooooooooooooooooop()");
}

void loop() {

  // /*
  GSM->CheckSerial();

  //delay(LOOP_DELAY);
  if (Serial.available()) {
    String received = Serial.readString();
    delay(1);
    //GSM->ReadSMSByIndex(received.toInt());
    //GSM->SendUSSD(received.c_str());
    GSM->WriteToSerial(received.c_str());


    Blink();
  }
  delay(1);
}
