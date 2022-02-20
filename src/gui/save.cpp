#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::saveGame() {
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if (filename.length() < 1)
        return;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString s = QString::number(game->cellSizeX()) + " " + QString::number(game->cellSizeY()) + "\n";

    s.append(QString::number(game->getPowerLimit()) + "\n");
    QColor masterColor = game->getMasterColor();
    QString buf = QString::number(masterColor.red()) + " " +
                  QString::number(masterColor.green()) + " " +
                  QString::number(masterColor.blue()) + "\n";
    s.append(buf);
    buf.clear();
    buf = QString::number(ui->iterInterval->value()) + "\n";
    s.append(buf);

    file.write(s.toUtf8());
    file.close();

    QString dataFile = filename + ".dat";
    QString dataFile0 = filename + ".init";
    QString databaseFile = filename + ".db";
    QString dataFilePart0 = filename + ".0";
    QString dataFilePart1 = filename + ".1";

    QFile file2(dataFile);
    if (!file2.open(QIODevice::WriteOnly))
        return;
    QFile file3(dataFile0);
    if (!file3.open(QIODevice::WriteOnly))
        return;
    QFile file4(databaseFile);
    if (!file4.open(QIODevice::WriteOnly))
        return;
    QFile file5(dataFilePart0);
    if (!file5.open(QIODevice::WriteOnly))
        return;
    QFile file6(dataFilePart1);
    if (!file6.open(QIODevice::WriteOnly))
        return;

    unsigned int universeSizeX = unsigned(game->cellSizeX());
    unsigned int universeSizeY = unsigned(game->cellSizeY());

    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            unsigned int index = i * universeSizeX + j;
            file2.putChar(char(game->value[index]));
            file3.putChar(char(game->initialValue[index]));
            file4.putChar(char(game->universe[index] + 48));

            if (game->powerValue[index] > 2 * 255) {
                file5.putChar(char(game->initialValue[index]));
            } else {
                file6.putChar(char(game->initialValue[index]));
            }
        }
    }

    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file6.close();
}
