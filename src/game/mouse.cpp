#include "include/gamewidget.h"

void GameWidget::mousePressEvent(QMouseEvent *e) {
    if (e->x() >= 0 && e->x() < width() && e->y() >= 0 && e->y() < height()) {
        emit environmentChanged(true);
        double cellWidth = floor(double(width()) / int(universeSizeX) + 1);
        double cellHeight = floor(double(height()) / int(universeSizeY) + 1);
        //qDebug() << e->x()<<" "<<e->y()<<" "<<width()<<" "<<height()<<" "<<cellWidth<<" "<<cellHeight<<"\n";
        int i = int(floor(e->y() / cellHeight));
        int j = int(floor(e->x() / cellWidth));
        int index = i * int(universeSizeX) + j;

        universe[index] = !universe[index];
        if (!universe[index]) {
            value[index] = 0;
        }
        if (universe[index] && value[index] < powerLimit) {
            value[index]++;
        }

        update();
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *e) {

    if (e->x() >= 0 && e->x() < width() && e->y() >= 0 && e->y() < height()) {
        double cellWidth = floor(double(width()) / int(universeSizeX) + 1);
        double cellHeight = floor(double(height()) / int(universeSizeY) + 1);
        int i = int(floor(e->y() / cellHeight));
        int j = int(floor(e->x() / cellWidth));
        //qDebug() << e->x()<<" "<<e->y()<<" "<<width()<<" "<<height()<<"\n";

        int index = i * int(universeSizeX) + j;
        if (!universe[index]) { // if current cell is empty,fill in it
            universe[index] = !universe[index];
            if (universe[index]) {
                value[index] = 1;
            }
            update();
        }
    }
}
