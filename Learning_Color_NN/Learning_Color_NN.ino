#include "Perceptron.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

uint16_t clear, red, green, blue ;
perceptron colorPerceptron(4);

void setup() {

  tcs.begin();

  randomSeed(A0);
  colorPerceptron.randomize();

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  pinMode(11, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  tcs.setInterrupt(false);
  delay(60);
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);
  
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  colorPerceptron.inputs[0] = r;
  colorPerceptron.inputs[1] = g;
  colorPerceptron.inputs[2] = b;

  float guess = colorPerceptron.feedForward();

  if (digitalRead(11) == 0) {
    digitalWrite(12, LOW);
    colorPerceptron.train(1, guess);
    delay(1000);
    digitalWrite(12, HIGH);
  }

  if (digitalRead(8) == 0) {
    digitalWrite(12, LOW);
    colorPerceptron.train(-1, guess);
    delay(1000);
    digitalWrite(12, HIGH);
  }

  if (guess == 1) {
    Serial.println("Match");
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  
  else {
    Serial.println("No Match");
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  
}
