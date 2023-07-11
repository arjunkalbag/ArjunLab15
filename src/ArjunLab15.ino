#include "oled-wing-adafruit.h"
// #include "WatchDog_WCL.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#define WD D4

volatile int countdown = 5;

void setup()
{
  Serial.begin(9600);
  display.setup();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (System.resetReason() == RESET_REASON_WATCHDOG)
  {
    resetDisplay();
    display.println("Watchdog Reset!");
    Serial.println("Watchdog Reset!");
    display.display();
  }
  else
  {
    resetDisplay();
    display.println("Other Reset!");
    Serial.println("Other Reset!");
    display.display();
  }

  pinMode(WD, INPUT_PULLUP);

  delay(1000);

  Watchdog.init(WatchdogConfiguration().timeout(5000));
  Watchdog.start();
  Watchdog.refresh();
}
void loop()
{
  display.loop();
  if (digitalRead(WD) == LOW)
  {
    delay(1000);
    resetDisplay();
    display.display();
    countdown--;
    resetDisplay();
    display.println(countdown);
    display.display();
    Serial.println(countdown);
  }
  else
  {
    Watchdog.refresh();
  }
}

void resetDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
}