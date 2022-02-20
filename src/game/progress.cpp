#include "include/gamewidget.h"

void GameWidget::startGame(const int &number) {
    generations = number;
    myTimer.start();
    timer->start();
}

void GameWidget::stepGame() {
    generations = 1;
    myTimer.start();
    timer->start();
}

void GameWidget::stopGame() {
    timer->stop();
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
