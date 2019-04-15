#include <G_PatternSequencer.h>
#include <G_FadePattern.h>
#include <G_MovingPixelGroup.h>

int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
G_PatternSequencer runner(&strip);


void setup() {
  strip.begin();  
  delay(2000);
  Serial.begin(115200);

  G_MovingPixelGroup* moveGrp = new G_MovingPixelGroup(0, 1, new int[2]{0,20}, 2, new int[2]{1,21}, 2);
  G_FadePattern* pattern = new G_FadePattern(moveGrp, 0,0,0, 0,0,255, 300, 0, 0, false);
  runner.addPattern(pattern);
}

void loop() {
  runner.run();
}
