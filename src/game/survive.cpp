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

    bool customSurviveDecision = false;
    bool customBornDecision = false;

    double customSurviveParameter = 0;
    double customBornParameter = 0;

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
                switch (customSurviveAlgorithm) {
                    case 1:
                        customSurviveParameter = power[index] / double(neighbour);
                        break;
                    case 2:
                        customSurviveParameter = powerValue[index] / double(neighbour);
                        break;
                    case 3:
                        customSurviveParameter = power[index];
                        break;
                    case 4:
                        customSurviveParameter = powerValue[index];
                        break;
                    default:
                        break;
                }

                if (customSurviveAlgorithm) {
                    switch (customSurviveRule) {
                        case 0:
                            customSurviveDecision = customSurviveParameter < customSurvive;
                            break;
                        case 1:
                            customSurviveDecision = customSurviveParameter > customSurvive;
                            break;
                        case 2:
                            customSurviveDecision = customSurviveParameter <= customSurvive;
                            break;
                        case 3:
                            customSurviveDecision = customSurviveParameter >= customSurvive;
                            break;
                        case 4:
                            customSurviveDecision = fabs(customSurviveParameter - customSurvive) < 1e-15;
                            break;
                        case 5:
                            customSurviveDecision = fabs(customSurviveParameter - customSurvive) > 1e-15;
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
                switch (customBornAlgorithm) {
                    case 1:
                        customBornParameter = power[index] / double(neighbour);
                        break;
                    case 2:
                        customBornParameter = powerValue[index] / double(neighbour);
                        break;
                    case 3:
                        customBornParameter = power[index];
                        break;
                    case 4:
                        customBornParameter = powerValue[index];
                        break;
                    default:
                        break;
                }

                if (customBornAlgorithm) {
                    switch (customBornRule) {
                        case 0:
                            customBornDecision = customBornParameter < customBorn;
                            break;
                        case 1:
                            customBornDecision = customBornParameter > customBorn;
                            break;
                        case 2:
                            customBornDecision = customBornParameter <= customBorn;
                            break;
                        case 3:
                            customBornDecision = customBornParameter >= customBorn;
                            break;
                        case 4:
                            customBornDecision = fabs(customBornParameter - customBorn) < 1e-15;
                            break;
                        case 5:
                            customBornDecision = fabs(customBornParameter - customBorn) > 1e-15;
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
        customBornDecision = false;
    }

    // survive?
    if (value[index] > 0) {
        if (population <= populationLimit && (survive || customSurviveDecision)) {
            if (nextValue[index] < powerLimit) {
                nextValue[index]++;
            }
        } else if (nextValue[index] > 0) {
            nextValue[index]--;
        }
    }
        // born
    else if (born || customBornDecision) {
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

void GameWidget::setCustomSurviveAlgorithm(int a) {
    customSurviveAlgorithm = a;
}

void GameWidget::setCustomSurviveRule(int a) {
    customSurviveRule = a;
}

void GameWidget::setCustomSurvive(double a) {
    customSurvive = a;
}

void GameWidget::setCustomBornAlgorithm(int a) {
    customBornAlgorithm = a;
}

void GameWidget::setCustomBornRule(int a) {
    customBornRule = a;
}

void GameWidget::setCustomBorn(double a) {
    customBorn = a;
}

void GameWidget::setLoopType(int type) {
    loopType = type;
}

unsigned int GameWidget::getLoopCount() {
    return loopCount;
}

