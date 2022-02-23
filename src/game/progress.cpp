#include "include/gamewidget.h"

void GameWidget::startGame(const int &number) {
    generations = number;
    myTimer.start();
    timer->start();
    statusBar->showMessage(tr("Simulation is running..."));
}

void GameWidget::stepGame() {
    generations = 1;
    myTimer.start();
    timer->start();
    statusBar->showMessage(tr("Simulation advanced for only one step."));
}

void GameWidget::stopGame() {
    timer->stop();
    statusBar->showMessage(tr("Simulation stopped."));
}

void GameWidget::clear() {
    setWorkDone(0);
    emit nextLoopStarts(true);

    universe.clear();
    value.clear();
    initialValue.clear();
    next.clear();
    nextValue.clear();
    power.clear();
    powerValue.clear();
    bornLoop.clear();

    resetUniverse();

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
    emit gameEnds(true);
    update();
    statusBar->showMessage(tr("Ready"));
}

int GameWidget::interval() {
    return timer->interval();
}

void GameWidget::setInterval(int msec) {
    timer->setInterval(msec);
}

void GameWidget::setWorkDone(double ratio) {
    workDone = ratio;
}

double GameWidget::getWorkDone() {
    return workDone;
}

void GameWidget::setWorkSpeed(double speed) {
    workSpeed = speed;
}

double GameWidget::getWorkSpeed() {
    return workSpeed;
}

void GameWidget::setRemainingTime(double time) {
    remainingTime = time;
}

double GameWidget::getRemainingTime() {
    return remainingTime;
}

double GameWidget::getElapsedTime() {
    return elapsedTime;
}
