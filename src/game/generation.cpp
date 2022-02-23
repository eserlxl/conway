#include "include/gamewidget.h"
#include <iostream>
#include <vector>

void GameWidget::newGeneration() {
    if (generations < 0)
        generations++;

    loopCount++;

    populationLimit = 16 * unsigned(sqrt(universeSizeX * universeSizeY));

    unChangedCell = 0;

    unsigned int index = 0;

    switch (loopType) {
        case 0:
            index = 0;
            population = 0;
            for (unsigned int i = 0; i < universeSizeY; i++) {
                for (unsigned int j = 0; j < universeSizeX; j++) {

                    next[index] = isAlive(index, i, j);

                    if (next[index] == universe[index] &&
                        nextValue[index] == value[index])
                        unChangedCell++;

                    index++;
                }
            }
            break;
        case 1:
            index = universeSizeX * universeSizeY - 1;
            population = 0;
            for (unsigned int i = 0; i < universeSizeY; i++) {
                for (unsigned int j = 0; j < universeSizeX; j++) {

                    next[index] = isAlive(index, universeSizeY - 1 - i, universeSizeX - 1 - j);

                    if (next[index] == universe[index] &&
                        nextValue[index] == value[index])
                        unChangedCell++;

                    index--;
                }
            }
            break;
        case 2:
            if (loopCount % 2) {
                index = 0;
                population = 0;
                for (unsigned int i = 0; i < universeSizeY; i++) {
                    for (unsigned int j = 0; j < 0 + universeSizeX; j++) {

                        next[index] = isAlive(index, i, j);

                        if (next[index] == universe[index] &&
                            nextValue[index] == value[index])
                            unChangedCell++;

                        index++;
                    }
                }
            } else {
                index = universeSizeX * universeSizeY - 1;
                population = 0;
                for (unsigned int i = 0; i < universeSizeY; i++) {
                    for (unsigned int j = 0; j < universeSizeX; j++) {

                        next[index] = isAlive(index, universeSizeY - 1 - i, universeSizeX - 1 - j);

                        if (next[index] == universe[index] &&
                            nextValue[index] == value[index])
                            unChangedCell++;

                        index--;
                    }
                }
            }
            break;
        case 3:
            std::vector<unsigned> randomXList, randomYList;
            randomXList.resize(universeSizeX * universeSizeY);
            randomYList.resize(universeSizeX * universeSizeY);
            for (unsigned int i = 0; i < universeSizeY; i++) {
                for (unsigned int j = 0; j < universeSizeX; j++) {
                    randomXList[index] = i;
                    randomYList[index] = j;
                    index++;
                }
            }

            srand(loopCount);

            population = 0;
            while (randomXList.size() > 0) {

                unsigned randomIndex = rand() % randomXList.size();
                unsigned i = randomXList[randomIndex];
                unsigned j = randomYList[randomIndex];

                unsigned k = i * universeSizeX + j;

                next[k] = isAlive(k, i, j);

                if (next[k] == universe[k] &&
                    nextValue[k] == value[k])
                    unChangedCell++;

                randomXList.erase(randomXList.begin() + randomIndex);
                randomYList.erase(randomYList.begin() + randomIndex);
            }
            break;
    }

    index = 0;
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            universe[index] = next[index];
            value[index] = nextValue[index];

            index++;
        }
    }

    workDonePrevious = getWorkDone();
    elapsedTimePrevious = elapsedTime;

    workDone = double(unChangedCell) / (int(universeSizeX) * int(universeSizeY));

    elapsedTime = double(myTimer.elapsed()) / 1000;

    double workSpeedPrevious = workDonePrevious / elapsedTimePrevious;
    workSpeed = workDone / elapsedTime;

    double a0 = -log(workSpeed) / elapsedTime;
    double a1 = -log(workSpeedPrevious) / elapsedTimePrevious;

    double remainingTime0 = -log(workSpeed / 100) / a0 - elapsedTime;
    double remainingTime1 = -log(workSpeedPrevious / 100) / a1 - elapsedTimePrevious;

    double remainingTimeNext = remainingTime0 / (remainingTime0 - remainingTime1);

    if (workSpeed > 0) {
        remainingTime = 0.5 * (remainingTime * workSpeedPrevious / workSpeed + (1 - workDone) / workSpeed);
    } else {
        remainingTime = 0;
    }

    remainingTime = max(remainingTime, remainingTimeNext);

    emit nextLoopStarts(true);

    if (unChangedCell == universeSizeX * universeSizeY) {
        /*QMessageBox::information(this,
                             tr("Game lost sense"),
                             tr("The End. Now game finished because all the next
           generations will be the same."), QMessageBox::Ok);*/
        qDebug() << "All the next generations will be the same.\n";

        stopGame();
        gameEnds(true);

        statusBar->showMessage(tr("All the next generations will be the same. Simulation stopped."));
        return;
    }

    update();
    generations--;
    if (generations == 0) {
        stopGame();
        gameEnds(true);
        statusBar->showMessage(tr("Iterations finished. Simulation stopped."));
        qDebug() << "Iterations finished.\n";
        /*QMessageBox::information(this, tr("Game finished."),
                                 tr("Iterations finished."), QMessageBox::Ok,
                                 QMessageBox::Cancel);*/
    }
}
