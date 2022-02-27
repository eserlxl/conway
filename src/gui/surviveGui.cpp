#include "include/mainwindow.h"

void MainWindow::on_algorithmBox_currentIndexChanged(int index) {
    game->setAlgorithm(index);
}

void MainWindow::on_powerLimitBox_valueChanged(int powerLimit) {
    game->setPowerLimit(powerLimit);
}

void MainWindow::on_customBornAlgorithmBox_currentIndexChanged(int index) {
    game->setCustomBornAlgorithm(index);
}

void MainWindow::on_customBornBox_valueChanged(double value) {
    game->setCustomBorn(value);
}

void MainWindow::on_customSurviveAlgorithmBox_currentIndexChanged(int index) {
    game->setCustomSurviveAlgorithm(index);
}

void MainWindow::on_customSurviveBox_valueChanged(double value) {
    game->setCustomSurvive(value);
}

void MainWindow::on_customBornRuleBox_currentIndexChanged(int index) {
    game->setCustomBornRule(index);
}

void MainWindow::on_customSurviveRuleBox_currentIndexChanged(int index) {
    game->setCustomSurviveRule(index);
}

void MainWindow::on_loopTypeComboBox_currentIndexChanged(int index) {
    game->setLoopType(index);
}

void MainWindow::on_popLimitSlider_valueChanged(int value) {
    game->updatePopLimit(value);
}