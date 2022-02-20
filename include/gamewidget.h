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
#include <qmath.h>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

    ~GameWidget();

    bool *universe;     // map
    int *initialValue;
    int *value;     // map
    int *power; // map
    int *powerValue; // map

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

    void setPowerAlgorithmBornAlgorithm(int a);

    void setPowerAlgorithmBornRule(int a);

    void setPowerAlgorithmBorn(double a);

    void setPowerAlgorithmSurviveAlgorithm(int a);

    void setPowerAlgorithmSurviveRule(int a);

    void setPowerAlgorithmSurvive(double a);

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

    bool *next;     // map
    int *nextValue;     // map
    int *checked;
    unsigned int *bornLoop;

    unsigned int universeSizeX;     // width
    unsigned int universeSizeY;     // height
    int powerLimit;

    unsigned int population;
    unsigned int populationLimit;

    unsigned int unChangedCell;

    int algorithm;

    int powerAlgorithmBornAlgorithm;
    int powerAlgorithmBornRule;
    double powerAlgorithmBorn;
    int powerAlgorithmSurviveAlgorithm;
    int powerAlgorithmSurviveRule;
    double powerAlgorithmSurvive;

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
