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
        row_ = row - 8 * 2;
    }
    if (row >= 24 && row < 32) {
        device = 0;
        row_ = row - 8 * 3;
    }

    lc.setLed(device, column, row_, state);
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
            setLed(row, column, tower[row][column] == 1);
        }
    }
}

void TowerStack::start() {
    setBrickSize(4);
    int brick_animation_speed_ = 150 - (getTowerHeight() * 4);

    setBrickAnimationSpeed(brick_animation_speed_);

    drawTower();
    generateBrick();
    drawBrick();
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

TowerStack::animation_direction TowerStack::getBrickAnimationDirection() {
    return brick_animation_direction;
}

void TowerStack::setBrickAnimationDirection(TowerStack::animation_direction brickAnimationDirection) {
    brick_animation_direction = brickAnimationDirection;
}

void TowerStack::timeBrickAnimation() {
    if (lastAnimationStepTime + getBrickAnimationSpeed() <= millis()) {
        doBrickAnimationStep();
        lastAnimationStepTime = millis();
    }
}


void TowerStack::animateBrick(int size, int height, animation_direction direction) {
    int tail, head;

    /* animateBrick left -> right */
    if (direction == RIGHT) {
        tail = brick_animation_step;
        head = brick_animation_step + size;
    }

    /* animateBrick right -> left */
    if (direction == LEFT) {
        tail = brick_animation_step + size;
        head = brick_animation_step;
    }

    tower[height][tail] = 0;
    tower[height][head] = 1;

    drawBrick();
}

void TowerStack::doBrickAnimationStep() {
    int size = getBrickSize();
    int height = getTowerHeight() - 1;

    int steps_left_to_right = 8 - size;

    animation_direction direction = getBrickAnimationDirection();

    /* animateBrick left -> right */
    if (direction == RIGHT) {
        animateBrick(size, height, direction);

        brick_animation_step = ++brick_animation_step;

        if (brick_animation_step == steps_left_to_right) {
            setBrickAnimationDirection(LEFT);
            return;
        }
    }

    /* animateBrick right -> left */
    if (direction == LEFT) {
        animateBrick(size, height, direction);
        brick_animation_step = --brick_animation_step;

        if (brick_animation_step < 0) {
            setBrickAnimationDirection(RIGHT);
            return;
        }
    }
}


void TowerStack::drawBrick() {
    int row = getTowerHeight() - 1;

    for (int column = 0; column < 8; ++column) {
        setLed(row, column, tower[row][column] == 1);
        Serial.print(tower[row][column]);
    }
    Serial.println();
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
}




