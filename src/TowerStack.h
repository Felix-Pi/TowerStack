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

    void test();


private:
    int tower_height = 4;
    int tower[MAX_HEIGHT][COLUMNS] = {
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 1, 0, 0}
    };

    int brick_animation_speed;
    int brick_size = 5;


    int getTowerHeight();

    int incrementTowerHeight();

    void drawTower();

    void setBrickSize(int brickSize);

    int getBrickSize();

    void generateBrick();

    int getBrickAnimationSpeed() const;

    void setBrickAnimationSpeed(int brickAnimationSpeed);

    void animateBrick();

    void drawBrick();

    void button_pressed();


    void setLed(int row, int column, bool state);

};


#endif //TOWERSTACK_TOWERSTACK_H
