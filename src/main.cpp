#include <Arduino.h>
#include <LedControl.h>
#include <TowerStack.h>

#include <Wire.h>
#include <pt.h>

#define LCLOADPIN 10 // LC LOAD pin
#define LCCLKPIN 11 // LC CLK pin
#define LCDINPIN 12 // LC DataIn pin

#define BUTTON_PIN 13

LedControl lc = LedControl(LCDINPIN, LCCLKPIN, LCLOADPIN, 4);

TowerStack tower(lc);

int previous = HIGH;
int state = LOW;

void check_for_button_press() { //ToDo: digital read faster alternative?
    Serial.println("check_for_button_press()");

    int reading = digitalRead(BUTTON_PIN);

    if (reading == HIGH && previous == LOW) {
        Serial.println("button pressed");
        tower.button_pressed();
    }
    previous = reading;
}


void setup() {
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT);

    for (int address = 0; address < lc.getDeviceCount(); address++) {
        lc.shutdown(address, false);
        lc.setIntensity(address, 0);
        lc.clearDisplay(address);
    }

    tower.newGame();

    tower.test();
}


void loop() {
    check_for_button_press();
    tower.timeBrickAnimation();
}