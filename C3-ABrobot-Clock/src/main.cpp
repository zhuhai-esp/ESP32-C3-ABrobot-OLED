#include <Arduino.h>
#include <ArduinoOTA.h>
#include <U8g2lib.h>
#include <WiFi.h>

#undef LED_BUILTIN
#define LED_BUILTIN 8

static const char *WEEK_DAYS[] = {"日", "一", "二", "三", "四", "五", "六"};
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 6, 5, U8X8_PIN_NONE);
char buf[256];
u32_t count = 0;
String ip;

void inline startWifiConfig() {
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin();
  for (int i = 0; WiFi.status() != WL_CONNECTED && i < 100; i++) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.beginSmartConfig();
    u8g2.setCursor(33, 29);
    u8g2.print("还没联网");
    u8g2.setCursor(33, 46);
    u8g2.print("ESPTouch");
    u8g2.nextPage();
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    WiFi.stopSmartConfig();
    WiFi.mode(WIFI_MODE_STA);
  }
}

void inline startConfigTime() {
  const int timeZone = 8 * 3600;
  configTime(timeZone, 0, "ntp6.aliyun.com", "cn.ntp.org.cn", "ntp.ntsc.ac.cn");
  while (time(nullptr) < 8 * 3600 * 2) {
    delay(500);
  }
  delay(500);
}

void inline setupOTAConfig() {
  ArduinoOTA.onStart([] {});
  ArduinoOTA.onProgress([](u32_t pro, u32_t total) {});
  ArduinoOTA.onEnd([] {});
  ArduinoOTA.begin();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese3);
  startWifiConfig();
  startConfigTime();
  ip = WiFi.localIP().toString();
  setupOTAConfig();
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
}

void inline showCurrentTime() {
  struct tm info;
  getLocalTime(&info);
  u8g2.firstPage();
  strftime(buf, 32, "%T", &info);
  u8g2.setCursor(33, 29);
  u8g2.print(buf);
  sprintf(buf, "%02d月%02d日", info.tm_mon + 1, info.tm_mday);
  u8g2.setCursor(33, 46);
  u8g2.print(buf);
  u8g2.nextPage();
}

void loop() {
  delay(100);
  showCurrentTime();
  ArduinoOTA.handle();
  if (count++ >= 100) {
    count = 0;
  }
}