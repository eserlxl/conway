#include "include/mainwindow.h"

void MainWindow::on_algorithmBox_currentIndexChanged(int index) {
    game->setAlgorithm(index);
}

void MainWindow::on_powerLimitBox_valueChanged(int powerLimit) {
    game->setPowerLimit(powerLimit);
}

void MainWindow::on_powerAlgorithmBornAlgorithmBox_currentIndexChanged(int index) {
    game->setpowerAlgorithmBornAlgorithm(index);
}

void MainWindow::on_powerAlgorithmBornBox_valueChanged(double value) {
    game->setpowerAlgorithmBorn(value);
}

void MainWindow::on_powerAlgorithmSurviveAlgorithmBox_currentIndexChanged(int index) {
    game->setpowerAlgorithmSurviveAlgorithm(index);
}

void MainWindow::on_powerAlgorithmSurviveBox_valueChanged(double value) {
    game->setpowerAlgorithmSurvive(value);
}

void MainWindow::on_powerAlgorithmBornRuleBox_currentIndexChanged(int index) {
    game->setpowerAlgorithmBornRule(index);
}

void MainWindow::on_powerAlgorithmSurviveRuleBox_currentIndexChanged(int index) {
    game->setpowerAlgorithmSurviveRule(index);
}

void MainWindow::on_loopTypeComboBox_currentIndexChanged(int index) {
    game->setLoopType(index);
}
