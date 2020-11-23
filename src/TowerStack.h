#ifndef TOWERSTACK_TOWERSTACK_H
#define TOWERSTACK_TOWERSTACK_H


#include <LedControl.h>

class TowerStack {
    LedControl lc;

public:
    TowerStack(LedControl lc);

    int max_height;

private:


    void setLed(int row, int column, bool state);

};


#endif //TOWERSTACK_TOWERSTACK_H
