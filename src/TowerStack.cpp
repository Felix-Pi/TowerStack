//
// Created by Felix Pieschka on 23.11.20.
//
#include "TowerStack.h"

#include <Arduino.h>
#include <LedControl.h>

TowerStack::TowerStack(LedControl lc) : lc(lc) {
    int devices = lc.getDeviceCount();
}

/* matrix */
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

void TowerStack::resetMatrix(int delay_time) {
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 8; ++j) {
            setLed(i, j, false);
        }
        delay(delay_time);
    }
}

/* game */
void TowerStack::setLevel(int tower_height) {
    int animation_speed = 150 - (tower_height * 4);
    setBrickAnimationSpeed(animation_speed);
}

void TowerStack::newGame() {
    resetMatrix(0);
    delay(500);
    generateTower();
    drawTower();

    setLevel(tower_height);

    setBrickSize(4);

    delay(1000);
    generateBrick();
    drawBrick();
}

void TowerStack::button_pressed() {
    int brick_row = getTowerHeight() - 1;
    int tower_row = getTowerHeight() - 2;

    int new_brick_size = 0;

    for (int column = 0; column < 8; ++column) {
        if (tower[brick_row][column] == 1 && tower[tower_row][column] == 1) {
            tower[brick_row][column] = 1;
            new_brick_size = ++new_brick_size;
        } else {
            tower[brick_row][column] = 0;
        }
    }

    //lose
    if (new_brick_size == 0) {
        animation_loose();
        newGame();
        return;
    }

    //win
    if (tower_height == 32) {
        resetTower();
        animation_win();
        newGame();
        return;
    }

    setBrickSize(new_brick_size);
    setLevel(tower_height);
    drawTower();
    generateBrick();
}

/* tower */
void TowerStack::resetTower() {
    tower_height = 4;

    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 8; ++j) {
            tower[i][j] = 0;
        }
    }
}

int TowerStack::getTowerHeight() {
    return tower_height;
}

void TowerStack::generateTower() {
    resetTower();

    int tower_template[MAX_HEIGHT][COLUMNS] = {
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 1, 0, 0}
    };

    for (int i = 0; i < tower_height; ++i) {
        for (int j = 0; j < 8; ++j) {
            tower[i][j] = tower_template[i][j];
        }
    }
}

int TowerStack::incrementTowerHeight() {
    if (tower_height == 31) return -1;
    return ++tower_height;
}

void TowerStack::drawTower() {
    for (int row = 0; row < getTowerHeight(); ++row) {
        for (int column = 0; column < 8; ++column) {
            setLed(row, column, tower[row][column] == 1);
        }
    }
}

/* brick */
void TowerStack::setBrickSize(int brickSize) {
    brick_size = brickSize;
}

int TowerStack::getBrickSize() {
    return brick_size;
}

void TowerStack::generateBrick() {
    setBrickAnimationDirection(RIGHT);
    resetBrickAnimationStep();

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

void TowerStack::drawBrick() {
    int row = getTowerHeight() - 1;

    for (int column = 0; column < 8; ++column) {
        setLed(row, column, tower[row][column] == 1);
    }
}

/* brick animation */
void TowerStack::resetBrickAnimationStep() {
    brick_animation_step = 0;
}

void TowerStack::setBrickAnimationDirection(TowerStack::animation_direction brickAnimationDirection) {
    brick_animation_direction = brickAnimationDirection;
}

TowerStack::animation_direction TowerStack::getBrickAnimationDirection() {
    return brick_animation_direction;
}

int TowerStack::getBrickAnimationSpeed() {
    return brick_animation_speed;
}

void TowerStack::setBrickAnimationSpeed(int brickAnimationSpeed) {
    brick_animation_speed = brickAnimationSpeed;
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

void TowerStack::doBrickAnimationStep() { //ToDo: fix double delay
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

void TowerStack::timeBrickAnimation() {
    if (lastAnimationStepTime + getBrickAnimationSpeed() <= millis()) {
        doBrickAnimationStep();
        lastAnimationStepTime = millis();
    }
}

/* animations */
void TowerStack::animation_win() {
    int max_brightness = 6;
    int delay_time = 100;

    for (int reps = 0; reps < 3; reps++) {
        for (int brightness = 0; brightness < max_brightness; ++brightness) {
            for (int device = 0; device < lc.getDeviceCount(); ++device) {
                lc.setIntensity(device, brightness);
            }
            delay(delay_time);
        }
        for (int brightness = max_brightness; brightness >= 1; --brightness) {
            for (int device = lc.getDeviceCount(); device >= 0; --device) {
                lc.setIntensity(device, brightness);
            }
            delay(delay_time);
        }
    }

    for (int row = getTowerHeight(); row >= tower_height; --row) {
        for (int column = 0; column < 8; ++column) {
            setLed(row, column, false);
        }
        delay(10 + 3 * row);
    }

}

void TowerStack::animation_loose() {
    int delay_time = 15;

    resetMatrix(delay_time);

    for (int device = 0; device < lc.getDeviceCount(); ++device) {
        for (int row = 0; row < 8; ++row) {
            lc.setLed(device, row, row, true);
            lc.setLed(device, row, 7 - row, true);
            delay(15);
        }
    }

    resetMatrix(delay_time);
}






