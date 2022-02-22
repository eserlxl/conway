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

    on_randomUniverse_clicked();

    void on_loadData_clicked();

    void on_algorithmBox_currentIndexChanged(int index);

    void on_cellSizeX_valueChanged(int x);

    void on_cellSizeY_valueChanged(int y);

    void updateProgressBar();

    void on_powerLimitBox_valueChanged(int powerLimit);

    void on_customSurviveAlgorithmBox_currentIndexChanged(int index);

    void on_customBornAlgorithmBox_currentIndexChanged(int index);

    void on_customBornBox_valueChanged(double value);

    void on_customSurviveBox_valueChanged(double value);

    void on_customBornRuleBox_currentIndexChanged(int index);

    void on_customSurviveRuleBox_currentIndexChanged(int index);

    void on_loopTypeComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget *game;
};

#endif // MAINWINDOW_H
