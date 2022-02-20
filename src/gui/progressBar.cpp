#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateProgressBar() {
    ui->Tamamlanma->setValue(int(game->getWorkDone() * 100));

    ui->workDoneLabel->setText("Work Done: " + QString::number(game->getWorkDone() * 100) + " %");

    ui->workSpeedLabel->setText("Work Speed: " + QString::number(3600 * game->getWorkSpeed()) + " 1/h ");

    double elapsedTime = game->getElapsedTime();
    if (elapsedTime > 3600) {
        ui->elapsedTime->setText("Elapsed Time: " + QString::number(elapsedTime / 3600) + " hours");
    } else if (elapsedTime > 60) {
        ui->elapsedTime->setText("Elapsed Time: " + QString::number(elapsedTime / 60) + " minutes");
    } else {
        ui->elapsedTime->setText("Elapsed Time: " + QString::number(elapsedTime) + " seconds");
    }

    double remainingTime = game->getRemainingTime();
    if (remainingTime > 3600) {
        ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime / 3600) + " hours");
    } else if (remainingTime > 60) {
        ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime / 60) + " minutes");
    } else {
        ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime) + " seconds");
    }

    ui->populationLabel->setText("Population: " + QString::number(game->getPopulation()));

    ui->loopCountLabel->setText("Loop: " + QString::number(game->getLoopCount()));
}
