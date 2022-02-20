#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::loadGame() {
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if (filename.length() < 1)
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sX, sY;
    in >> sX;
    ui->cellSizeX->setValue(sX);
    game->setCellSizeX(sX);

    in >> sY;
    ui->cellSizeY->setValue(sY);
    game->setCellSizeY(sY);

    int r, g, b; // RGB color
    in >> r >> g >> b;
    currentColor = QColor(r, g, b);
    game->setMasterColor(currentColor); // sets color of the dots
    QPixmap icon(16, 16); // icon on the button
    icon.fill(currentColor); // fill with new color
    ui->colorButton->setIcon(QIcon(icon)); // set icon for button
    in >> r; // r will be interval number
    ui->iterInterval->setValue(r);
    game->setInterval(r);

    QFile file2(filename.append(".dat"));
    if (!file2.open(QIODevice::ReadOnly))
        return;

    for (unsigned int i = 0; i < unsigned(sY); i++) {
        for (unsigned int j = 0; j < unsigned(sX); j++) {
            char c;
            file2.getChar(&c);
            unsigned int index = i * unsigned(sX) + j;
            game->value[index] = (256 + int(c)) % 256;
            game->initialValue[index] = game->value[index];

            game->universe[index] = game->value[index] > 0;
        }
    }

    file2.close();

    QFile file3(filename.append(".init"));
    if (file3.open(QIODevice::ReadOnly)) {
        for (unsigned int i = 0; i < unsigned(sY); i++) {
            for (unsigned int j = 0; j < unsigned(sX); j++) {
                char c;
                file3.getChar(&c);
                game->initialValue[i * unsigned(sX) + j] = (256 + int(c)) % 256;
            }
        }

        file3.close();
    }
}
