#include <Arduino_APDS9960.h>
#include <Leanbot.h>
String line1;
String line2;
String line3;
String line4; 

#include <U8g2lib.h>         
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);   // SH1106 for 1.3" OLED module
 
void OLED_Display() {
  u8g2.firstPage();
  do {                                              // OLED buffer drawing loop
 
    u8g2.setCursor(0,15);
    u8g2.print(line1);

    u8g2.setCursor(0,30);
    u8g2.print(line2);

    u8g2.setCursor(0,45);
    u8g2.print(line3);

    u8g2.setCursor(0,60);
    u8g2.print(line4);
    
  } while ( u8g2.nextPage() );
}
 
//============   OLED display   ================================================

void setup() {
  Leanbot.begin();
  APDS.begin();                                     // STEP 2: Initialize the Leanbot and the color sensor
  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }

    // begin OLED
  u8g2.setBusClock(400000);
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.begin();
}
void loop() {
  if (APDS.proximityAvailable()) {
    int proximity = APDS.readProximity(); //0(close) 255(far) -1(error)
    Serial.print("proximity = "); Serial.println(proximity); 

   LbRGB.clear();
   LbRGB.setBrightness(255-proximity);
   LbRGB.fillColor(0xffffff, BITMAP(ledO, ledA, ledB, ledC, ledD, ledE, ledF));
   LbRGB.show();
  }
  
 
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b;
  APDS.readColor(r, g, b); 

   // Hiển thị giá trị RGB
  line1 = "R: " + String(r);
  line2 = "G: " + String(g);
  line3 = "B: " + String(b);
  if(r > g && r > b){
    line4 = "Red";
  } else if(g > r && g > b){
    line4 = "Green"; 
  } else if(b > g && b > r){
    line4 = "Blue";
  }else{
    line4 = "Unknown";
  }
  OLED_Display();

  
  delay(1000);
}