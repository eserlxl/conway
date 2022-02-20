#include "include/mainwindow.h"

void MainWindow::on_algorithmBox_currentIndexChanged(int index) {
    game->setAlgorithm(index);
}

void MainWindow::on_powerLimitBox_valueChanged(int powerLimit) {
    game->setPowerLimit(powerLimit);
}

void MainWindow::on_powerAlgorithmBornAlgorithmBox_currentIndexChanged(int index) {
    game->setPowerAlgorithmBornAlgorithm(index);
}

void MainWindow::on_powerAlgorithmBornBox_valueChanged(double value) {
    game->setPowerAlgorithmBorn(value);
}

void MainWindow::on_powerAlgorithmSurviveAlgorithmBox_currentIndexChanged(int index) {
    game->setPowerAlgorithmSurviveAlgorithm(index);
}

void MainWindow::on_powerAlgorithmSurviveBox_valueChanged(double value) {
    game->setPowerAlgorithmSurvive(value);
}

void MainWindow::on_powerAlgorithmBornRuleBox_currentIndexChanged(int index) {
    game->setPowerAlgorithmBornRule(index);
}

void MainWindow::on_powerAlgorithmSurviveRuleBox_currentIndexChanged(int index) {
    game->setPowerAlgorithmSurviveRule(index);
}

void MainWindow::on_loopTypeComboBox_currentIndexChanged(int index) {
    game->setLoopType(index);
}
