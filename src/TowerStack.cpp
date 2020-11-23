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
    int device, row_;
    if (row < 0 || row >= MAX_HEIGHT || column < 0 || column > 7) return;

    if (row >= 0 && row < 8) {
        device = 3;
        row_ = row;
    }
    if (row >= 8 && row < 16) {
        device = 2;
        row_ = row - 8;
    }
    if (row >= 16 && row < 24) {
        device = 1;
        row_ = row - (8 * 2);
    }
    if (row >= 24 && row < 32) {
        device = 0;
        row_ = row - (8 * 3);
    }

    lc.setLed(device, row, column, state);
}

int TowerStack::getTowerHeight() {
    return tower_height;
}

int TowerStack::incrementTowerHeight() {
    if (tower_height == 31) return -1;
    return ++tower_height;
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
/*
    int brick_animation_speed_ = 150 - (getTowerHeight() * 4);

    setBrickAnimationSpeed(brick_animation_speed_);

    drawTower();
    generateBrick();
*/

    for (int row = 0; row < 32; ++row) {
        for (int column = 0; column < 8; ++column) {
            setLed(column, row, true);
            delay(50);
        }
    }

}

void TowerStack::generateBrick() {
    int height = incrementTowerHeight();
    int brick[8];

    for (int i = 0; i < 8; i++) {
        int temp = 0;
        if (i < getBrickSize()) {
            temp = 1;
        }
        tower[height - 1][i] = temp;
    }
}

int TowerStack::getBrickAnimationSpeed() {
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

void TowerStack::button_pressed() {
    int brick_row = getTowerHeight() - 1;
    int tower_row = getTowerHeight() - 2;

    for (int column = 0; column < 8; ++column) {
        if (tower[brick_row][column] == 1 && tower[tower_row][column] == 1) {
            tower[brick_row][column] = 1;
        } else {
            tower[brick_row][column] = 0;
        }
    }

    //check win
    //check loss

    drawTower();
    generateBrick();
    animateBrick();
}


