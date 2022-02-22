#include "include/gamewidget.h"
#include <iostream>
#include <vector>

// i: Row, universeSizeY: Row Number
// j: Column, universeSizeX: Column Number

GameWidget::GameWidget(QWidget *parent)
        : QWidget(parent), timer(new QTimer(this)),
          statusBar(new QStatusBar(this)),
          generations(-1), loopCount(0),
          universeSizeX(100), universeSizeY(100), powerLimit(255), population(0),
          powerAlgorithmBornRule(0), powerAlgorithmBorn(0), powerAlgorithmSurviveRule(0), powerAlgorithmSurvive(0),
          loopType(0),
          workDone(0), elapsedTime(1) {
    timer->setInterval(1);
    m_masterColor = QColor(255, 255, 255);

    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));

    clear();
}

GameWidget::~GameWidget() {
}
