#include "FastLED.h"
#include <CapacitiveSensor.h>
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

#define DATA_PIN    5
#define CLOCK_PIN   6
#define LED_TYPE    DOTSTAR
#define COLOR_ORDER GRB
#define NUM_LEDS    15
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

int hit;
int capSensePin = 4;

void setup() {
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  LEDS.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {

  long start = millis();
  char inByte = 0;

  if (Serial.available() > 0) {
    inByte = Serial.read();
    Serial.println(cs_4_2.capacitiveSensor(30));
    delay(10);

    tropicThunder();
    bounceFadeRain();
    FastLED.show();
    FastLED.delay(100 / FRAMES_PER_SECOND);
  }
}

void bounceFadeRain()
{
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin8(10, 0, NUM_LEDS);
  leds[pos] += CRGB::Magenta;
  if (pos == 1 || pos == 15) {
    hit++;
  }
  FastLED.show();

  FastLED.delay(100 / FRAMES_PER_SECOND);
}

void tropicThunder() {
  // adapted from Michael's Unicorn Thunder
  //  https://github.com/mixania/Unicorn
  //  ☆彡 ☆。、:*:。

  unsigned int randSpark = random(0, (NUM_LEDS) - 1);
  unsigned int thunderDelay = random(3, 50);

  leds[randSpark] = CRGB::Green;
  FastLED.show();
  delay(thunderDelay);
  leds[randSpark] = CRGB::Orange;
  FastLED.show();
  delay(thunderDelay);
  leds[randSpark] = CRGB::Black;
  delay(thunderDelay);

}
