#include "include/gamewidget.h"

bool GameWidget::isAlive(unsigned int index, unsigned int row, unsigned int col) {

    //unsigned int index = row * universeSizeX + col;
    unsigned int neighbour = neighbourhood(row, col);

    // Don't analyse 3x3 empty rows - Loop accelerator :)
    if (power[index] == 0 && universe[index] == false) {
        return false;
    }

    bool survive = false;
    bool born = false;

    bool powerAlgorithmSurviveDecision = false;
    bool powerAlgorithmBornDecision = false;

    double powerAlgorithmSurviveParameter = 0;
    double powerAlgorithmBornParameter = 0;

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
                // There is no survive rule for Seeds!
            case 6: // Colony
                if (power[index] >= 2) {
                    survive = true;
                }
                break;
            case 7: // Custom
                switch (powerAlgorithmSurviveAlgorithm) {
                    case 1:
                        powerAlgorithmSurviveParameter = power[index] / double(neighbour);
                        break;
                    case 2:
                        powerAlgorithmSurviveParameter = powerValue[index] / double(neighbour);
                        break;
                    case 3:
                        powerAlgorithmSurviveParameter = power[index];
                        break;
                    case 4:
                        powerAlgorithmSurviveParameter = powerValue[index];
                        break;
                    default:
                        break;
                }

                if (powerAlgorithmSurviveAlgorithm) {
                    switch (powerAlgorithmSurviveRule) {
                        case 0:
                            powerAlgorithmSurviveDecision = powerAlgorithmSurviveParameter < powerAlgorithmSurvive;
                            break;
                        case 1:
                            powerAlgorithmSurviveDecision = powerAlgorithmSurviveParameter > powerAlgorithmSurvive;
                            break;
                        case 2:
                            powerAlgorithmSurviveDecision = powerAlgorithmSurviveParameter <= powerAlgorithmSurvive;
                            break;
                        case 3:
                            powerAlgorithmSurviveDecision = powerAlgorithmSurviveParameter >= powerAlgorithmSurvive;
                            break;
                        case 4:
                            powerAlgorithmSurviveDecision =
                                    fabs(powerAlgorithmSurviveParameter - powerAlgorithmSurvive) < 1e-15;
                            break;
                        case 5:
                            powerAlgorithmSurviveDecision =
                                    fabs(powerAlgorithmSurviveParameter - powerAlgorithmSurvive) > 1e-15;
                            break;
                        default:
                            break;
                    }
                }
                break;
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
            case 6: // Colony
                if (power[index] >= 3) {
                    born = true;
                }
                break;
            case 7: // Custom
                switch (powerAlgorithmBornAlgorithm) {
                    case 1:
                        powerAlgorithmBornParameter = power[index] / double(neighbour);
                        break;
                    case 2:
                        powerAlgorithmBornParameter = powerValue[index] / double(neighbour);
                        break;
                    case 3:
                        powerAlgorithmBornParameter = power[index];
                        break;
                    case 4:
                        powerAlgorithmBornParameter = powerValue[index];
                        break;
                    default:
                        break;
                }

                if (powerAlgorithmBornAlgorithm) {
                    switch (powerAlgorithmBornRule) {
                        case 0:
                            powerAlgorithmBornDecision = powerAlgorithmBornParameter < powerAlgorithmBorn;
                            break;
                        case 1:
                            powerAlgorithmBornDecision = powerAlgorithmBornParameter > powerAlgorithmBorn;
                            break;
                        case 2:
                            powerAlgorithmBornDecision = powerAlgorithmBornParameter <= powerAlgorithmBorn;
                            break;
                        case 3:
                            powerAlgorithmBornDecision = powerAlgorithmBornParameter >= powerAlgorithmBorn;
                            break;
                        case 4:
                            powerAlgorithmBornDecision = fabs(powerAlgorithmBornParameter - powerAlgorithmBorn) < 1e-15;
                            break;
                        case 5:
                            powerAlgorithmBornDecision = fabs(powerAlgorithmBornParameter - powerAlgorithmBorn) > 1e-15;
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
    }

    if (population >= populationLimit) {
        born = false;
        powerAlgorithmBornDecision = false;
    }

    // survive?
    if (value[index] > 0) {
        if (population < populationLimit && (survive || powerAlgorithmSurviveDecision)) {
            if (nextValue[index] < powerLimit) {
                nextValue[index]++;
            }
        } else if (nextValue[index] > 0) {
            nextValue[index]--;
        }
    }
        // born
    else if (born || powerAlgorithmBornDecision) {
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

void GameWidget::setPowerAlgorithmSurviveAlgorithm(int a) {
    powerAlgorithmSurviveAlgorithm = a;
}

void GameWidget::setPowerAlgorithmSurviveRule(int a) {
    powerAlgorithmSurviveRule = a;
}

void GameWidget::setPowerAlgorithmSurvive(double a) {
    powerAlgorithmSurvive = a;
}

void GameWidget::setPowerAlgorithmBornAlgorithm(int a) {
    powerAlgorithmBornAlgorithm = a;
}

void GameWidget::setPowerAlgorithmBornRule(int a) {
    powerAlgorithmBornRule = a;
}

void GameWidget::setPowerAlgorithmBorn(double a) {
    powerAlgorithmBorn = a;
}

void GameWidget::setLoopType(int type) {
    loopType = type;
}

unsigned int GameWidget::getLoopCount() {
    return loopCount;
}

