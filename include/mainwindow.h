#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "gamewidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public
    slots:
            void

    selectMasterColor();

    void saveGame();

    void loadGame();

private
    slots:
            void

    on_rastgele_clicked();

    void on_stabilityBox_valueChanged(int s);

    void on_loadData_clicked();

    void on_algorithmBox_currentIndexChanged(int index);

    void on_cellSizeX_valueChanged(int x);

    void on_cellSizeY_valueChanged(int y);

    void updateProgressBar();

    void on_powerLimitBox_valueChanged(int powerLimit);

    void on_stabilitySurviveAlgorithmBox_currentIndexChanged(int index);

    void on_stabilityBornAlgorithmBox_currentIndexChanged(int index);

    void on_stabilityBornBox_valueChanged(double value);

    void on_stabilitySurviveBox_valueChanged(double value);

    void on_stabilityBornRuleBox_currentIndexChanged(int index);

    void on_stabilitySurviveRuleBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget *game;
};

#endif // MAINWINDOW_H
