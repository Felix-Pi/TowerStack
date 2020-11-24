#ifndef TOWERSTACK_TOWERSTACK_H
#define TOWERSTACK_TOWERSTACK_H


#include <LedControl.h>

#define MAX_HEIGHT 32
#define COLUMNS 8

class TowerStack {
    LedControl lc;


public:
    TowerStack(LedControl lc);

    void start();

    void button_pressed();

    void test();

private:
    int tower_height = 4;
    int tower[MAX_HEIGHT][COLUMNS] = {
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 1, 0, 0}
    };

    enum animation_direction {
        LEFT, RIGHT
    };


    int brick_animation_step = 0;

    animation_direction brick_animation_direction = RIGHT;

    animation_direction getBrickAnimationDirection();

    void setBrickAnimationDirection(animation_direction brickAnimationDirection);

    int brick_animation_speed;
    int brick_size;


    int getTowerHeight();

    int incrementTowerHeight();

    void drawTower();

    void setBrickSize(int brickSize);

    int getBrickSize();

    void generateBrick();

    int getBrickAnimationSpeed();

    void setBrickAnimationSpeed(int brickAnimationSpeed);

    void animateBrick(int size, int height, animation_direction direction);

    void doBrickAnimationStep();


    void drawBrick();


    void setLed(int row, int column, bool state);

};


#endif //TOWERSTACK_TOWERSTACK_H
