#include "Leanbot.h"
 
 
String line1;
String line2;
 
//============   OLED display   ================================================
 
#include <U8g2lib.h>         // U8g2 Library Reference: https://github.com/olikraus/u8g2/wiki
#include <Wire.h>
 
 
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);   // SH1106 for 1.3" OLED module
 
 
void OLED_Display() {
  u8g2.firstPage();
  do {                                              // OLED buffer drawing loop
 
    u8g2.setCursor(35, 16);			// Total Display is (XX,YY)= 128, 64
    u8g2.print(line1);
 
    u8g2.setCursor(35, 32);
    u8g2.print(line2);
    
  } while ( u8g2.nextPage() );
}
 
//============   OLED display   ================================================
 
 
void setup() {
  Leanbot.begin();
 
  // begin OLED
  u8g2.setBusClock( 400000 );                 // I2C speed 400kHz
  u8g2.setFont( u8g2_font_luBS08_tr );        // OLED: choose a suitable font
  u8g2.begin();
}
 
 
void loop() {
 
  line1 = "hello world";
  OLED_Display();

  delay(2500);

  line2 = "I'm An nha";
  OLED_Display();
}