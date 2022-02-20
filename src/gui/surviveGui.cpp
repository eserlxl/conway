#include "include/mainwindow.h"

void MainWindow::on_powerLimitBox_valueChanged(int powerLimit) {
    game->setPowerLimit(powerLimit);
}

void MainWindow::on_stabilityBornAlgorithmBox_currentIndexChanged(int index) {
    game->setStabilityBornAlgorithm(index);
}

void MainWindow::on_stabilityBornBox_valueChanged(double value) {
    game->setStabilityBorn(value);
}

void MainWindow::on_stabilitySurviveAlgorithmBox_currentIndexChanged(int index) {
    game->setStabilitySurviveAlgorithm(index);
}

void MainWindow::on_stabilitySurviveBox_valueChanged(double value) {
    game->setStabilitySurvive(value);
}

void MainWindow::on_stabilityBornRuleBox_currentIndexChanged(int index) {
    game->setStabilityBornRule(index);
}

void MainWindow::on_stabilitySurviveRuleBox_currentIndexChanged(int index) {
    game->setStabilitySurviveRule(index);
}

void MainWindow::on_stabilityBox_valueChanged(int s) {
    game->setStability(s);
}

void MainWindow::on_algorithmBox_currentIndexChanged(int index) {
    game->setAlgorithm(index);
}
