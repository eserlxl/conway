#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_loadData_clicked() {
    QString selfilter = tr("Text file (*.txt) (*.txt)");

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open data file"),
                                                    QDir::homePath(),
                                                    tr("Text file (*.txt) (*.txt);;Data File (*.dat) (*.dat)"),
                                                    &selfilter);
    if (filename.length() < 1)
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sv = 100;

    QVector <QVector<int>> v(sv + 1, QVector<int>(sv + 1, 0));

    int k = 0;
    while (!in.atEnd()) {
        k++;
        QString t1, t2;
        in >> t1;
        in >> t2;
        v[t1.toInt()][t2.toInt()]++;
    }

    int sX = sv;
    int sY = sv;
    ui->cellSizeX->setValue(sX);
    game->setCellSizeX(sX);
    ui->cellSizeY->setValue(sY);
    game->setCellSizeY(sY);

    QString dump = "", dump2 = "";
    for (int k = 0; k != sY; k++) {
        for (int j = 0; j != sX; j++) {
            //int t = qrand()%2;

            int t = v[k][j];

            if (t) {
                dump.append("*");
                dump2.append(QString::number(t));
            } else {
                dump.append("o");
                dump2.append("0");
            }

            dump2.append(" ");
        }
        dump.append("\n");
        dump2.append("\n");
    }
    game->setDump(dump);
    game->setDumpValues(dump2);

    v.clear();

    ui->iterInterval->setValue(1); // ms
    game->setInterval(1);
}
