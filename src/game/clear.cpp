#include "include/gamewidget.h"

void GameWidget::clear() {
    setWorkDone(0);
    emit nextLoopStarts(true);
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            unsigned int index = i * universeSizeX + j;
            universe[index] = false;
            next[index] = false;
            value[index] = 0;
            nextValue[index] = 0;
            initialValue[index] = 0;
            power[index] = 0;
            powerValue[index] = 0;
            bornLoop[index] = 0;
        }
    }
    gameEnds(true);
    update();
}
