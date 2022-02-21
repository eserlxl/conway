#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_randomUniverse_clicked() {
    for (int i = 0; i < game->cellSizeY(); i++) {
        for (int j = 0; j < game->cellSizeX(); j++) {
            unsigned int index = i * game->cellSizeX() + j;

            if (qrand() % 16 == 0) {
                game->value[index] = qrand() % (game->getPowerLimit() + 1);
                game->initialValue[index] = game->value[index];

                game->universe[index] = game->value[index] > 0;
            } else {
                game->value[index] = 0;
                game->initialValue[index] = 0;
                game->universe[index] = false;
            }
        }
    }

    // should randomUniverse return to the initial color?
    //int r=0,g=0,b=0; // RGB color
    //currentColor = QColor(r,g,b);
    //game->setMasterColor(currentColor); // sets color of the dots

    QPixmap icon(16, 16); // icon on the button
    icon.fill(currentColor); // fill with new color
    ui->colorButton->setIcon(QIcon(icon)); // set icon for button
    ui->iterInterval->setValue(1); // ms
    game->setInterval(1);
    update();
}

void MainWindow::on_cellSizeX_valueChanged(int x) {
    game->setCellSizeX(x);
}

void MainWindow::on_cellSizeY_valueChanged(int y) {
    game->setCellSizeY(y);
}
