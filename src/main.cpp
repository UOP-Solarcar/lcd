#include <Arduino.h>
#include <Nextion.h>

#define LEVEL_HIGH (30)
#define LEVEL_LOW (0)

#define CH0_OFFSET (40 - LEVEL_HIGH / 2)
#define CH1_OFFSET (CH0_OFFSET + 40 * 1)
#define CH2_OFFSET (CH0_OFFSET + 40 * 2)
#define CH3_OFFSET (CH0_OFFSET + 40 * 3)

NexWaveform s0 = NexWaveform(0, 1, "s0");

static uint8_t ch0_data = LEVEL_LOW;
static uint8_t ch1_data = LEVEL_LOW;
static uint8_t ch2_data = LEVEL_LOW;
static uint8_t ch3_data = LEVEL_LOW;

void setup() {
  nexInit();
  dbSerialPrintln("setup done");
}

void loop() {
  static uint32_t started = 0;
  if (millis() - started >= 2000) {
    started = millis();
    if (LEVEL_HIGH == ch0_data) {
      ch0_data = LEVEL_LOW;
    } else {
      ch0_data = LEVEL_HIGH;
    }
  }

  ch1_data = ch0_data + random(0, 2);
  ch2_data = ch0_data + random(0, 5);
  ch3_data = ch0_data + random(0, 8);

  s0.addValue(0, CH0_OFFSET + ch0_data);
  s0.addValue(1, CH1_OFFSET + ch1_data);
  s0.addValue(2, CH2_OFFSET + ch2_data);
  s0.addValue(3, CH3_OFFSET + ch3_data);
}
