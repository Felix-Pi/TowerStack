//
// Created by Felix Pieschka on 23.11.20.
//
#include "TowerStack.h"

#include <Arduino.h>
#include <LedControl.h>

TowerStack::TowerStack(LedControl lc) : lc(lc) {
    int devices = lc.getDeviceCount();

    this->max_height = 8 * devices;
}


void TowerStack::setLed(int row, int column, bool state) {

    int device;
    if (row < 0 || row >= this->max_height) return;

    if (row >= 0 && row < 8) {
        device = 3;
    }
    if (row >= 8 && row < 16) {
        device = 2;
        row -= 8;
    }
    if (row >= 16 && row < 24) {
        device = 1;
        row -= 8 * 2;
    }
    if (row >= 24 && row < 32) {
        device = 0;
        row -= 8 * 3;
    }

    lc.setLed(device, row, column, state);
}


