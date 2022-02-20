#include "include/gamewidget.h"

void GameWidget::resetUniverse() {
    delete[] universe;
    delete[] value;
    delete[] initialValue;
    delete[] next;
    delete[] nextValue;
    delete[] power;
    delete[] powerValue;
    delete[] checked;
    delete[] bornLoop;
    universe = new bool[universeSizeX * universeSizeY];
    value = new int[universeSizeX * universeSizeY];
    initialValue = new int[universeSizeX * universeSizeY];
    next = new bool[universeSizeX * universeSizeY];
    nextValue = new int[universeSizeX * universeSizeY];
    power = new int[universeSizeX * universeSizeY];
    powerValue = new int[universeSizeX * universeSizeY];
    checked = new int[universeSizeX * universeSizeY];
    bornLoop = new unsigned int[universeSizeX * universeSizeY];
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
    memset(universe, false, sizeof(bool) * universeSizeX * universeSizeY);
    memset(value, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(initialValue, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(next, false, sizeof(bool) * universeSizeX * universeSizeY);
    memset(nextValue, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(power, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(powerValue, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(checked, 0, sizeof(int) * universeSizeX * universeSizeY);
    memset(bornLoop, 0, sizeof(unsigned int) * universeSizeX * universeSizeY);
}

int GameWidget::cellSizeX() {
    return int(universeSizeX);
}

int GameWidget::cellSizeY() {
    return int(universeSizeY);
}

void GameWidget::setCellSizeX(const int &x) {
    if (x > 0 && x <= 1024) {
        universeSizeX = unsigned(x);
        resetUniverse();
        update();
    }
}

void GameWidget::setCellSizeY(const int &y) {
    if (y > 0 && y <= 1024) {
        universeSizeY = unsigned(y);
        resetUniverse();
        update();
    }
}

void GameWidget::resize(const int &x, const int &y) {
    if (x > 0 && x <= 1024 && y > 0 && y <= 1024) {
        universeSizeX = unsigned(x);
        universeSizeY = unsigned(y);
        resetUniverse();
        update();
    }
}
