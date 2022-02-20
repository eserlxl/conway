#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        currentColor(QColor("#000")),
        game(new GameWidget(this)) {
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon(QIcon(icon));

    connect(ui->startButton, SIGNAL(clicked()), game, SLOT(startGame()));
    connect(ui->stepButton, SIGNAL(clicked()), game, SLOT(stepGame()));
    connect(ui->stopButton, SIGNAL(clicked()), game, SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game, SLOT(clear()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(game, SIGNAL(environmentChanged(bool)), ui->cellSizeX, SLOT(setDisabled(bool)));
    connect(game, SIGNAL(environmentChanged(bool)), ui->cellSizeY, SLOT(setDisabled(bool)));
    connect(game, SIGNAL(gameEnds(bool)), ui->cellSizeX, SLOT(setEnabled(bool)));
    connect(game, SIGNAL(gameEnds(bool)), ui->cellSizeY, SLOT(setEnabled(bool)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));
    connect(game, SIGNAL(nextLoopStarts(bool)), this, SLOT(updateProgressBar()));

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    ui->gameLayout->setStretchFactor(ui->gameLayout, 8);
    ui->gameLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);

    ui->algorithmBox->addItem("Life - John Conway");
    ui->algorithmBox->addItem("Move - Stephen Morley");
    ui->algorithmBox->addItem("Maze");
    ui->algorithmBox->addItem("Mazecritic");
    ui->algorithmBox->addItem("Flock");
    ui->algorithmBox->addItem("Seeds");

    ui->stabilitySurviveAlgorithmBox->addItem("None");
    ui->stabilitySurviveAlgorithmBox->addItem("Mean Power");
    ui->stabilitySurviveAlgorithmBox->addItem("Mean PowerValue");
    ui->stabilitySurviveAlgorithmBox->addItem("Power");
    ui->stabilitySurviveAlgorithmBox->addItem("PowerValue");

    ui->stabilitySurviveRuleBox->addItem("None");
    ui->stabilitySurviveRuleBox->addItem("<");
    ui->stabilitySurviveRuleBox->addItem(">");
    ui->stabilitySurviveRuleBox->addItem("=");
    ui->stabilitySurviveRuleBox->addItem("≠");

    ui->stabilityBornAlgorithmBox->addItem("None");
    ui->stabilityBornAlgorithmBox->addItem("Mean Power");
    ui->stabilityBornAlgorithmBox->addItem("Mean PowerValue");
    ui->stabilityBornAlgorithmBox->addItem("Power");
    ui->stabilityBornAlgorithmBox->addItem("PowerValue");

    ui->stabilityBornRuleBox->addItem("None");
    ui->stabilityBornRuleBox->addItem("<");
    ui->stabilityBornRuleBox->addItem(">");
    ui->stabilityBornRuleBox->addItem("=");
    ui->stabilityBornRuleBox->addItem("≠");
}

MainWindow::~MainWindow() {
    delete ui;
}
