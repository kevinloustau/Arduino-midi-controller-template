#include <MIDIUSB.h>


int analogInputCount = 10;
int analogInputArray[10];
int analogInputArrayPrevious[10];


static const uint8_t analog_pins[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10};
//https://arduino.stackexchange.com/questions/1615/how-to-loop-over-analog-pins

void setup() {
  Serial.begin(115200);
}

void loop() {
    for (int i = 0; i < analogInputCount; i++) {
      analogInputArray[i] = analogRead(analog_pins[i]);
      analogInputArray[i] = map(analogInputArray[i], 0, 1023, 0, 126);
      
      if (analogInputArray[i] != analogInputArrayPrevious[i]) {
        controlChange(0, i, analogInputArray[i]);
      }
      analogInputArrayPrevious[i] = analogInputArray[i];
    }

}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
