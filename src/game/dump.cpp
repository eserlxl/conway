#include "include/gamewidget.h"

QString GameWidget::dump() {
    char temp;
    QString master = "";
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            if (universe[i * universeSizeX + j] == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

QString GameWidget::dumpValues() {
    QString master = "";
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            master.append(QString::number(value[i * universeSizeX + j]));
            master.append(" ");
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDumpValues(const QString &data) {
    unsigned int k = 0;

    QStringList list =
            QString(data).split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    foreach(QString
    s, list) {
        QStringList list2 = s.split(QRegExp("[\t\\s+]"), QString::SkipEmptyParts);

        foreach(QString
        s2, list2) {
            value[k++] = s2.toInt();
        }
    }

    update();
}

void GameWidget::setDump(const QString &data) {
    int current = 0;
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            universe[i * universeSizeX + j] = data[current] == '*';
            current++;
        }
        current++;
    }
    update();
}
