#include <Arduino.h>
#include <U8g2lib.h>

#undef LED_BUILTIN
#define LED_BUILTIN 8
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 6, 5, U8X8_PIN_NONE);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese3);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);

  u8g2.firstPage();
  do {
    u8g2.setCursor(33, 29);
    u8g2.print("24-02-种");
    u8g2.setCursor(33, 46);
    u8g2.print("23:55:器");
    u8g2.drawFrame(30, 12, 72, 40);
  } while (u8g2.nextPage());
}