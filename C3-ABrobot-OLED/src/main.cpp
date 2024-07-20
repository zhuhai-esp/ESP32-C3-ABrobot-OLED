#include <Arduino.h>
#include <U8g2lib.h>

#undef LED_BUILTIN
#define LED_BUILTIN 8
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 6, 5, U8X8_PIN_NONE);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  u8g2.setContrast(250);
  u8g2.begin();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_unifont_t_chinese3);
    u8g2.setCursor(30, 24);
    u8g2.print("24-02-11");
    u8g2.setCursor(30, 40);
    u8g2.print("23:55:45");
    u8g2.drawFrame(30, 12, 72, 40);
  } while (u8g2.nextPage());
}