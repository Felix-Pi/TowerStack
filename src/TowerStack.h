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

    void test();

    void timeBrickAnimation();

private:
    int tower_height;
    int tower[MAX_HEIGHT][COLUMNS];

    enum animation_direction {
        LEFT, RIGHT
    };

    void resetMatrix() {
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 8; ++j) {
                setLed(i, j, false);
            }
        }
    }

    void generateTower() {
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 8; ++j) {
                tower[i][j] = 0;
            }
        }

        int tower_template[MAX_HEIGHT][COLUMNS] = {
                {0, 1, 1, 1, 1, 1, 1, 0},
                {0, 1, 1, 1, 1, 1, 1, 0},
                {0, 1, 1, 1, 1, 1, 1, 0},
                {0, 0, 1, 1, 1, 1, 0, 0}
        };

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                tower[i][j] = tower_template[i][j];
            }
        }

        tower_height = 4;
    }

    long lastAnimationStepTime = millis();

    int brick_animation_step = 0;

    void restBrickAnimationStep();

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
