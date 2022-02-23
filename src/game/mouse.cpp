#include "include/gamewidget.h"

void GameWidget::mousePressEvent(QMouseEvent *e) {
    if (e->x() >= 0 && e->x() < width() && e->y() >= 0 && e->y() < height()) {
        emit environmentChanged(true);
        unsigned cellWidth = getCellWidth();
        unsigned cellHeight = getCellHeight();

        unsigned i = e->y() / (double) cellHeight;
        unsigned j = e->x() / (double) cellWidth;
        unsigned index = i * universeSizeX + j;

        //std::cout << e->x()<<" "<<e->y()<<" "<<width()<<" "<<height()<<" "<<cellWidth<<" "<<cellHeight<<" "<<index<<std::endl;

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
        unsigned cellWidth = getCellWidth();
        unsigned cellHeight = getCellHeight();
        unsigned i = e->y() / (double) cellHeight;
        unsigned j = e->x() / (double) cellWidth;
        //qDebug() << e->x()<<" "<<e->y()<<" "<<width()<<" "<<height()<<"\n";

        unsigned index = i * universeSizeX + j;
        if (!universe[index]) { // if current cell is empty,fill in it
            universe[index] = !universe[index];
            if (universe[index]) {
                value[index] = 1;
            }
            update();
        }
    }
}
