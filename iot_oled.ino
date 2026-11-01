#include <Leanbot.h>
#include <LeanbotIoT.h>

//Sử dụng macro F() để giảm mức sử dụng SRAM của Arduino.
#define WIFI_SSID     F( "xxxxxxxxx" )
#define WIFI_PASSWORD F( "yyyyyyyyy" )

#define IOT_ASSET_ID  F( "abcdefghiklmnopeqrst" )
#define IOT_REALM     F( "master" )


auto IoT_Text_OLED = LbIoT.Asset.attribute(F( "IOT_TO_OLED" ));


#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

void setup(){
  Leanbot.begin();

  //Bắt đầu OLED
  u8g2.setBusClock( 1000000 );                    //tốc độ I2C tối đa
  u8g2.begin();
  u8g2.setFont( u8g2_font_luBS08_tr );            //OLED: Chọn một phông chữ phù hợp
}

void OLED_Display(String text) {
  for ( u8g2.firstPage() ; u8g2.nextPage() ;){    //vòng lặp vẽ bộ đệm OLED
    u8g2.setCursor(35, 16);
    u8g2.print(text);

    u8g2.setCursor(35, 24);
    u8g2.print("line 2");

  }
}

void loop(){
  if (LbIoT.Wifi.status() != WL_CONNECTED){
    if (LbIoT.Wifi.begin(WIFI_SSID, WIFI_PASSWORD) < 0){
      return;
    }
  }

  if (LbIoT.Asset.status() != ESTABLISHED){
    if (LbIoT.Asset.begin( IOT_ASSET_ID, IOT_REALM) < 0){
      return;
    }
    auto iotNotes = LbIoT.Asset.attribute(F( "notes" ));
    Serial.print( "Asset: " );
    Serial.println(iotNotes.read());              //print asset info
  }

  Serial.print("\n\n\n""######   Read the text from  IoT Dashboard to OLED display");
  String text = IoT_Text_OLED.read();
  checkResponseStatus();
  Serial.print( IoT_Text_OLED.name());
  Serial.print( " = " );
  Serial.println(text);

  OLED_Display(text);

  delay(2500);
}

void checkResponseStatus(){
  int responseStatus = LbIoT.Asset.responseStatus();
  LbIoT.decodeStatus( responseStatus );
}