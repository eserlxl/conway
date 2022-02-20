#include "include/gamewidget.h"

double GameWidget::max(double x, double y) {
    if (x < y) {
        x = y;
    }

    return x;
}

int GameWidget::max(int x, int y) {
    if (x < y) {
        x = y;
    }

    return x;
}

double GameWidget::min(double x, double y) {
    if (x > y) {
        x = y;
    }

    return x;
}

int GameWidget::min(int x, int y) {
    if (x > y) {
        x = y;
    }

    return x;
}

double GameWidget::limit(double x, double min, double max) {
    if (x < min) {
        x = min;
    } else if (x > max) {
        x = max;
    }

    return x;
}

int GameWidget::limit(int x, int min, int max) {
    if (x < min) {
        x = min;
    } else if (x > max) {
        x = max;
    }

    return x;
}
