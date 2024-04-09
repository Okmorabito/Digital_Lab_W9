#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;                   //xy=295,339
AudioAnalyzePeak peak1;               //xy=452,300
AudioAnalyzeNoteFrequency notefreq1;  //xy=457,402
AudioOutputI2S i2s2;                  //xy=535,343
AudioConnection patchCord1(i2s1, 0, peak1, 0);
AudioConnection patchCord2(i2s1, 0, i2s2, 1);
AudioConnection patchCord3(i2s1, 0, i2s2, 0);
AudioConnection patchCord4(i2s1, 0, notefreq1, 0);
AudioControlSGTL5000 sgtl5000_1;  //xy=391,209
// GUItool: end automatically generated code


int numPixels = 8;
int pixelPin = 33;
int mappedNote = 0;
Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(numPixels, pixelPin, NEO_GRB);

void setup() {
  neopixel.begin();
  neopixel.clear();
  neopixel.show();
  AudioMemory(500);
  Serial.begin(9600);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  notefreq1.begin(.15);
}

void loop() {
  checkFreq();
  if (peak1.available()) {
    int peak = peak1.read() * 8;
    for (int i = 0; i < peak; i++) {
      neopixel.setPixelColor(i, mappedNote, 80, 0);
      neopixel.show();
    }
    neopixel.clear();
  }
}

void checkFreq() {
  if (notefreq1.available()) {
    float note = notefreq1.read();
    Serial.println(note);
    mappedNote = map(note, 440, 800, 0, 255);
  }
}
