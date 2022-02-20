#include "include/gamewidget.h"

void GameWidget::newGeneration() {
    if (generations < 0)
        generations++;

    loopCount++;

    populationLimit = unsigned(sqrt(universeSizeX * universeSizeY));

    unChangedCell = 0;

    //QRandomGenerator randomNumber;
    //randomNumber.seed(loopCount);
    //unsigned int shiftX = randomNumber.bounded(universeSizeX);
    //unsigned int shiftY = randomNumber.bounded(universeSizeY);

    //unsigned int index = shiftY*universeSizeY + shiftX;

    unsigned int index = 0;

    switch (loopType) {
        case 0:
            index = 0;
            population = 0;
            for (unsigned int i = 0; i < universeSizeY; i++) {
                for (unsigned int j = 0; j < 0 + universeSizeX; j++) {
                    //unsigned int index = (i%universeSizeY * universeSizeX + j%universeSizeX); // Sürekli aynı sırada kontrol etmiyoruz

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
                    //unsigned int index = (i%universeSizeY * universeSizeX + j%universeSizeX); // Sürekli aynı sırada kontrol etmiyoruz

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
                        //unsigned int index = (i%universeSizeY * universeSizeX + j%universeSizeX); // Sürekli aynı sırada kontrol etmiyoruz

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
                        //unsigned int index = (i%universeSizeY * universeSizeX + j%universeSizeX); // Sürekli aynı sırada kontrol etmiyoruz

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
            for (unsigned int i = 0; i < universeSizeY; i++) {
                for (unsigned int j = 0; j < 0 + universeSizeX; j++) {
                    checked[index] = 0;
                    index++;
                }
            }

            srand(loopCount);

            index = 0;
            population = 0;
            unsigned int i = 0;
            unsigned int j = 0;
            while (1) {
                //unsigned int index = (i%universeSizeY * universeSizeX + j%universeSizeX); // Sürekli aynı sırada kontrol etmiyoruz

                i = unsigned(rand());
                j = unsigned(rand());

                unsigned int k = (i % universeSizeY * universeSizeX + j % universeSizeX);

                if (checked[k] == 0) {
                    next[k] = isAlive(k, i % universeSizeY, j % universeSizeX);

                    if (next[k] == universe[k] &&
                        nextValue[k] == value[k])
                        unChangedCell++;

                    index++;
                    checked[k] = 1;
                }

                if (index >= universeSizeY * universeSizeX) {
                    break;
                }
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

    if (0 && unChangedCell == universeSizeX * universeSizeY) {
        /*QMessageBox::information(this,
                             tr("Game lost sense"),
                             tr("The End. Now game finished because all the next
           generations will be the same."), QMessageBox::Ok);*/
        qDebug() << "All the next generations will be the same.\n";
        //stopGame();
        //gameEnds(true);
        return;
    }

    update();
    generations--;
    if (generations == 0) {
        stopGame();
        gameEnds(true);
        qDebug() << "Iterations finished.\n";
        /*QMessageBox::information(this, tr("Game finished."),
                                 tr("Iterations finished."), QMessageBox::Ok,
                                 QMessageBox::Cancel);*/
    }
}
