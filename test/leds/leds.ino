#include <Adafruit_NeoPixel.h>

#define PIN_GROUP_0 6 // Group of LED rings for top camera
#define NUM_LEDS 12   // Number of LEDs on a single ring

Adafruit_NeoPixel topGroup = Adafruit_NeoPixel(NUM_LEDS, PIN_GROUP_0, NEO_GRB + NEO_KHZ800);

void setup() {
    topGroup.begin();

}

void loop() {
    topGroup.fill(topGroup.Color(25, 25, 25));
    topGroup.show();
}
