//
// Created by Felix Pieschka on 23.11.20.
//
#include "TowerStack.h"

#include <Arduino.h>
#include <LedControl.h>

TowerStack::TowerStack(LedControl lc) : lc(lc) {
    int devices = lc.getDeviceCount();
}


void TowerStack::setLed(int row, int column, bool state) {
    int device;
    if (row < 0 || row >= MAX_HEIGHT || column < 0 || column > 7) return;

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

int TowerStack::getTowerHeight() {
    return height;
}

int TowerStack::incrementHeight() {
    if (height == 31) return -1;
    return ++height;
}

void TowerStack::setBrickSize(int brickSize) {
    brick_size = brickSize;
}

int TowerStack::getBrickSize() {
    return brick_size;
}


void TowerStack::drawTower() {
    for (int row = 0; row < getTowerHeight(); ++row) {
        for (int column = 0; column < 8; ++column) {
            setLed(column, row, tower[row][column] == 1);
        }
    }
}

void TowerStack::start() {
    setBrickAnimationSpeed(300);
    drawTower();

    generateBrick();
}

void TowerStack::generateBrick() {
    int tower_height = incrementHeight();
    int brick[8];

    for (int i = 0; i < 8; i++) {
        int temp = 0;
        if (i < getBrickSize()) {
            temp = 1;
        }
        tower[tower_height - 1][i] = temp;
    }
}

int TowerStack::getBrickAnimationSpeed() const {
    return brick_animation_speed;
}

void TowerStack::setBrickAnimationSpeed(int brickAnimationSpeed) {
    brick_animation_speed = brickAnimationSpeed;
}

void TowerStack::animateBrick() {
    int size = getBrickSize();
    int height = getTowerHeight() - 1;

    //left -> right
    for (int i = 0; i < 8 - size; ++i) {
        delay(getBrickAnimationSpeed());
        int tail = i;
        int head = i + size;

        tower[height][tail] = 0;
        tower[height][head] = 1;
        drawBrick();
    }

    //right -> left
    for (int i = 7 - size; i >= 0; --i) {
        delay(getBrickAnimationSpeed());
        int tail = i + size;
        int head = i;

        tower[height][tail] = 0;
        tower[height][head] = 1;
        drawBrick();
    }

}

void TowerStack::drawBrick() {
    int row = getTowerHeight() - 1;

    for (int column = 0; column < 8; ++column) {
        setLed(column, row, tower[row][column] == 1);
        Serial.print(tower[row][column]);
    }
    Serial.println();
}


void TowerStack::test() {
    animateBrick();
}

