/*
 * SHT45-QT basic example — reads temperature & humidity once per second.
 *
 * Wiring: plug the board into any Qwiic/STEMMA QT port, or wire the header:
 *   GND->GND, 3V3->3.3V, SDA->SDA, SCL->SCL
 *
 * Library: Adafruit SHT4x (install from the Library Manager).
 * Works on any Arduino-compatible board with I2C. Address is fixed at 0x44.
 *
 * Serial Plotter friendly: prints "temp_C:xx.xx,rh_pct:yy.yy".
 */
#include <Adafruit_SHT4x.h>

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (!sht4.begin()) {
    Serial.println("SHT4x not found on 0x44 - check wiring/pull-ups (JP1).");
    while (true) delay(1000);
  }

  // HIGH_PRECISION: ~8 ms per reading, best repeatability.
  // Heater off: heater is only for de-creep in condensing environments,
  // and it biases the temperature reading while active.
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);
}

void loop() {
  sensors_event_t rh, temp;
  if (!sht4.getEvent(&rh, &temp)) {
    Serial.println("read failed");
  } else {
    Serial.print("temp_C:");
    Serial.print(temp.temperature, 2);
    Serial.print(",rh_pct:");
    Serial.println(rh.relative_humidity, 2);
  }
  delay(1000);
}
