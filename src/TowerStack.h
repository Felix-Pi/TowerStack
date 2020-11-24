//
// Created by Felix Pieschka on 23.11.20.
//

#ifndef TOWERSTACK_TOWERSTACK_H
#define TOWERSTACK_TOWERSTACK_H


#include <LedControl.h>

#define MAX_HEIGHT 32
#define COLUMNS 8

class TowerStack {
    LedControl lc;


public:
    TowerStack(LedControl lc);

    void newGame();

    void button_pressed();

    void timeBrickAnimation();

private:
    /* game */
    void setLevel(int tower_height);

    /* tower */
    int tower_height = 4;
    int tower[MAX_HEIGHT][COLUMNS];

    /* brick */
    int brick_size;

    /* brick animation */
    long lastAnimationStepTime = millis();
    int brick_animation_step = 0;
    enum animation_direction {
        LEFT, RIGHT
    };
    animation_direction brick_animation_direction = RIGHT;
    int brick_animation_speed;


    /* matrix */
    void setLed(int row, int column, bool state);

    void resetMatrix(int delay_time);

    /* tower */
    void resetTower();

    int getTowerHeight();

    void generateTower();

    int incrementTowerHeight();

    void drawTower();

    /* brick */
    void setBrickSize(int brickSize);

    int getBrickSize();

    void generateBrick();

    void drawBrick();

    /* brick animation */
    void resetBrickAnimationStep();

    void setBrickAnimationDirection(animation_direction brickAnimationDirection);

    animation_direction getBrickAnimationDirection();

    int getBrickAnimationSpeed();

    void setBrickAnimationSpeed(int brickAnimationSpeed);

    void animateBrick(int size, int height, animation_direction direction);

    void doBrickAnimationStep();

    /* animations */
    void animation_win();

    void animation_loose();

};


#endif //TOWERSTACK_TOWERSTACK_H
