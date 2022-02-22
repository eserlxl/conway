#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        currentColor("#fff"),
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

    game->statusBar->showMessage(tr("Ready"));
    ui->statusBarLayout->addWidget(game->statusBar);

    ui->gameLayout->addWidget(game);

    ui->algorithmBox->addItem("Life - John Conway");
    ui->algorithmBox->addItem("Move - Stephen Morley");
    ui->algorithmBox->addItem("Maze");
    ui->algorithmBox->addItem("Mazecritic");
    ui->algorithmBox->addItem("Flock");
    ui->algorithmBox->addItem("Seeds");
    ui->algorithmBox->addItem("Colony");
    ui->algorithmBox->addItem("Custom");
    ui->algorithmBox->setCurrentIndex(0);

    ui->powerAlgorithmSurviveAlgorithmBox->addItem("None");
    ui->powerAlgorithmSurviveAlgorithmBox->addItem("Mean Power");
    ui->powerAlgorithmSurviveAlgorithmBox->addItem("Mean Power Value");
    ui->powerAlgorithmSurviveAlgorithmBox->addItem("Power");
    ui->powerAlgorithmSurviveAlgorithmBox->addItem("Power Value");

    ui->powerAlgorithmSurviveRuleBox->addItem("None");
    ui->powerAlgorithmSurviveRuleBox->addItem("<");
    ui->powerAlgorithmSurviveRuleBox->addItem(">");
    ui->powerAlgorithmSurviveRuleBox->addItem("≤");
    ui->powerAlgorithmSurviveRuleBox->addItem("≥");
    ui->powerAlgorithmSurviveRuleBox->addItem("=");
    ui->powerAlgorithmSurviveRuleBox->addItem("≠");

    ui->powerAlgorithmBornAlgorithmBox->addItem("None");
    ui->powerAlgorithmBornAlgorithmBox->addItem("Mean Power");
    ui->powerAlgorithmBornAlgorithmBox->addItem("Mean Power Value");
    ui->powerAlgorithmBornAlgorithmBox->addItem("Power");
    ui->powerAlgorithmBornAlgorithmBox->addItem("Power Value");

    ui->powerAlgorithmBornRuleBox->addItem("None");
    ui->powerAlgorithmBornRuleBox->addItem("<");
    ui->powerAlgorithmBornRuleBox->addItem(">");
    ui->powerAlgorithmBornRuleBox->addItem("≤");
    ui->powerAlgorithmBornRuleBox->addItem("≥");
    ui->powerAlgorithmBornRuleBox->addItem("=");
    ui->powerAlgorithmBornRuleBox->addItem("≠");

    ui->loopTypeComboBox->addItem("Standard");
    ui->loopTypeComboBox->addItem("Inverse");
    ui->loopTypeComboBox->addItem("Alternating");
    ui->loopTypeComboBox->addItem("Random");
    ui->loopTypeComboBox->setCurrentIndex(3);
}

MainWindow::~MainWindow() {
    delete ui;
}
