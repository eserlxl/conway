#include "include/gamewidget.h"

void GameWidget::resetUniverse() {
    universe.clear();
    value.clear();
    initialValue.clear();
    next.clear();
    nextValue.clear();
    power.clear();
    powerValue.clear();
    bornLoop.clear();

    universe.resize(universeSizeX * universeSizeY);
    value.resize(universeSizeX * universeSizeY);
    initialValue.resize(universeSizeX * universeSizeY);
    next.resize(universeSizeX * universeSizeY);
    nextValue.resize(universeSizeX * universeSizeY);
    power.resize(universeSizeX * universeSizeY);
    powerValue.resize(universeSizeX * universeSizeY);
    bornLoop.resize(universeSizeX * universeSizeY);
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
