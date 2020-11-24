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
    /**
     * TowerStack constructor
     * @param lc  LedControl instance
     */
    TowerStack(LedControl lc);

    /*
     * resets everything and starts a new game
     */
    void newGame();

    /**
     * called when button is pressed. Evaluates move
     */
    void button_pressed();

    /**
     * calls doBrickAnimationStep() if delay is over
     */
    void timeBrickAnimation();

private:
    /* game */
    /**
     * Sets brick animation speed
     * @param tower_height
     */
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
    /**
     * sets led to state
     * @param row 0..31
     * @param column 0..7
     * @param state true | false
     */
    void setLed(int row, int column, bool state);

    /**
     * turns off every led
     * @param delay_time delay after each row
     */
    void resetMatrix(int delay_time);

    /* tower */
    /**
     * resets tower to default
     */
    void resetTower();

    /**
     * returns current tower height
     * @return tower_height
     */
    int getTowerHeight();

    /**
     * generates tower from template
     */
    void generateTower();

    /**
     * increments tower height
     * @return new tower height
     */
    int incrementTowerHeight();

    /**
     * draws tower on matrix
     */
    void drawTower();

    /* brick */
    /**
     * sets size / length of the brick
     * @param brickSize 1...6
     */
    void setBrickSize(int brickSize);

    /**
     * get current brick size
     * @return brick_size
     */
    int getBrickSize();

    /**
     * generates new brick,
     * resets brick_animation_direction to RIGHT
     *        and brick_animation_step to 0
     */
    void generateBrick();

    /**
     * draws brick
     */
    void drawBrick();

    /* brick animation */
    /**
     * set brick_animation_step to 0
     */
    void resetBrickAnimationStep();

    /**
     * sets direction
     * @param brickAnimationDirection LEFT | RIGHT
     */
    void setBrickAnimationDirection(animation_direction brickAnimationDirection);

    /**
     * returns current direction
     * @return direction (LEFT | RIGHT)
     */
    animation_direction getBrickAnimationDirection();

    /**
     * returns current brick animation speed
     * @return brick_animation_speed
     */
    int getBrickAnimationSpeed();

    /**
     * sets current brick animation speed
     * @param brickAnimationSpeed
     */
    void setBrickAnimationSpeed(int brickAnimationSpeed);

    /**
     * calculates new brick position
     * @param size brick size
     * @param height tower height
     * @param direction brick animation direction
     */
    void animateBrick(int size, int height, animation_direction direction);

    /**
     * makes brick move to new position
     */
    void doBrickAnimationStep();

    /* animations */
    /**
     * win animation
     */
    void animation_win();

    /**
     * loose animation
     */
    void animation_loose();

};


#endif //TOWERSTACK_TOWERSTACK_H
