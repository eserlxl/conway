#include "include/gamewidget.h"

// i: Row, universeSizeY: Row Number
// j: Column, universeSizeX: Column Number

GameWidget::GameWidget(QWidget *parent)
        : QWidget(parent), timer(new QTimer(this)), generations(-1), loopCount(0),
          universeSizeX(50), universeSizeY(50), stability(0), powerLimit(1), population(0),
          stabilityBornRule(0), stabilityBorn(0), stabilitySurviveRule(0), stabilitySurvive(0),
          workDone(0), elapsedTime(1) {
    timer->setInterval(300);
    m_masterColor = QColor(255, 255, 255);
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

GameWidget::~GameWidget() {
    delete[] universe;
    delete[] value;
    delete[] initialValue;
    delete[] next;
    delete[] nextValue;
    delete[] power;
    delete[] powerValue;
    delete[] checked;
    delete[] bornLoop;
}
