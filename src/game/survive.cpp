#include "include/gamewidget.h"

bool GameWidget::isAlive(unsigned int index, unsigned int row, unsigned int col) {

    //unsigned int index = row * universeSizeX + col;
    unsigned int neighbour = neighbourhood(row, col);

    bool survive = false;
    bool born = false;

    bool stabilitySurviveDecision = false;
    bool stabilityBornDecision = false;

    double stabilitySurviveParameter = 0;

    switch (stabilitySurviveAlgorithm) {
        case 1:
            stabilitySurviveParameter = power[index] / double(neighbour);
            break;
        case 2:
            stabilitySurviveParameter = powerValue[index] / double(neighbour);
            break;
        case 3:
            stabilitySurviveParameter = power[index];
            break;
        case 4:
            stabilitySurviveParameter = powerValue[index];
            break;
        default:
            break;
    }

    if (stabilitySurviveAlgorithm) {
        switch (stabilitySurviveRule) {
            case 0:
                stabilitySurviveDecision = stabilitySurviveParameter < stabilitySurvive;
                break;
            case 1:
                stabilitySurviveDecision = stabilitySurviveParameter > stabilitySurvive;
                break;
            case 2:
                stabilitySurviveDecision = fabs(stabilitySurviveParameter - stabilitySurvive) < 1e-15;
                break;
            case 3:
                stabilitySurviveDecision = fabs(stabilitySurviveParameter - stabilitySurvive) > 1e-15;
                break;
            default:
                break;
        }
    }

    double stabilityBornParameter = 0;

    switch (stabilityBornAlgorithm) {
        case 1:
            stabilityBornParameter = power[index] / double(neighbour);
            break;
        case 2:
            stabilityBornParameter = powerValue[index] / double(neighbour);
            break;
        case 3:
            stabilityBornParameter = power[index];
            break;
        case 4:
            stabilityBornParameter = powerValue[index];
            break;
        default:
            break;
    }

    if (stabilityBornAlgorithm) {
        switch (stabilityBornRule) {
            case 0:
                stabilityBornDecision = stabilityBornParameter < stabilityBorn;
                break;
            case 1:
                stabilityBornDecision = stabilityBornParameter > stabilityBorn;
                break;
            case 2:
                stabilityBornDecision = fabs(stabilityBornParameter - stabilityBorn) < 1e-15;
                break;
            case 3:
                stabilityBornDecision = fabs(stabilityBornParameter - stabilityBorn) > 1e-15;
                break;
            default:
                break;
        }
    }


    // survive?
    if (universe[index] == true) {
        switch (algorithm) {
            case 0: // John Conway, Life Game
                if (power[index] == 2 || power[index] == 3) {
                    survive = true;
                }
                break;
            case 1: // Move
                if (power[index] == 2 || power[index] == 4 || power[index] == 5) {
                    survive = true;
                }
                break;
            case 2: // Maze
                if (power[index] > 0 && power[index] < 6) {
                    survive = true;
                }
                break;
            case 3: // Mazecritic
                if (power[index] > 0 && power[index] < 5) {
                    survive = true;
                }
                break;
            case 4: // Flock
                if (power[index] > 0 && power[index] < 2) {
                    survive = true;
                }
                break;
                // Seeds için survive kuralı yok
            default:
                break;
        }
    }
        // born?
    else {
        switch (algorithm) {
            case 0: // John Conway, Life Game
                if (power[index] == 3) {
                    born = true;
                }
                break;
            case 1: // Move
                if (power[index] == 3 || power[index] == 6 || power[index] == 8) {
                    born = true;
                }
                break;
            case 2: // Maze
                if (power[index] == 3) {
                    born = true;
                }
                break;
            case 3: // Mazecritic
                if (power[index] == 3) {
                    born = true;
                }
                break;
            case 4: // Flock
                if (power[index] == 3) {
                    born = true;
                }
                break;
            case 5: // Seeds
                if (power[index] == 2) {
                    born = true;
                }
                break;
        }
    }

    if (population >= populationLimit) {
        born = false;
        stabilityBornDecision = false;
    }

    // survive?
    if (value[index] > 0) {
        if ((population < populationLimit || loopCount - bornLoop[index] > 16) &&
            (survive || stabilitySurviveDecision)) {
            if (nextValue[index] < powerLimit) {
                nextValue[index]++;
            }
        } else if (nextValue[index] > 0) {
            nextValue[index]--;
        }
    }
        // born
    else if ((bornLoop[index] == 0 || loopCount - bornLoop[index] > 16) && (born || stabilityBornDecision)) {
        nextValue[index] = 1;
        bornLoop[index] = loopCount;
    }

    if (nextValue[index]) {
        population++;
    }

    return nextValue[index] > 0;
}

unsigned int GameWidget::getPopulation() {
    return population;
}

void GameWidget::setPowerLimit(int limit) {
    powerLimit = limit;
}

int GameWidget::getPowerLimit() {
    return powerLimit;
}

void GameWidget::setAlgorithm(int a) {
    algorithm = a;
}

void GameWidget::setStability(int s) {
    stability = s;
}

void GameWidget::setStabilitySurviveAlgorithm(int a) {
    stabilitySurviveAlgorithm = a;
}

void GameWidget::setStabilitySurviveRule(int a) {
    stabilitySurviveRule = a;
}

void GameWidget::setStabilitySurvive(double a) {
    stabilitySurvive = a;
}

void GameWidget::setStabilityBornAlgorithm(int a) {
    stabilityBornAlgorithm = a;
}

void GameWidget::setStabilityBornRule(int a) {
    stabilityBornRule = a;
}

void GameWidget::setStabilityBorn(double a) {
    stabilityBorn = a;
}
