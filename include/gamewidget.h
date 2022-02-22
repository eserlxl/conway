#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QRectF>
#include <QTimer>
#include <QRandomGenerator>
#include <QStatusBar>
#include <qmath.h>
#include <iostream>
#include <vector>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

    QStatusBar *statusBar = nullptr;

    ~GameWidget();

    std::vector<bool> universe;
    std::vector<int> initialValue;
    std::vector<int> value;
    std::vector<int> power;
    std::vector<int> powerValue;

protected:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    signals:
//when one of the cell has been changed,emit this signal to lock the universeSize
            void

    environmentChanged(bool ok);

//when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

    void nextLoopStarts(bool ok);

public
    slots:
            void

    startGame(const int &number = -1);     // start
    void stepGame(); // run for 1 step
    void stopGame();     // finish
    void clear();     // clear

    double limit(double x, double min, double max);

    int limit(int x, int min, int max);

    double max(double x, double y);

    int max(int x, int y);

    double min(double x, double y);

    int min(int x, int y);

    void setCellSizeX(const int &x);

    void setCellSizeY(const int &y);

    void resize(const int &x, const int &y);

    int cellSizeX();

    int cellSizeY();

    int interval();     // interval between generations
    void setInterval(int msec);     // set interval between generations

    unsigned int getLoopCount();

    void setLoopType(int type);

    void setPowerLimit(int limit);

    int getPowerLimit();

    unsigned int getPopulation();

    void setAlgorithm(int a);

    void setCustomBornAlgorithm(int a);

    void setCustomBornRule(int a);

    void setCustomBorn(double a);

    void setCustomSurviveAlgorithm(int a);

    void setCustomSurviveRule(int a);

    void setCustomSurvive(double a);

    void setWorkDone(double ratio);

    double getWorkDone();

    void setWorkSpeed(double speed);

    double getWorkSpeed();

    void setRemainingTime(double time);

    double getRemainingTime();

    double getElapsedTime();

    void setMasterColor(const QColor &color);     // set color of the cells
    QColor getMasterColor(); // get color of the cells

    QString dump();     // dump of current universe
    void setDump(const QString &data);     // set current universe from it's dump

    QString dumpValues();     // dump of current values of the universe
    void setDumpValues(const QString &data);     // set current values of the universe from it's dump

private
    slots:
            void
    paintGrid(QPainter
    &p);

    void paintUniverse(QPainter &p);

    void newGeneration();

private:
    QColor m_masterColor;
    QTimer *timer;
    QTime myTimer;
    int generations;

    unsigned int loopCount;

    std::vector<bool> next;
    std::vector<int> nextValue;
    std::vector<unsigned> bornLoop;

    unsigned int universeSizeX;     // width
    unsigned int universeSizeY;     // height
    int powerLimit;

    unsigned int population;
    unsigned int populationLimit;

    unsigned int unChangedCell;

    int algorithm;

    int customBornAlgorithm;
    int customBornRule;
    double customBorn;
    int customSurviveAlgorithm;
    int customSurviveRule;
    double customSurvive;

    int loopType;

    bool
    isAlive(unsigned int index, unsigned int row, unsigned int col);     // return true if universe[k][j] accept rules
    void resetUniverse();    // reset the size of universe
    double workDone;
    double workDonePrevious;
    double workSpeed;
    double remainingTime;
    double elapsedTime;
    double elapsedTimePrevious;

    unsigned int neighbourhood(unsigned int row, unsigned int col);
};

#endif // GAMEWIDGET_H
